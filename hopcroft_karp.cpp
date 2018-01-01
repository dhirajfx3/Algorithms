#include <vector>
#define ve vector
using namespace std;
class hopcroft_karp
{
	// everything 0 indexed
	ve<ve<int> > adjX[2];
	ve<int> visitedX[2];
	ve<int> cmX[2];
	ve<int> Queue;
	int nX[2], marker, Qfill, n;
public:
	void init(int L, int R)
	{
		nX[0] = L;
		nX[1] = R;
		n = L + R;
		Queue.resize(n + 2);
		adjX[0].resize(L);
		adjX[1].resize(R);
		visitedX[0].resize(L);
		visitedX[1].resize(R);
		cmX[0].resize(L, -1);
		cmX[1].resize(R, -1);
		Qfill = 0;
		marker = 1;
		init_bfs();
	}
	// Left - Right = 0 - 1
	void add(int a, int b)
	{
		adjX[0][a].push_back(b);
		adjX[1][b].push_back(a);
	}
 
	/*
	Algorithm:
	Keep augmenting until no more augmentation exists
	*/
	// Returns the matching
	ve<pair<int, int> >  max_matching()
	{
		while (aug_make())
		{
			++rmv;
			aug_do();
			clean();
		}
		ve<pair<int, int>> matching;
		for (int i = 0; i<nX[0]; i++)
		{
			if (cmX[0][i] != -1)
				matching.push_back({ i,cmX[0][i] });
		}
		return matching;
	}
	// Bfs structure
	ve<ve<int> > adj2[2];
	ve<int> aug, rem[2];
	int aug_fill, rmv;
	void init_bfs()
	{
		adj2[0].resize(nX[0]);
		adj2[1].resize(nX[1]);
		rem[0].resize(nX[0]);
		rem[1].resize(nX[1]);
		aug_fill = 0;
		aug.resize(nX[1]);
		rmv = 1;
	}
	bool aug_make()
	{
		int Ql = 0, Qr = 0;
		aug_fill = 0;
		++marker;
		for (int i = 0; i<nX[0]; i++)
		{
			if (cmX[0][i] == -1)
			{
				Queue[Qr++] = i;
				visitedX[0][i] = marker;
			}
		}
		int turn = 1;
    // (optional condition in while) aug_fill == 0
		while (Ql != Qr && aug_fill==0)
		{
			if (turn)
			{
				int Temp = Qr;
				while (Ql != Temp)
				{
					int curr = Queue[Ql++];
					for (auto &x : adjX[0][curr])
					{
						if (cmX[0][curr] != x)
						{
							adj2[1][x].push_back(curr);
 
							if (cmX[1][x] == -1 && visitedX[1][x] != marker)
							{
								aug[aug_fill++] = x;
							}
							if (visitedX[1][x] != marker && cmX[1][x] != -1)
							{
								Queue[Qr++] = x;
								Qr = Qr>n + 1 ? 0 : Qr;
							}
							visitedX[1][x] = marker;
						}
					}
					Ql = Ql>n + 1 ? 0 : Ql;
				}
			}
			else
			{
				int Temp = Qr;
				while (Ql != Temp)
				{
					int curr = Queue[Ql++];
					adj2[0][cmX[1][curr]].push_back(curr);
					if (visitedX[0][cmX[1][curr]] != marker)
					{
						Queue[Qr++] = cmX[1][curr];
						visitedX[0][cmX[1][curr]] = marker;
					}
					Qr = Qr>n + 1 ? 0 : Qr;
					Ql = Ql>n + 1 ? 0 : Ql;
				}
			}
			turn = !turn;
		}
		return aug_fill;
	}
	void aug_do()
	{
		for (int i = 0; i<aug_fill; i++)
		{
			++marker;
			if (cmX[1][aug[i]] == -1)
				dfs(aug[i], 1);
		}
	}
	bool dfs(int c, int is_right)
	{
		if (!is_right && cmX[0][c] == -1)
		{
			rem[is_right][c] = rmv;
			return true;
		}
		visitedX[is_right][c] = marker;
		for (auto &x : adj2[is_right][c])
		{
			if (visitedX[!is_right][x] != marker && rem[!is_right][x] != rmv)
			{
				if (dfs(x, !is_right))
				{
					if (is_right)
					{
						cmX[1][c] = x;
						cmX[0][x] = c;
					}
					rem[is_right][c] = rmv;
					return true;
				}
			}
		}
		return false;
	}
		void clean()
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < nX[i]; j++)
			{
				adj2[i][j].clear();
			}
		}
	}
};
// faster implementation at https://sites.google.com/site/indy256/algo_cpp/hopcroft_karp
