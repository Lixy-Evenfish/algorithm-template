#include<bits/stdc++.h>
#define int long long

using namespace std;
typedef pair<int,int> PII;
struct LCA{
	int n,k,tot;
	vector<vector<PII>> &v;//无权边时，此处改为int
	vector<int> dfn,depth,pos;
	vector<array<int,24>> st,idx;
	LCA(vector<vector<PII>> &g): v(g){//无权边时，此处改为int
		n = g.size()-1;
		k = __lg(2*n+1);
		pos.resize(n+1);
		depth.resize(n+1);  
		dfn.resize(2*n+1);  
		st.resize(2*n+1,{});
		idx.resize(2*n+1,{});
		tot = 0;
	}
	
	void dfs(int u,int p,int dis){
		dfn[++tot] = u;
		pos[u] = tot;
		depth[u] = dis;
		for(auto [d,i] : v[u]){//无边权，此处改为auto i
			if(i != p){
				dfs(i,u,dis + d);//无边权时，此处改为 dis + 1
				dfn[++tot] = u; 
			}
		}
	}
	
	void work(int s){
		dfs(s,-1,1);
		
		for(int i = 1; i <= tot; i++){
			st[i][0] = depth[dfn[i]];
			idx[i][0] = dfn[i];
		}
	
		for(int j = 1; j <= k; j++){
			for(int i = 1; i + (1 << j) - 1 <= tot; i++){
				if(st[i][j-1] < st[i + (1 << (j-1))][j-1]){
					st[i][j] = st[i][j-1];
					idx[i][j] = idx[i][j-1];
				}else{
					st[i][j] = st[i + (1 << (j-1))][j-1];
					idx[i][j] = idx[i + (1 << (j-1))][j-1];
				}
			}
		}
	}
	
	int query(int x,int y){
		int l = pos[x], r = pos[y];
		if(l > r) swap(l, r);
		int len = __lg(r - l + 1);
		
		if(st[l][len] < st[r - (1 << len) + 1][len]){
			return idx[l][len];
		}else{
			return idx[r - (1 << len) + 1][len];
		}
	}
	
	int dis(int x,int y){
		return depth[x] + depth[y] - 2*depth[query(x,y)];
	}
};
