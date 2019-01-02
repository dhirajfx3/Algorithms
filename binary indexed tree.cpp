#include<vector>
#define ve vector
using namespace std;
class bit
{
	// 1 based indexing only
	ve<int> tree;
	public:
	void construct(int n)
	{
		tree.resize(n+1);
	}
	void add(int pos,int val)
	{
		while(pos<=n)
		{
			v[pos]+=val;
			pos=pos+(pos&(-pos));
		}
	}
	int sum(int pos)
	{
		int s=0;
		while(pos>0)
		{
			s=s+v[pos];
			pos=pos-(pos&pos);
		}
		return s;
	}
};
