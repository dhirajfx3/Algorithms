#include <iostream>
#include<vector>
#include<climits>
using namespace std;
int max1(int a, int b) { return (a > b)? a : b; }

struct data{
    int wt;
    int val;
};
int** knapSack(int W, vector < data > d)
{
   int** mat = 0;
   mat = new int*[d.size()+1];
   for(int i=0;i<=d.size();i++)
   {
       mat[i] = new int[W+1];
       for(int w=0;w<=W;w++)
       {
        if (i == 0 || w == 0)
            mat[i][w]=0;
        else if (d[i-1].wt <= W)
            mat[i][w] = max1( d[i-1].val + mat[i-1][w-d[i-1].wt],mat[i-1][w]);
        else
            mat[i][w] = mat[i-1][w];
       }
   }
   return mat;
}
int main()
{
    int n;
    cin>>n;
    int W;
    cin>>W;
    vector < data > d(n);
    for(int i=0;i<n;i++)
    {
        cin >> d[i].val >> d[i].wt;
    }
    
    int** mat = knapSack(W , d );
    int i=d.size();
    int w=W;
    /*while (mat[i][w]!=0){
    if(mat[i][w]==mat[i-1][w] || w<d[i-1].wt){
            i--;
            }
    else{
            cout<<d[i-1].val<<"  extracted  ";
            w=w-d[i-1].wt;
            i--;
            cout<<"rem wt. "<<w<<endl;

    }
    }*/
    cout<<"\nMax value :"<<mat[d.size()][W] << "\n";
    return 0;
}
