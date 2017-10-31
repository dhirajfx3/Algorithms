#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <time.h>
#include <ctime>
#include <sys/time.h>
#include<vector>

using namespace std;

void selectionsort(vector<int> &a,int n)
{
    for(int i=0;i<n-1;i++)
    {
        int pos=i,min=a[i];
        for(int j=i;j<n;j++)
        {
            if(a[i]>min)
            {
                min=a[i];
                pos=i;
            }
        }
        int t=a[i];
        a[i]=a[pos];
        a[pos]=t;
    }
}

bool linearsearch(vector<int> &a,int n,int key)
{
    for(int i=0;i<n;i++)
        if(key==a[i])
        return true;
    return false;
}

bool binarysearch(vector<int> &a,int n,int key)
{
    int l=0,r=n-1,mid;
    mid=(l+r)/2;
    while(l<=r)
    {
        mid=(l+r)/2;
        if(a[mid]==key)
            return true;
        else{
            if(a[mid]>key)
                r=mid-1;
            else
                l=mid+1;
        }
    }
    return false;
}
void mer(vector<int> &a,int l,int mid,int r);
void mergesort(vector<int> &a,int l,int r)
{
    if(l>=r)
        return;
    else
    {
        int mid=(l+r)/2;
        mergesort(a,l,mid);
        mergesort(a,mid+1,r);
        mer(a,l,mid+1,r);
    }
}
void mer(vector<int> &a,int l,int mid,int r)
{
    int size=r-l+1;
    int b[size];
    int i=l,j=mid,k=0;
    while(i<=mid && j<=r)
    {
        if(a[i]>a[j])
            b[k++]=a[j++];
        else
            b[k++]=a[i++];
    }
        if(i<=mid)
        {
            for(;i<=mid;i++)
                b[k++]=a[i];
        }
        else
            for(;j<=r;j++)
                b[k++]=a[j];

        for(int i=l;i<=r;i++)
            a[i]=b[i-l];
}

int main()
{
    int e[]={1000,5000,10000,30000,40000,50000,70000,100000,400000,500000,700000,900000,1000000,2000000,4000000,5000000,7000000,10000000,30000000,70000000,100000000};
    for(int p=0;p<sizeof(e)/sizeof(int);p++)
    {
        int i=e[p];
        vector<int> a;
        for(int j=0;j<i;j++)
            a.push_back(j);
    //cout << "hello" << endl;
        std::srand(unsigned(std::time(0)));

 //   auto engine = std::default_random_engine{};
        std::random_shuffle ( a.begin(), a.end() );

        clock_t startTime = clock();
        linearsearch(a,i,a[i-1]);
   // cout << linearsearch(a,i,a[i-1]) << " " <<endl;
        double lsearch=double( clock() - startTime )/CLOCKS_PER_SEC;
//cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;
        startTime = clock();
        mergesort(a,0,i-1);
        double mergeso=double( clock() - startTime )/CLOCKS_PER_SEC;

   /* startTime = clock();
  //  cout<< startTime << " -start time"<<endl;
    selectionsort(a,i);
  //  cout<< " search complete"<<endl;
    double selectsort=double( clock() - startTime )/CLOCKS_PER_SEC;*/

        //Binary earch
        startTime = clock();
        binarysearch(a,i,a[i-1]);
   //cout <<  binarysearch(a,i,a[i-1])<< " "<<endl;
        double bsearch=double( clock() - startTime )/CLOCKS_PER_SEC;
        cout << "n= " << i << " O(n) = "<<lsearch <</* " O(n^2) = " <<selectsort << */" O(log n) = " << bsearch << "O(nlog n) = "<<mergeso <<endl;
    }
}
