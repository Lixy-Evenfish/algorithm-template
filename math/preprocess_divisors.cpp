#include<bits/stdc++.h>
#define int long long
using namespace std;

vector<int> flat,start;

const int N = 1001000;
void init(){	
	vector<int> cnt(N + 1, 0);
	for(int i = 1; i <= N; i ++)
		for(int j = i; j <= N; j += i)
			cnt[j] ++;
	
	start.assign(N + 2, 0);
	for(int k = 1; k <= N; k ++)
		start[k + 1] = start[k] + cnt[k];
	flat.assign(start[N + 1], 0);
	
	vector<int> p = start;
	for(int i = 1; i <= N; i ++){
		for(int j = i; j <= N; j += i){
			flat[ p[j]++ ] = i;
		}
	}
}
void solve(){
    int val;
	for(int p = start[val]; p < start[val + 1]; p ++){
		int divisor = flat[p];
		
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	init();
	solve();
	return 0;
}