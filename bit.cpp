#include<vector>
#define ve vector
using namespace std;
class bit
{
	// 1 based indexing only
	ve<int> tree;
	int n;
	public:
	void construct(int x)
	{
		tree.resize(x+1);
		n=x;
	}
	void add(int pos,int val)
	{
		while(pos<=n)
		{
			tree[pos]+=val;
			pos=pos+(pos&(-pos));	
		}
	}
	int sum(int pos)
	{
		int s=0;
		while(pos>0)
		{
			s=s+tree[pos];
			pos=pos-(pos&(-pos));
		}
		return s;
	}
};
