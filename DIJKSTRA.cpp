#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
vector<vector<int> > adj, W;
vector<int> sd;
int SIZE;
struct cmp
{
	bool operator()(const int &p, const int &q)const
	{
		if (sd[p] < sd[q])
			return true;
		else
			if (sd[p] == sd[q])
				return p < q;
		return false;
	}
};
class DIJKSTRA
{
public:
	bool add(int u, int v, int w = 1)
	{
		adj[u].push_back(v), W[u].push_back(w);
		adj[v].push_back(u), W[v].push_back(w);
		return true;
	}
	void run(int Source) // Zero indexed
	{
		sd[Source] = 0;
		set<int, cmp> S;
		S.insert(Source);
		while (!S.empty())
		{
			int P = *S.begin();
			S.erase(S.begin());
			for (int i = 0; i<adj[P].size(); i++)
			{
				if (sd[adj[P][i]]>sd[P] + W[P][i])
				{
					S.erase(adj[P][i]);
					sd[adj[P][i]] = sd[P] + W[P][i];
					S.insert(adj[P][i]);
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
				cout << ((sd[i] == 1e9) ? -1 : sd[i]) << " ";
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
