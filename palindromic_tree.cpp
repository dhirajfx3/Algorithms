#include <iostream>
#include <vector>
#include <map>
#include <string>

#define ve vector
#define pb push_back
using namespace std;
class palindrome
{
	string S;
	ve<ve<int> > adj;
	ve<int> suffix_link;
	int curr, pos;
	ve<int> len;
	ve<map<char, int> > edges;
	int size;
public:
	palindrome() :len({ -1,0 }), edges(2), suffix_link({ 0,0 }), size(1)
	{
	}
	void construct(string A)
	{
		pos = 1;
		S = '$';
		S += A;
		curr = 1;
		for (int i = 1; i<S.length(); i++)
		{
			add(S[i]);
			++pos;
		}
	}
	void extend()
	{
		len.pb(0);
		edges.pb(map<char, int>());
		suffix_link.pb(0);
		++size;
  	}
	void add(char c)
	{
		while (c != S[pos - len[curr] - 1] )
		{
			curr = suffix_link[curr];
		}
		if (edges[curr].find(c) != edges[curr].end())
		{
			curr = edges[curr][c]; 
			return;
		}
		extend();
		edges[curr][c] = size;
		len[size] = len[curr] + 2;
		if (len[size] == 1)
		{
			suffix_link[size] = 1;
			curr = size;
			return;
		}
		int temp = suffix_link[curr];
		while (c != S[pos - len[temp] - 1])
		{
			temp = suffix_link[temp];
		}
		suffix_link[size] = edges[temp][c];
		curr = size;
	}
	void print(int node=0,string Z="") // ONLY FOR USER's CONVINIENCE 
	{
		for (auto &x : edges[node])
		{
			if (node == 0)
			{
				cout << x.first << endl;
				print(x.second, x.first + Z);
			}
			else
			{
				cout << x.first + Z + x.first << endl;
				print(x.second, x.first + Z + x.first);
			}
		}
	}
};
int main()
{
	palindrome P;
	P.construct("aaabbbbaaa");
	P.print(1); // even length palindromes
	P.print(0); // odd length palindromes
	return 0;
}
