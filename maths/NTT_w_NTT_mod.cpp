/*
How to use :
NTT<long long> Object;
c=Object.convolve(a,b,c); a,b  and c are  vectors of type [int]
to be convolved and c is where you will get the result;

Results will be modulo : 119*(1<<23)   [ find and replace this with other NTT modulo along with its primitive root to find answer other modulo(need not be prime) ]
Safely Apply FFT to array of size 2x10**6
mod = 119*(1<<23)+1  #998244353
root = 3
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
		vector<T> a, b, c;
		vector<vector<int> > W, IW;
		int SZ, depth;
		long long MOD;
		long long ROOT;
		long long ROOT_INV;
		template<class T2>
		inline void check_over(T2 &z)
		{
			z -= ((z >= MOD) ? MOD : 0);
		}
		template<class T2>
		inline void check_neg(T2 &z)
		{
			z += ((z < 0) ? MOD : 0);
		}
		inline int mul(const int &p, const int &q)
		{
			return (p * 1ll * q) % MOD;
		}
		inline int add(int z)
		{
			return z >= MOD ? z - MOD : z;
		}
		inline int sub(int z)
		{
			return z < 0 ? z + MOD : z;
		}
	public:
		NTT()
		{
			MOD = 119 * (1 << 23) + 1;
			ROOT = 3;
			ROOT_INV = inv_(ROOT, MOD);
			evaluate_ohmega();
		}
		// O(n) Ohmega/Inv-Ohmega
		void evaluate_ohmega()
		{
			// W[i][j] = Root ^ j/(1<<i)
			const int max_log = 21, max_size = 1 << max_log;
			int nth_root = fast(ROOT, (MOD - 1) >> max_log, MOD);
			int curr_val = 1;
			W.resize(max_log + 1);
			W[max_log].resize(max_size);
			for (int i = 0; i < max_size; i++)
			{
				W[max_log][i] = curr_val;
				curr_val = mul(curr_val, nth_root);
			}

			for (int i = max_log - 1; i >= 1; i--)
			{
				W[i].resize(1 << i);
				int block_size = 1 << i;
				for (int j = 0; j < block_size; j++)
				{
					W[i][j] = W[i + 1][j << 1];
				}
			}

			int inverse_nth_root = fast(ROOT_INV, (MOD - 1) >> max_log, MOD);
			curr_val = 1;
			IW.resize(max_log + 1);
			IW[max_log].resize(max_size);
			for (int i = 0; i < max_size; i++)
			{
				IW[max_log][i] = curr_val;
				curr_val = mul(curr_val, inverse_nth_root);
			}

			for (int i = max_log - 1; i >= 1; i--)
			{
				IW[i].resize(1 << i);
				int block_size = 1 << i;
				for (int j = 0; j < block_size; j++)
				{
					IW[i][j] = IW[i + 1][j << 1];
				}
			}
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

		void ntt(vector<T> &v)
		{
			for (int i = 0; i < SZ; i++)
				if (bit_reverse[i] < i)
					swap(v[i], v[bit_reverse[i]]);
			for (int i = 1, dep = 1; i < SZ; i <<= 1, ++dep)
			{
				for (int j = 0, block_size = (i << 1); j < SZ; j += block_size)
				{
					for (int k = j; k < i + j; k++)
					{
						int u2 = mul(W[dep][k - j], v[i + k]);
						int u1 = v[k];
						v[k] = add(u1 + u2);
						v[k + i] = sub(u1 - u2);
					}
				}
			}
		}
		void ntt_inverse(vector<T> &v)
		{
			for (int i = 0; i < SZ; i++)
				if (bit_reverse[i] < i)
					swap(v[i], v[bit_reverse[i]]);
			for (int i = 1, dep = 1; i < SZ; i <<= 1, ++dep)
			{
				for (int j = 0, block_size = (i << 1); j < SZ; j += block_size)
				{
					for (int k = j; k < i + j; k++)
					{
						int u2 = mul(IW[dep][k - j], v[i + k]);
						int u1 = v[k];
						v[k] = add(u1 + u2);
						v[k + i] = sub(u1 - u2);
					}
				}
			}
			long long INV = inv_(1 << depth, MOD);
			for (auto x = 0; x < v.size(); x++)
				v[x] = (v[x] * INV) % MOD;
		}
		void convolve(const vector<T> &p, const vector<T> &q, vector<T> &r)// a0+a1x+a2x2    a.b= c
		{
			prepare((p.size() + q.size()) - 1);
			a = p;
			a.resize(SZ);
			b = q;
			b.resize(SZ);
			r.resize(SZ);
			ntt(a);
			ntt(b);
			for (int i = 0; i < SZ; i++)
				r[i] = (a[i] * (b[i] * 1LL)) % MOD;

			ntt_inverse(r);
			while (r.size() > 1 && r.back() == 0)
				r.pop_back();
		}
		void multiply(const vector<T> &p, const vector<T> &q, vector<T> &r)
		{
			if ((p.size() + 1)*(q.size() + 1) < 5000)
				pm(p, q, r);
			else
				convolve(p, q, r);
		}
		void pm(const vector<T> &a, const vector<T> &b, vector<T> &c)
		{
			c.resize(a.size() - 1 + b.size());
			for (int i = 0; i < a.size(); i++)
			{
				for (int j = 0; j < b.size(); j++)
				{
					c[i + j] = (c[i + j] + a[i] * 1ll * b[j]) % MOD;
				}
			}
		}

	};
}
FFT_MODULO::NTT<int> N;
