#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class BellmanFord
{
	/*
	Single source shortest path 
	Complexity : O(VE) (by aggregate analysis)
	*/
	vector<int> u,v,w,sd; // directed edges - for undirected uncomment coded lines
	int Vertex_count;
public:
	BellmanFord(int N=0):Vertex_count(N),sd(N,1e9){}
	bool run(int Source)
	{
		sd[Source]=0;
		for(int i=0;i<Vertex_count-1;i++)
			for(int i = 0 ; i < v.size();i++)
				sd[v[i]]=min(sd[v[i]],sd[u[i]]+w[i]);
		for(int i=0;i<v.size();i++)
			if(sd[v[i]]<sd[u[i]]+w[i])
				return false;
		return true;
	}
	bool add(int U,int V,int W=6) // Zero indexed call
	{
		u.push_back(U),v.push_back(V),w.push_back(W);
		//v.push_back(U),u.push_back(V),w.push_back(W);
		return true;
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
