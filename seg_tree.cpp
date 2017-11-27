class seg_tree
{
	ve<int> tree;
	ve<int> lazy;
	int n;
	inline int get_size(int R)
	{
		R--;
		int Z=1;
		while(R)
		{
			Z<<=1;
			R>>=1;
		}
		return Z*2;
	}
public:
	void construct(vector<int> &v)
	{
		tree.resize(get_size(v.size()));
		lazy=tree;
		n=v.size()-1;
		make_tree(v,0,v.size()-1,1);
	}
	void make_tree(vector<int> &v,int L,int R,int curr)
	{
		if(L==R)
		{
			tree[curr]=v[L];
			return ;
		}
		int mid=(L+R)/2;
		make_tree(v,L,mid,2*curr);
		make_tree(v,mid+1,R,2*curr+1);
		tree[curr]=(tree[2*curr]+tree[2*curr+1]);
		return ;
	}
	int find_max(int l,int r)
	{
		return find_max2(l,r,0,n,1);
	}
	int find_max2(int l,int r,int L,int R,int curr)
	{
		if(r<L || l>R)
			return 0;
		if(L>=l && R<=r)
			return tree[curr];
		int c=curr;
		if(lazy[c])
		{
			update(L,R,curr<<1,L,(L+R)>>1);
			update(L,R,(curr<<1)+1,((L+R)>>1)+1,R);
			lazy[c]=0;
		}
		return (find_max2(l,r,L,(L+R)/2,2*curr)+find_max2(l,r,(L+R)/2+1,R,2*curr+1));
	}
	void update(int l,int r)
	{
		update(l,r,1,0,n);
	}
	void update(int l,int r,int c,int L,int R)
	{
		int curr=c;
		if(r<L || l>R)
			return ;
		if(L>=l && R<=r)
		{
			lazy[c]^=1;
			tree[c]=R-L+1-tree[c];
			return;
		}
		if(lazy[c])
		{
			update(L,R,curr<<1,L,(L+R)>>1);
		update(L,R,(curr<<1)+1,((L+R)>>1)+1,R);
			lazy[c]=0;
		}
		update(l,r,curr<<1,L,(L+R)>>1);
		update(l,r,(curr<<1)+1,((L+R)>>1)+1,R);
		tree[curr]=(tree[2*curr]+tree[2*curr+1]);
		return;
	}
};
