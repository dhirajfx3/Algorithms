#include<algorithm>
#include<vector>
using namespace std;
class KrukshalMST :private DISJ  // class DISJ from disjoint set union.cpp
{
public:
	vector<int> W, U, V, sorted_order;
	int N, M;     // number of vertex N , edge count M 

	KrukshalMST(int n, int m) :N(n), M(m), DISJ(n), W(m), U(m), V(m), sorted_order(m)
	{
		for (int i = 0; i<M; i++)
		{
			cin >> W[i] >> U[i] >> V[i];
			sorted_order[i] = i;
		}
	}
	void add(int wi, int ui, int vi)
	{
		W.push_back(wi);
		U.push_back(ui);
		V.push_back(vi);
		sorted_order.push_back(M);
		++M;
	}
	bool operator() (const int &x,const int &y) const
	{
		return W[x] < W[y];
	}
	int build_MST()
	{
		int A = 0;
		sort(sorted_order.begin(), sorted_order.end(),*this);
		for (int i = 0; i<M; i++)
		{
			if (!same_set(U[sorted_order[i]], V[sorted_order[i]]))
			{
				A += W[sorted_order[i]];
				unite(U[sorted_order[i]], V[sorted_order[i]]);
			}
		}
		return A;
	}
};
