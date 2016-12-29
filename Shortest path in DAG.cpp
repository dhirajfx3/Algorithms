#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;
class DAG_shortest
{
	/*
	Finding single source shortest distance in a directed acyclic graph 
	Complexity : O(V) [top_sort] + O(E) [relaxation(aggregate analysis)] = O(V+E) 
	*/
	vector<int> top_sort,visited,sd;
	vector<vector<int> > adj,W;
	int Vertex_count;
	bool ts;
	void dfs()
	{
		for(int i=0;i<visited.size();i++)
		{
			if(!visited[i])
				visit(i);
		}
	}
	void visit(int v)
	{
		visited[v]=true;
		for(auto &x:adj[v])
			if(!visited[x])
				visit(x);
		top_sort.push_back(v);
	}
public:
	DAG_shortest(int N=0):visited(N),Vertex_count(N),sd(N,1e9),ts(true),adj(N),W(N){}
	void topo_sort()
	{
		/*
		for the purpose of topological sorting 
		*/
		dfs();
		ts=false;
		reverse(top_sort.begin(),top_sort.end());
	}
	bool add(int u,int v,int w=6) 					// Zero indexed call
	{
		adj[u].push_back(v),W[u].push_back(w);
		return true;
	}
	void run(int Source)
	{
		if(ts)						    // check whether the topological sort has been performed
		topo_sort();  					// if not then do it
		for(int i=0;i<sd.size();i++)    // initialising to some large value  
			sd[i]=1e9;
		sd[Source]=0;
		for(auto &x:top_sort)
			for(int i=0;i<adj[x].size();i++)
				sd[adj[x][i]]=min(sd[adj[x][i]],sd[x]+W[x][i]);
	}
	void printsd(int y)
	{
		run(y);
		for(int i=0;i<sd.size();i++)
			if(i!=y)
				cout << ((sd[i]==1e9)?-1:sd[i]) <<" ";
		cout << endl;
	}
};
