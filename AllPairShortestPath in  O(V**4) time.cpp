#include<vector>
#include<cstdio>
using namespace std;
class AllPairShortestPath
{
	/*
	All pairs shortest path using fact that path of M edges must have atmost((M-1) + 1)
	Time Complexity : O(V**4)
	Space Complexity :O(V*V)
	*/
	vector<vector<long long> > W, L;
	int SIZE;
public:
	AllPairShortestPath(int N=0):W(N,vector<long long>(N,1e9)),SIZE(N)
	{
		for (int i = 0; i < SIZE; i++)
			W[i][i]=0;
	}
	void add(int u, int v, long long w) // 0-indexed
	{
		W[u][v] = min(w, W[u][v]);
	}
	void run()
	{
		L = W;
		for (int p = 1; p < SIZE - 1; p++)
			for (int i = 0; i < SIZE; i++)
				for (int j = 0; j < SIZE; j++)
					for (int k = 0; k < SIZE; k++)
						L[i][j] = min(L[i][j], W[j][k] + L[i][k]);
	}
	void printsd(int Source)                     // 0-indexed
	{
		for (int i = 0; i < SIZE; i++)
		{
			if (i != Source)
			{
				if (L[Source][i] == 1e9)
					printf("-1 ");
				else
					printf("%lld ", L[Source][i]);
			}
		}
		printf("\n");
	}
};
