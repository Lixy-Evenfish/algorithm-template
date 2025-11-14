#include<bits/stdc++.h>
using namespace std;

struct Hash
{
	vector<int> h1,h2,p1,p2;
	int n;
	const int P = 13331;
	const int mod1 = 998244353,mod2 = 998244853;
	Hash (string &s)
	{
	    //多个字符串哈希，p1，p2可以只算一次，拆散了用，就行
		n = s.size();
		h1.resize(n+1);
		h2.resize(n+1);
		p1.resize(n+1);
		p2.resize(n+1);
		p1[0] = p2[0]= h1[0] = h2[0] = 1;
		for (int i = 1 ; i <= n; i ++) {
			h1[i] = (1ll*h1[i - 1] * P + s[i]) % mod1;
			h2[i] = (1ll*h2[i - 1] * P + s[i]) % mod2;
			p1[i] = (1ll*p1[i - 1] * P) % mod1;
			p2[i] = (1ll*p2[i - 1] * P) % mod2;
		}
	}
	pair<int,int> check(int l,int r)
	{
		return {(h1[r] - (1ll*h1[l - 1] * p1[r - l + 1]) % mod1 + mod1) % mod1,
			(h2[r] - (1ll * h2[l - 1] * p2[r - l + 1]) % mod2 + mod2) % mod2};
	}
	
};