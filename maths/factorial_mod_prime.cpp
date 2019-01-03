#define Z 1000000
class fact_mod
{
  int fact[ Z + 1 ], invfact[ Z + 1 ], mod_inv[ Z + 1 ] ;
public:
  fact_mod()
  {
    fact[0] = 1;
    invfact[0] = 1;
    long long P=mod;
    mod_inv[1] = 1;
    mod_inv[0]=0;
    for (int i = 2; i <= Z; i++) 
    {
      mod_inv[i] = (-(P / i) * mod_inv[P% i]) % P + P;
    }
    for (long long int i = 1; i <= Z; i++)
    {
      fact[i] = (fact[i - 1] * i) % P;
      invfact[i] = (invfact[i - 1] * (1LL * mod_inv[i])) % P;
    }
  }
  long long fac(int k)
  {
	  return fact[k];
  }
  long long inv_fac(int k)
  {
	  return invfact[k];
  }
  long long inv(int k)
  {
	  return mod_inv[k];
  }
  long long ncr(int n, int k)
  {
    if (k > n)
      return 0;
    long long val = fact[n] * (((invfact[n - k] * 1LL)*invfact[k]) % mod) % mod;
    return val;
  }
};
