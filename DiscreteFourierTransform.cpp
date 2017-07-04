template<typename my_type>
class DiscreteFourierTransform
{
	int N;
	int revised()
	{
		int temp = N - 1;
		int ans = 1;
		while (temp)
		{
			ans *= 2;
			temp >>= 1;
		}
		return ans;
	}
public:
	ve<num> DFT(const ve<my_type> &v)
	{
		int R = revised();
		ve<num> a(R);
		for (int i = 0; i<N && i<v.size(); i++)
		{
			a[i].re = v[i];
		}
		return DFT(a);
	}
	ve<num> DFT(const ve<num> &a)
	{
		int n = a.size();
		if (n == 1)
			return a;
		num wn(2 * pi / n);
		num w(1, 0);
		ve<num> a0, a1;
		for (int i = 0; i<n;)
		{
			a0.pb(a[i++]);
			a1.pb(a[i++]);
		}
		ve<num> y0 = DFT(a0);
		ve<num> y1 = DFT(a1);
		ve<num> y(n);
		int n_2 = n / 2;
		for (int k = 0; k<n_2; k++)
		{
			y[k] = y0[k] + w*y1[k];
			y[k + n_2] = y0[k] - w*y1[k];
			w = w*wn;
		}
		return y;
	}
	ve<num> inv_DFT(const ve<num> &y)
	{
		int n = y.size();
		if (n == 1)
			return y;
		num wn(2 * pi / n);
		wn.im = -wn.im;
		num w(1, 0);
		ve<num> y0, y1;
		for (int i = 0; i<n;)
		{
			y0.pb(y[i++]);
			y1.pb(y[i++]);
		}
		ve<num> a0 = inv_DFT(y0);
		ve<num> a1 = inv_DFT(y1);
		ve<num> a(n);
		int n_2 = n / 2;
		for (int k = 0; k<n_2; k++)
		{
			a[k] = (a0[k] + w*a1[k]);
			a[k + n_2] = (a0[k] - w*a1[k]);
			w = w*wn;
		}
		return a;
	}
	ve<my_type> poly_mult(const ve<my_type> &a, const ve<my_type> &b)
	{
		N = a.size() + b.size();
		int val = revised();
		ve<num> R(inv_DFT(DFT(a)*DFT(b)));
		for (auto &x : R)
			x.re /= val, x.im /= val;
		ve<long long> Res;
		for (int i = 0; i < N - 1; i++)
			Res.pb(static_cast<long long>(R[i].re + 0.5));
		return Res;
	}
};
DiscreteFourierTransform<int> D;
