#include<vector>
#include<algorithm>
#include<cstdio>
using namespace std;
class FloydWarshall
{
	/*
	All pair shortest path by Floyd-Warshall aprroach
	Using the fact that if intermediate vertices are in the set [1,k] then,
	shortest path W[i][j] for some i,j is
	min ( (sp i to k and rest of v(s) in [1,k-1]) + sp from k to j and rest of v(s) in [1,k-1] ).
	So Here we calculate the sp for i-j with building set for [1,k] with k starting from l and 
	ending to vertex count SIZE
	*/
	vector<vector<long long> > W;
	int SIZE;
public:
	FloydWarshall(int N = 0) :W(N, vector<long long>(N, 1e18)), SIZE(N)
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
		for (int k = 0; k < SIZE; k++)
			for (int i = 0; i < SIZE; i++)
				for (int j = 0; j < SIZE; j++)
					W[i][j] = min(W[i][j], W[i][k] + W[k][j]);
	}
	void printsd(int Source)                     // 0-indexed
	{
		for (int i = 0; i < SIZE; i++)
		{
			if (i != Source)
			{
				if (W[Source][i]>5e17)
					printf("-1 ");
				else
					printf("%lld ", W[Source][i]);
			}
		}
		printf("\n");
	}
};
