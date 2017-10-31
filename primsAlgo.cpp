#include<bits/stdc++.h>
#define ll long long
#define rep(i,a,b) for(int i=a;i<b;i++)
#define vi std::vector<int>
#define pb push_back
#define pii pair<int, int>
#define F first
#define S second

#define si set<int>
#define mii map<int, int>
using namespace std;
class elem
{
	public:
	    int par;
	    int key;
	    int val;
	    elem(int a, int b, int c)
	    {
		par = a;
		key = b;
		val = c;
	    }
};
bool operator<(const elem &lhs, const elem &rhs)
{
    return lhs.val > rhs.val;
}
vector<pii> g[100];
int n, m;
int cov[100];
int num;
priority_queue< elem, vector<elem> > p;


void PrimMST()
{
    cin >> n >> m;
    rep(i,0,m)
    {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back(make_pair(b, c));
        g[b].push_back(make_pair(a, c));
    }
    p.push(elem(0, 1, 0));
    while(num < n)
    {
        elem e = p.top();
        p.pop();
        if(cov[e.key] == 1)
            continue;
        ++num;
        cov[e.key] = 1;
        int par = e.par;
        int nod = e.key;
        int val = e.val;
        if(num > 1)
     	    cout << e.par << " " << e.key << endl;
        rep(i,0,g[nod].size())
        {
            pii a = g[nod][i];
            p.push(elem(e.key, a.F, e.val+a.S));
        }
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    //cin >> t;
    rep(j,1,t+1){
        PrimMST();
    }

}

