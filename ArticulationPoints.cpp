#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Graph
{
	int n;
	vector<vector<int> > adj;
	vector<int> level, be_lvl;
	vector<int> visited, ap;
	int var;
	void dfs(int u, int p = -1, int lvl = 0)
	{
		visited[u] = true;
		level[u] = lvl;
		be_lvl[u] = lvl;
		bool is_leaf = true;
		for (auto &x : adj[u])
		{

			if (!visited[x])
			{
				is_leaf = false;
				dfs(x, u, lvl + 1);
				be_lvl[u] = min(be_lvl[x], be_lvl[u]);
				if (u == 0)
					++var;
			}
			else if (x != p)
				be_lvl[u] = min(level[x], be_lvl[u]);
			if (be_lvl[x] >= level[u] && u != 0)
			{
				ap[u] = true;
			}
		}
		if (is_leaf == true)
			ap[u] = false;
	}
public:
	Graph(int n, int m) :n(n), adj(n), level(n), be_lvl(n), visited(n), ap(n)
	{
		var = 0;
		for (int i = 0; i<m; i++)
		{
			int u, v;
			cin >> u >> v;
			--u, --v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		dfs(0);
	}

};
int main()
{
	int n, m;
	cin >> n >> m;
	new Graph(n, m);
	return 0;
}
