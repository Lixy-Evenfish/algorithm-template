#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod;
struct Comb{
	int n;
	vector<int> fact,infact;
	Comb(int n1):n(n1),fact(n1+2),infact(n1+2){
		init();
	}
	int qmi(int a,int b)
	{
		int ret = 1;
		while(b)
		{
			if(b & 1) ret = (1ll * ret * a) % mod;
			a = (1ll*a*a) % mod;
			b >>= 1;
		}
		return ret;
	}
	void init()
	{
		fact[0] = infact[0] = 1;
		for(int i = 1; i <= n; i ++)
		{
			fact[i] = (1ll*fact[i-1]*i) % mod;
			infact[i] =(1ll*infact[i-1]*qmi(i,mod-2)) % mod;
			//cout << fact[i] << ' ';
		}
	}
	int C(int a,int b)
	{
		return (((1ll*fact[a]*infact[b])%mod)*infact[a-b]) % mod;
	}
}comb(5e5 + 10);