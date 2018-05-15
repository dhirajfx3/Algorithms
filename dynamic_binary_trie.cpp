#define MaxLen 30
#define MaxN 100000
int SUM[MaxN*MaxLen+5],L[MaxN*MaxLen+5],R[MaxN*MaxLen+5];
int Next=1,root=1;
class Trie
{
	int Con[MaxLen];
	int Con2[MaxLen];
public:
	Trie()
	{	
			add(x);
      erase(x);
      find_value_to_minimize(x);
	}
	// 0 left,1-right
	void add(int val)
	{
		int c=Root;
		convert(Con,val);
		SUM[c]++;
		for(int i=0;i<MaxLen;i++)
		{
			if(Con[i]==0)
			{
				if(L[c]==0)
					L[c]=++Next;
				c=L[c];
			}
			else
			{
				if(R[c]==0)
					R[c]=++Next;
				c=R[c];
			}
			SUM[c]++;
		}
	}
	long long find_val_to_minimize(int val)
	{
		convert(Con2,val);
		int c=root;
		long long ans=0;
		for(int i=0;i<MaxLen;i++)
		{
			if(Con2[i]==0)
			{
				if(L[c] && SUM[L[c]])
				{
					c=L[c];
				}
				else
					c=R[c],ans^=1<<(29-i);
			}
			else
			{
				if(R[c] && SUM[R[c]])
					c=R[c];
				else
					c=L[c],ans^=1<<(29-i);
			}
			--SUM[c];
		}
		return ans;
	}
  void erase(int val)
  {
    convert(Con2,val);
		int c=root;
    SUM[c]--;
		long long ans=0;
		for(int i=0;i<MaxLen;i++)
		{
			if(Con2[i]==0)
					c=L[c];
				else 
					c=R[c];
			--SUM[c];
		}
		return ans;
  }
	void convert(int *X,int value)
	{
		int x=MaxLen-1;
		for(int i=0;i<MaxLen;i++)
		{
			X[x]=value&1;
			value>>=1;
			--x;
		}
	}
};
