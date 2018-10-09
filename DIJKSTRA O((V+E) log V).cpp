#include <cstdio>
// Time complexity: O((V+E) log V )
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#define ve vector
using namespace std;
int SIZE;
class DIJKSTRA
{
	ve<ve<pair<int,int>>> adj;
        ve<long long> sd;
public:
	bool add(int u, int v, int w = 1)
	{
		adj[u].push_back({v,w}) ;
		adj[v].push_back({u,w})
		return true;
	}
	void run(int Source) // Zero indexed
	{
		sd[Source] = 0;
		set<pair<long long,int>> S;
		S.insert({0,Source});
		ve<bool> inq(adj.resize());
		while (!S.empty())
		{
			auto P = *S.begin();
			S.erase(S.begin());
			inq[P.second]=true;
			for (auto &x:adj[P.second])
			{
				if (!inq[x.first] && sd[x.first]> x.second + P.first)
				{
					S.erase({sd[x.first],x.first});
					sd[x.first] = x.second+P.first;
					S.insert({sd[x.first],x.first});
				}
			}
		}
		return;
	}
	void printsd(int y)
	{
		run(y);
		for (int i = 0; i<sd.size(); i++)
			if (i != y)
				cout << ((sd[i] == 1e18) ? -1 : sd[i]) << " ";
		cout << endl;
		return;
	}
};
void solve()
{
	int N, M, u, v, w;
	scanf("%d%d", &N, &M);
	DIJKSTRA B;
	SIZE = N;
	adj = vector<vector<int > >(N);
	W = vector<vector<int> >(N);
	sd = vector<int>(N, 1e9);
	for (int i = 0; i<M; i++)
	{
		scanf("%d%d%d", &u, &v, &w);
		B.add(u - 1, v - 1, w);
	}
	scanf("%d", &N);
	B.printsd(N - 1);
	return;
}
int main()
{
	int T = 1;
	scanf("%d", &T);
	while (T--)
	{
		solve();
	}
	return 0;
}
