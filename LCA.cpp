#include<bits/stdc++.h>
#define int long long

using namespace std;

struct LCA{
	int n,k;
	vector<vector<int>> &v;
	vector<array<int,32>> fa;
	vector<int> depth;
	LCA(vector<vector<int>> &g): v(g){
		n = g.size()-1;
		k = __lg(n);
		fa.resize(n+1,{});
		depth.resize(n+1);
	}
	void dfs(int u,int p){
		//cout << u << ' ' << p << endl;
		depth[u] = depth[p] + 1;
		fa[u][0] = p;
		for(int i = 1; i <= k; i ++){
			fa[u][i] = fa[fa[u][i-1]][i-1];
		}
		for(int i : v[u]){
			if(i != p) dfs(i,u);
		}
	}
	
	void work(int s){
		dfs(s,0);
	}
	
	int jump(int u,int dis){
		if(dis == 0) return u;
		int t = depth[u] - dis, p = u;
		for(int i = k; i >= 0; i --){
			if(depth[fa[p][i]] > t) p = fa[p][i];
		}
		return fa[p][0];
	}
	
	int getlca(int a, int b) {
		if(depth[a] != depth[b]){
			if (depth[a] < depth[b])
				swap(a, b);
			for (int i = k ; i >= 0; i --) {
				if (depth[fa[a][i]] > depth[b])
					a = fa[a][i];
			}
			a = fa[a][0];
		}
		if (a == b)
			return a;
		for (int i = k ; i >= 0 ; i --) {
			if (fa[a][i] != fa[b][i]) {
				a = fa[a][i];
				b = fa[b][i];
			}
		}
		return fa[a][0];
	}
	
};