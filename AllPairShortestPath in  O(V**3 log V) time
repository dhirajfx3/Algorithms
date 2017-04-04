#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
class AllPairShortestPath2
{
	/*
	All pairs shortest path by the fact that path of at most M edges must be 
	path of(ceil(M/2))edges + another path of at most (ceil(M/2)) edges
	Time complexity :O((V**3)lgV)
	Space complexity :O(V*V)
	*/
	vector<vector<long long> > W;
	int SIZE;
public:
	AllPairShortestPath2(int N = 0) :W(N, vector<long long>(N, 1e9)), SIZE(N)
	{
		for (int i = 0; i < SIZE; i++)
			W[i][i] = 0;
	}
	void add(int u, int v, long long w) // 0-indexed
	{
		W[u][v] = min(w, W[u][v]);
	}
	void run()
	{
		for (int p = 1; p < SIZE ; p*=2)
			for (int i = 0; i < SIZE; i++)
				for (int j = 0; j < SIZE; j++)
					for (int k = 0; k < SIZE; k++)
						W[i][j] = min(W[i][j], W[j][k] + W[i][k]);
	}
	void printsd(int Source)                     // 0-indexed
	{
		for (int i = 0; i < SIZE; i++)
		{
			if (i != Source)
			{
				if (W[Source][i] == 1e9)
					printf("-1 ");
				else
					printf("%lld ", W[Source][i]);
			}
		}
		printf("\n");
	}
};
