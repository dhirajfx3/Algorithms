#include<deque>
#include<vector>
#include<algorithm>
using namespace std;
class MaxFlow
{
	vector<vector<int> > cf, adj2, I_val;
	vector<int> visited, parent, i_val;
	int N, id, S, T;
public:
	MaxFlow(int n) :N(n),  cf(n), visited(n, false),parent(n), id(0), I_val(n), i_val(n), adj2(n)
	{
	}
	void add(int u, int v, int w)
	{
		I_val[u].push_back(adj2[v].size());
		I_val[v].push_back(adj2[u].size());
		adj2[u].push_back(v), cf[u].push_back(w);
		adj2[v].push_back(u), cf[v].push_back(0);
	}
	int path()
	{
		deque<int> Q, Min;
		Q.push_back(S);
		Min.push_back(1e9);
		visited[S] = id;
		int x, y;
		while (!Q.empty())
		{
			x = Q.front();
			y = Min.front();
			Min.pop_front();
			Q.pop_front();
			for (int i = 0; i<cf[x].size(); i++)
			{
				if (cf[x][i] && visited[adj2[x][i]] != id)
				{
					parent[adj2[x][i]] = x;
					i_val[adj2[x][i]] = i;
					visited[adj2[x][i]] = id;
					Min.push_back(min(y, cf[x][i]));
					Q.push_back(adj2[x][i]);
					if (adj2[x][i] == T)
						return Min.back();
				}
			}
		}
		return 0;
	}
	int max_flow(int s, int t) // 0 indexed
	{
		S = s, T = t; int cmin = 0, A = 0;
		int u = s, v = t, x;
		id = 1;
		for (cmin = path(); cmin != 0; cmin = path())
		{
			v = t;
			while (v != s)
			{
				u = parent[v];
				x = i_val[v];
				cf[u][x] -= cmin;
				cf[v][I_val[u][x]] += cmin;
				v = u;
			}
			++id;
			A += cmin;
		}
		return A;
	}
};
