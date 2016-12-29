#include<vector>
#include<algorithm>
using namespace std;
struct edge
{
	int u, v;
	long long w;
	edge(int p=0,int q=0,long long r=0):u(p),v(q),w(r){}
	bool operator<( const edge &v2)const
	{
		return w > v2.w;
	}
};
class PRIM_s
{
	/*
	In Prim's algorithm the safe edge is added one by one while its running time is O(ElgE)
	*/
	vector<bool> inQ;
	vector<edge> heap;
	vector<vector<int> > adj, adjW;
public:
	PRIM_s(int n = 0):inQ(n),adj(n),adjW(n){}
	long long Prims()
	{
		edge tmp;
		int u;
		long long A = 0;
		for (int i = 0; i < adj[0].size(); i++)
		{
			tmp.u = 0, tmp.v = adj[0][i], tmp.w = adjW[0][i];
			heap.push_back(tmp);
			push_heap(heap.begin(), heap.end());
		}
		inQ[0] = true;
		for(int z=0;z<adj.size()-1;z++)
		{
			tmp = heap.front();
			while (inQ[tmp.v])
			{
				pop_heap(heap.begin(), heap.end());
				heap.pop_back();
				tmp = heap.front();
			}
			inQ[tmp.v] = true;
			pop_heap(heap.begin(), heap.end());
			heap.pop_back();
			A += tmp.w;
			u = tmp.v;
			tmp.u = u;
			for (int i = 0; i < adj[u].size(); i++)
			{
				if (!inQ[adj[u][i]])
				{
					tmp.v = adj[u][i], tmp.w = adjW[u][i];
					heap.push_back(tmp);
					push_heap(heap.begin(), heap.end());
				}
			}
		}
		return A;
	}
	bool add(int u, int v, long long w)
	{
		adj[u].push_back(v);
		adjW[u].push_back(w);
		adj[v].push_back(u);
		adjW[v].push_back(w);
		return true;
	}
};
