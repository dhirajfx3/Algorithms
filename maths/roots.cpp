int fast_mod(long long x,int expo,long long pri)
{
	if(expo==0)
		return 1%pri;
	int ans=1;
	while(expo)
	{
		if(expo&1)
			ans= (ans*x)%pri;
		expo>>=1;
		x=(x*x)%pri;
	}
	return ans;
}
// p is prime
bool is_primitive(int x,int p)
{
	if(p==1)
		return true;
	int j=2,q=p-1;
	long long alf=4;
	while(alf<=q)
	{
		int k=0;
		while(q%j==0)
		{
			q/=j;
			++k;
		}
		if(k)
		{
			if(fast_mod(x,(p-1)/j,p)==1)
				return false;
		}
		alf+=(j<<1)+1;
		++j;
	}
	if(q>1)
	{
		if(fast_mod(x,(p-1)/j,p)==1)
			return false;
	}
	return true;
}
// first primitive modulo pr greater than x [20% numbers are atleast primitive roots]
int next_primitive(int x,int pr)
{
	for(int i=x+1;i<pr;i++)
	{
		if(is_primitive(i,pr))
			return i;
	}
	return 1;
}
