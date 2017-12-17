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
long long inv_(long long val, long long Pr)
{
	return fast(val, Pr - 2, Pr);
}
template<typename T>
class NTT
{
	ve<int> bit_reverse;
	int SZ, depth;
	 long long MOD;
	 long long ROOT; // MOD == 15*(1<<27)+1 (prime)
public:
	NTT() :MOD(2013265921), ROOT(22) {}
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
		for (int i = 1; i + 1<SZ; i++)
		{
			if ((i << 1)<SZ)
				bit_reverse[i << 1] = bit_reverse[i] >> 1;
			if ((i & 1) == 0)
			{
				bit_reverse[i + 1] = bit_reverse[i] | (SZ >> 1);
			}
		}
	}
	void ntt(vector<T> &a, int root)
	{
		for (int i = 0; i < SZ; i++)
			if (bit_reverse[i] < i)
				swap(a[i], a[bit_reverse[i]]);
		for (int i = 1; i<SZ; i <<= 1)
		{
			// ROOT**(i*2)=ROOT**((1<<27)*15)=ROOT**(MOD-1)=1
			long long w = fast(root, (MOD - 1) / (i<<1), MOD);
			for (int j = 0; j<SZ; j += (i << 1))
			{
				long long w0 = 1;
				for (int k = 0; k<i; k++)
				{
					long long V = a[k + j];
					long long W = (w0*a[k + j + i]) % MOD;
					a[k + j] = (V + W)%MOD;
					a[k + j + i] = (V - W+MOD)%MOD;
					w0 *= w;
					w0 %= MOD;
				}
			}
		}
	}
	void ntt_inverse(vector<T> &a)
	{
		ntt(a, inv_(ROOT, MOD));
		long long INV = inv_(1 << depth, MOD);
		for (auto &x : a)
		{
			x =(INV*x)%MOD;
		}
	}
	void convolve(ve<T> &a, vector<T> &b, vector<T> &c)// a0+a1x+a2x2    a.b= c
	{
		prepare(max(a.size(), b.size())*2);
		a.resize(SZ);
		b.resize(SZ);
		c.resize(SZ);
		ntt(a, ROOT);
		ntt(b, ROOT);
		for (int i = 0; i<SZ; i++)
		{
			c[i] = (a[i] * (b[i]*1LL))%MOD;
		}
		ntt_inverse(c);
	}
};
