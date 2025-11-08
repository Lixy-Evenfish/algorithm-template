#include<bits/stdc++.h>
#define int long long

using namespace std;
void solve(){
    int n;
    vector<vector<int>> dis(n+1,vector<int>(n+1,1e18));
	auto floyd = [&](){
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= n; j ++)
				for(int k = 1; k <= n; k ++){
					dis[j][k] = min(dis[j][k],dis[j][i] + dis[i][k]);
				}
	};
	floyd();
}