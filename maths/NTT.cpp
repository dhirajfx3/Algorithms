/*
How to use :
NTT<long long> Object;
c=Object.convolve(a,b); a and b are  vectors of type [long long]
to be convolved and c is where you will get the result;

Results will be modulo : 1000000007   [ find and replace 1000000007 with other modulo to find answer other modulo(need not be prime) ]

For any convolution with coefficients less than 10**9
(i.e 328747545207318082056355840 is when max coeff after fft)
Safely Apply FFT to array of size 2x10**6
mod1 = 15*(1<<27)+1  #2013265921
root1 = 22
mod2 = 119*(1<<23)+1  #998244353
root2 = 3

mod3  = 39*(1<<22)+1   #163577857
root3 = 23
*/
#include <vector>
#include <algorithm>
using namespace std;
namespace FFT_MODULO
{
	long long fast(long long a, long long b, long long pr)
	{
		if (b == 0)
			return 1 % pr;
		long long ans = 1 % pr;
		while (b)
		{
			if (b & 1)
			{
				ans *= a;
				ans %= pr;
			}
			b >>= 1;
			a *= a;
			a %= pr;
		}
		return ans;
	}

	template<typename T>
	void eu(int a, int b, T *x, T *y)
	{
		if (b == 0)
		{
			*x = 1;
			*y = 0;
			return;
		}
		T tempx, tempy;
		eu(b, a%b, &tempx, &tempy);
		*x = tempy;
		*y = tempx - tempy * (a / b);
		return;
	}
	template<typename T>
	T inv_(T val, T m)
	{
		T x, y;
		eu(val, m, &x, &y);
		return x < 0 ? x + m : x;
	}
	template<typename T>
	class NTT
	{
		vector<int> bit_reverse;
		vector<T> a[3], b[3], c[3];
		vector<T> a2[2], b2[2], c2[2];
		vector<long long> rps;
		int SZ, depth;
		long long my_mod;
		long long MOD[3];
		long long ROOT[3];
		long long ROOT_INV[3];
		template<class T2, class T3>
		inline void check(T2 &z, const T3 &mod)
		{
			z -= z >= mod ? mod : 0;
		}
		template<class T2, class T3>
		inline void check2(T2 &z, const T3 &mod)
		{
			z += z < 0 ? mod : 0;
		}
	public:
		void set_mod(long long t)
		{
			my_mod = t;
		}
		NTT() :my_mod(1000000007)
		{
			MOD[2] = 15 * (1 << 27) + 1;
			ROOT[2] = 22;
			MOD[1] = 119 * (1 << 23) + 1;
			ROOT[1] = 3;
			MOD[0] = 39 * (1 << 22) + 1;
			ROOT[0] = 23;
			for (int i = 0; i < 3; i++)
				ROOT_INV[i] = inv_(ROOT[i], MOD[i]);
		}
		// O(n) bitreverse
		void prepare(int pre)
		{
			SZ = 1;
			depth = 0;
			--pre;
			while (pre)
			{
				SZ <<= 1;
				++depth;
				pre >>= 1;
			}
			bit_reverse.resize(SZ);
			rps.resize(SZ);
			bit_reverse[0] = 0;
			bit_reverse[1] = SZ >> 1;
			for (int i = 1; i + 1 < SZ; i++)
			{
				if ((i << 1) < SZ)
					bit_reverse[i << 1] = bit_reverse[i] >> 1;
				if ((i & 1) == 0)
				{
					bit_reverse[i + 1] = bit_reverse[i] | (SZ >> 1);
				}
			}
		}
		void nttk(vector<T> a[], long long Root[], int K)
		{
			for (int k = 0; k < K; k++)
			{
				for (int i = 0; i < SZ; i++)
				{
					if (bit_reverse[i] < i)
					{
						swap(a[k][i], a[k][bit_reverse[i]]);
					}
				}
			}
			for (int k_mod = 0; k_mod < K; k_mod++)
			{
				int cmod = MOD[k_mod];
				vector<T> &v = a[k_mod];
				for (int i = 1; i < SZ; i <<= 1)
				{
					long long wk = fast(Root[k_mod], (cmod - 1) / (i << 1), cmod);
					rps[0] = 1;
					for (int j = 1; j < i; j++)
						rps[j] = (rps[j - 1] * wk) % cmod;
					for (int j = 0, blk = (i << 1); j < SZ; j += blk)
					{
						for (int k = 0; k < i; k++)
						{
							long long V = v[j + k];
							long long W = (rps[k] * v[j + i + k]) % cmod;
							long long Z = V + W;
							check(Z, cmod);
							v[j + k] = Z;
							Z = V - W;
							check2(Z, cmod);
							v[j + i + k] = Z;
						}
					}
				}
			}
		}
		void nttk_inverse(vector<T> p[], int K)
		{
			nttk(p, ROOT_INV, K);
			vector<long long> INV(K);
			for (int i = 0; i < K; i++)
				INV[i] = inv_<long long>(1 << depth, MOD[i]);
			for (int j = 0; j < K; j++)
			{
				for (auto x = 0; x < p[0].size(); x++)
				{
					p[j][x] = (p[j][x] * INV[j]) % MOD[j];
				}
			}
		}
		void convolve(vector<T> &p, vector<T> &q, vector<T> &r)// a0+a1x+a2x2    a.b= c
		{
			///*
			if (my_mod > 10)
			{
				karatsuba(p, q, r);
				while (r.size() > 1 && r.back() == 0)
					r.pop_back();
				return;
			}
			// comment above line only if coefficient of resulting polynomial will fit in 64 bit integer*/
			prepare((p.size() + q.size()) - 1);
			int K = 2;
			a[0] = p;
			a[0].resize(SZ);
			b[0] = q;
			b[0].resize(SZ);
			c[0].resize(SZ);
			for (int i = 1; i < K; i++)
				a[i] = a[0], b[i] = b[0], c[i] = c[0];
			nttk(a, ROOT, K);
			nttk(b, ROOT, K);
			for (int j = 0; j < K; j++)
			{
				for (int i = 0; i < SZ; i++)
				{
					c[j][i] = (a[j][i] * (b[j][i] * 1LL)) % MOD[j];
				}
			}
			nttk_inverse(c, K);
			chinese_rem(c, r, MOD, K, my_mod);
			while (r.size() > 1 && r.back() == 0)
				r.pop_back();
		}
		vector<T> multiply(vector<T> &p, vector<T> &q)
		{
				if ((p.size() + 1)*(q.size() + 1) < 10000)
					return pm(p, q);
			vector<T> z;
			convolve(p, q, z);
			return z;
		}
		vector<T> pm(const vector<T> &a, const vector<T> &b)
		{
			vector<T> c(a.size() - 1 + b.size());
			for (int i = 0; i < a.size(); i++)
			{
				for (int j = 0; j < b.size(); j++)
				{
					c[i + j] = (c[i + j] + a[i] * 1ll * b[j]) % my_mod;
				}
			}
			return c;
		}
		void chinese_rem(vector<T> c[], vector<T> &ans, long long ni[], long long k, long long modulo_final)
		{
			ans.resize(c[0].size());
			vector<long long>  MOD_INV(2, 1);
			MOD_INV[0] = inv_(ni[0], ni[1]);
			MOD_INV[1] = inv_(ni[1], ni[0]);
			long long Z = ni[0] * ni[1];
			for (int j = 0; j < ans.size(); j++)
			{
				ans[j] = ((((c[0][j] * MOD_INV[1]) % ni[0])*ni[1] + ((c[1][j] * MOD_INV[0]) % ni[1])*ni[0]) % Z) % modulo_final;
			}

			return;
		}
		void karatsuba(vector<T> &p, vector<T> &q, vector<T> &r)
		{
			prepare((p.size() + q.size()) - 1);
			int K = 2;
			long long k_2 = 1, k = 0;
			while (k_2*k_2 < my_mod)
				k_2 *= 2, ++k;

			a[0].resize(SZ);
			a[1].resize(SZ);
			b[0].resize(SZ);
			b[1].resize(SZ);
			c[0].resize(SZ);
			c[1].resize(SZ);

			for (int i = 0; i < SZ; i++)
			{
				if (i < p.size())
					a[0][i] = a[1][i] = (p[i] >> k);
				else
					a[0][i] = a[1][i] = 0;
			}
			for (int i = 0; i < SZ; i++)
			{
				if (i < q.size())
					b[0][i] = b[1][i] = (q[i] >> k);
				else
					b[0][i] = b[1][i] = 0;
			}

			a2[0].resize(SZ);
			a2[1].resize(SZ);
			b2[0].resize(SZ);
			b2[1].resize(SZ);
			c2[0].resize(SZ);
			c2[1].resize(SZ);

			for (int i = 0; i < SZ; i++)
			{
				if (i < p.size())
					a2[0][i] = a2[1][i] = (p[i] & (k_2 - 1));
				else
					a2[0][i] = a2[1][i] = 0;
			}

			for (int i = 0; i < SZ; i++)
			{
				if (i < q.size())
					b2[0][i] = b2[1][i] = (q[i] & (k_2 - 1));
				else
					b2[0][i] = b2[1][i] = 0;
			}
			nttk(a, ROOT, K);
			nttk(b, ROOT, K);

			nttk(a2, ROOT, K);
			nttk(b2, ROOT, K);

			/*
			 [a2+a.k][b2+b.k]
			 a2.b2+a.b.k.k+[a2.b+a.b2].k
			*/
			for (int j = 0; j < K; j++)
			{
				for (int i = 0; i < SZ; i++)
				{
					c[j][i] = (a2[j][i] * (b2[j][i] * 1LL)) % MOD[j];
				}
			}
			nttk_inverse(c, K);
			chinese_rem(c, r, MOD, K, my_mod);

			for (int j = 0; j < K; j++)
			{
				for (int i = 0; i < SZ; i++)
				{
					c2[j][i] = (a[j][i] * (b[j][i] * 1LL)) % MOD[j];
				}
			}
			nttk_inverse(c2, K);
			chinese_rem(c2, c[0], MOD, K, my_mod);
			long long K1;
			for (int j = 0; j < K; j++)
			{
				for (int i = 0; i < SZ; i++)
				{
					K1 = (a2[j][i] * (b[j][i] * 1LL)) % MOD[j];
					K1 += (a[j][i] * (b2[j][i] * 1LL)) % MOD[j];
					check(K1, MOD[j]);
					c2[j][i] = K1;
				}
			}
			nttk_inverse(c2, K);
			chinese_rem(c2, c[1], MOD, K, my_mod);

			K1 = (k_2*k_2) % my_mod;
			for (int i = 0; i < SZ; i++)
			{
				r[i] = (r[i] + c[0][i] * K1 + c[1][i] * k_2) % my_mod;
			}
		}
	};
}
