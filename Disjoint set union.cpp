#include<vector>
using namespace std;
class DISJ
{
	/*
	Super Linear time:O(n.a(n)) ( amortized )
	[ rank union + path compression ]
	*/
	vector<int> rank, parent;
	int SIZE;
public:
	DISJ(int N) :SIZE(N), rank(N, 0), parent(N)
	{
		for (int i = 0; i<N; i++)
			parent[i] = i, rank[i] = 0;
	}
	int find_set(int x)
	{
		if (parent[x] == x)    // root node check
			return x;
		parent[x] = find_set(parent[x]); // path compression
		return parent[x];
	}
	void link(int x, int y)
	{
		if (rank[x] == rank[y])
		{
			rank[x]++;
			parent[y] = x;
			return;
		}
		if (rank[x]<rank[y])
			parent[x] = y;
		else
			parent[y] = x;
	}
	void unite(int x, int y)
	{
		x = find_set(x);
		y = find_set(y);
		if (x != y)
			link(x, y);
	}
	bool same_set(int x, int y)
	{
		return (find_set(x) == find_set(y));
	}
	/* Reference : CLRS 3rd edition 21st chapter Data Structure for Disjoint sets */
};
