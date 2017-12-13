// Euler totient using sieve O(n log n)
#define Lim 1000001
int phi[Lim+1],prime[Lim+1];
void phif()
{
	for(int i=0;i<=Lim;i++)
	{
		phi[i]=i;
	}
	phi[1]=1;
	for(int64_t i=2;i<=Lim;i++)
	{
		if(!prime[i])
		for(int64_t j=i;j<=Lim;j+=i)
		{
			prime[j]=1;
			phi[j]=(phi[j]/i)*(i-1);
		}
	}
}
//Naive method for euler totient
long long totient(long long  p)
{
	long long t=p;
	for(long long j=2;j*j<=p;j++)
	{
		int k=0;
		while(p%j==0)
			p/=j,++k;
		if(k)
			t=(t/j)*(j-1);
	}
	if(p!=1)
		t=(t/p)*(p-1);
	return t;
}
// Seive linear totient http://codeforces.com/blog/entry/10119 O(n)
int pr[Lim+1],cnt=0,lp[Lim+1];
//int phi[Lim+1];  // uncomment this
void linear_phif()
{
	phi[1] = 1;
    for (int i = 2; i <= Lim; ++i)
    {
        if (lp[i] == 0)
        {
            lp[i] = i;
            phi[i] = i - 1;
            pr[cnt++]=i;
        }
        else
        {
            //Calculating phi
            if (lp[i] == lp[i / lp[i]])
                phi[i] = phi[i / lp[i]] * lp[i];
            else
                phi[i] = phi[i / lp[i]] * (lp[i] - 1);
        }
        for (int j = 0; j < cnt && pr[j] <= lp[i] && i * pr[j] <= Lim; ++j)
            lp[i * pr[j]] = pr[j];
    }
}

