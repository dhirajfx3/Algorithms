#include <iostream>
#include <queue>
#include<bits/stdc++.h>
using namespace std;
clock_t st, en;
int V, M;
int G[1000][1000];

bool isBipartite(int src)
{
    
    int colorArr[V];
    for (int i = 0; i < V; ++i)
        colorArr[i] = -1;

    colorArr[src] = 1;

    queue <int> q;
    q.push(src);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; ++v)
        {
            if (G[u][v] && colorArr[v] == -1)
            {
                colorArr[v] = 1 - colorArr[u];
                q.push(v);
            }
	    else if (G[u][v] && colorArr[v] == colorArr[u])
                return false;
        }
    }

    return true;
}

int main()
{
    st = clock();

    cout << "Enter number of vertices: "; cin >> V;
    cout << "Enter number of edges: "; cin >> M;
    //V = M = 1000;	
    cout << "Enter edges:" << endl;
    memset(G, 0, sizeof(G));
    
    for(int i = 0; i < M; i++){
        int a, b;
        //a = (i)%V; b = (i+1)%V;
	cin >> a >> b;
	a--; b--;
	G[a][b] = 1;
	G[b][a] = 1;
    }
    
    isBipartite(0) ? cout << "\nYes,the graph is Bipartite\n" << endl : cout << "\nThe graph is not Bipartite\n" << endl;
    en = clock();
    double cpu_time_used;
    cpu_time_used = ((double) (en - st)) / CLOCKS_PER_SEC;
    cout << "\nThe execution time is : " << cpu_time_used << endl;//
}
