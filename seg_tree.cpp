/*
Segment tree operations and features :
	1. Find the maximum element in the positions [L,R] in the array of size N in O(logN) time.
	2. Add a constant value to all elements in positions [L,R] in O(logN) time.

See the main() function below for usage.
Be sure to uncomment line if your data cannot fit in 32-bit integers ( > 10^9) 
*/
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
#define ve vector
// uncomment line below if your data cannot fit 32-bit integers ( > 10^9 )
//#define int int64_t 
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
		tree[curr]=max(tree[2*curr],tree[2*curr+1]);
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
			update(L,R,curr<<1,L,(L+R)>>1,lazy[c]);
			update(L,R,(curr<<1)+1,((L+R)>>1)+1,R,lazy[c]);
			lazy[c]=0;
		}
		return max(find_max2(l,r,L,(L+R)/2,2*curr),find_max2(l,r,(L+R)/2+1,R,2*curr+1));
	}
	void update(int l,int r,int val)
	{
		update(l,r,1,0,n,val);
	}
	void update(int l,int r,int c,int L,int R,int val)
	{
		int curr=c;
		if(r<L || l>R)
			return ;
		if(L>=l && R<=r)
		{
			lazy[c]+=val;
			tree[c]+=val;
			return;
		}
		if(lazy[c])
		{
			update(L,R,curr<<1,L,(L+R)>>1,lazy[c]);
			update(L,R,(curr<<1)+1,((L+R)>>1)+1,R,lazy[c]);
			lazy[c]=0;
		}
		update(l,r,curr<<1,L,(L+R)>>1,val);
		update(l,r,(curr<<1)+1,((L+R)>>1)+1,R,val);
		tree[curr]=max(tree[2*curr],tree[2*curr+1]);
		return;
	}
};
#undef int
int main()
{
	
	seg_tree S; // Create a segment tree object
	ve<int> A{1,2,3,4,5};
	// build the segment tree
	S.construct(A);
	cout << S.find_max(0,2) << endl; // output : 3
	// Add 5 to all elements at indices [1,2 and 3] i.e A=[1,7,8,9,5]
	S.update(1,3,5);
	cout << S.find_max(3,4) << endl; // output : 9
	return 0;
}
