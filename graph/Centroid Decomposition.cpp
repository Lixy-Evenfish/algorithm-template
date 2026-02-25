#include<bits/stdc++.h>
#define int long long

using namespace std;

typedef pair<int,int> PII;
void solve(){
	int n;
	cin >> n;
	int tot,root,mi;
	vector<vector<PII>> v(n+1);
	vector<int> siz(n+1),done(n+1);
	
	for(int i = 1; i <= n - 1; i ++){
		int x,y,z;
		cin >> x >> y >> z;
		v[x].push_back({z,y}),v[y].push_back({z,x});
	}
	
	auto getsize = [&](auto &&self,int u,int p) -> void{
		siz[u] = 1;
		for(auto [d,i] : v[u]){
			if(i != p && !done[i]){
				self(self,i,u);
				siz[u] += siz[i];
			}
		}
	};
	
	auto getroot = [&](auto &&self,int u,int p) -> void{
		int mu = tot-siz[u];
		for(auto [d,i] : v[u]){
			if(i != p && !done[i]){
				mu = max(mu,siz[i]);
				self(self,i,u);
			}
		}
		if(mu < mi){
			mi = mu;
			root = u;
		}
	};
	
	
	auto dfs = [&](auto &&self,int u,int p)-> void{
		for(auto [d,i] : v[u]){
			if(i != p && !done[i]){
				self(self,i,u);
			}
		}
	};
	
	
	auto work = [&](auto &&self,int u) -> void{
		
		getsize(getsize,u,-1);
		tot = siz[u];
		
		mi = 1e9;
		root = u;
		getroot(getroot,u,-1);
		//cout << root << endl;
		
		
		/*在此处填写点分治计算答案代码*/
		/*root 为重心*/	
		for(auto [d,i] : v[root]){
			if(!done[i]){
				dfs(dfs,i,root);
			}
		}
		
		done[root] = 1;
		for(auto [d,i] : v[root]){
			if(!done[i]){
				self(self,i);
			}
		}
	};

	work(work,1);

	
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	int t = 1;
	//cin >> t;
	while(t --){
		solve();
	}
}
