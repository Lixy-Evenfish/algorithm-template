#include<bits/stdc++.h>
#define int long long
using namespace std;

vector<array<int,32>> f(n+1);
auto init = [&]()
{
	for (int j = 0; j <= 31; j ++ )
		for (int i = 1; i + (1ll << j) - 1 <= n; i ++ )
			if (!j) f[i][j] = a[i];
	else f[i][j] = max(f[i][j - 1], f[i + (1ll << (j - 1))][j - 1]);
};
auto query = [&](int l, int r) 
{
	int k = __lg(r - l + 1);
	return max(f[l][k], f[r - (1 << k) + 1][k]);
};
init();
