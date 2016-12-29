#include<vector>
using namespace std;
template<typename T>
class BIT
{
	int N;
	vector<T> v;
public:
	BIT(int X):N(X),v(X+1){}
	void update(T value,int pos)
	{
		pos++;
		while(pos<=N)
		{
			v[pos]+=value;
			pos=pos+(pos&(-pos));
		}
	}
	T get(int L,int R ) // get is 0 indexed query
	{
		T obj=v[0];
		++L,++R;
		while(R>0)
		{
			obj=obj+v[R];
			R=R-(R&(-R));
		}
		while(L>0)
		{
			obj=obj-v[L];
			L=L-(L&(-L));
		}
		return obj;
	}
};
