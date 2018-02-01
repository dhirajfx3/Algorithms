struct extended
{
	long long d, x, y;
	extended(long long d, long long x, long long y) :y(y), x(x), d(d) {}
};
extended eu(long long a, long long b)
{
	if (b == 0)
	{
		return extended(a, 1, 0);
	}
	extended A = eu(b, a%b);
	extended B(A.d, A.y, A.x - A.y*(a / b));
	return B;
}
long long mod_inv(long long val, long long m)
{
	return (eu(val, m).x + m) % m;
}
long long mod_inv2(long long val, long long m,long long p,long long K)   // inv of v mod prime p to power k  
{
	if (val == 0)
		return 0;
	int k0 = 1;
	long long ig= fast(val, p - 2, p);
	// now we will use u(n+1) = u(n)(2-au(n))
	while (k0 < K)
	{
		ig = ig*((2 - ig*val+m))%m;
		k0 *= 2;
	}
	return ig;
 
}
long long chinese_rem(vector<long long> &ni, vector<long long> &ai, long long n)
{
	long long ans = 0;
	for (int i = 0; i<ni.size(); i++)
	{
		long long m_inv = (mod_inv(n / ni[i], ni[i])*(n / ni[i])) % n;
		ans = (ans + (ai[i] * m_inv) % n) % n;
	}
	return ans;
}
