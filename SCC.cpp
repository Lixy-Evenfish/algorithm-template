#include<bits/stdc++.h>
#define int long long

using namespace std;

struct SCC{
	int n;
	vector<vector<int>> &v;
	vector<int> stk;
	vector<int> dfn,low,bel;
	int cur,cnt;
	
	SCC(vector<vector<int>> &g) : v(g){
		n = g.size() - 1;
		stk.resize(n+1);
		dfn.resize(n+1);
		low.resize(n+1);
		bel.resize(n+1);
		cur = cnt = 0;
	}
	
	void tarjan(int u){
		dfn[u] = low[u] = ++ cur;
		stk.push_back(u);
		for(int i : v[u]){
			if(!dfn[i]){
				tarjan(i);
				low[u] = min(low[u],low[i]);
			}else if(!bel[i]){
				low[u] = min(low[u],dfn[i]);
			}
		}
		
		if(dfn[u] == low[u]){
			cnt ++;
			int x;
			do{
				x = stk.back();
				bel[x] = cnt;
				stk.pop_back();
			}while(x != u);
		}
	}
	
	vector<int> work(){
		for(int i = 1; i <= n; i ++){
			if(!dfn[i]) tarjan(i);
		}
		return bel;
	}
	
	vector<vector<int>> rebuild(){
		vector<vector<int>> g(cnt + 1);
		set<pair<int,int>> s;
		for(int i = 1; i <= n; i ++){
			for(int j : v[i]){
				if(bel[j] != bel[i]){
					s.insert({bel[i],bel[j]});
				}
			}
		}
		for(auto [i,j] : s){ 
			g[i].push_back(j);
		}
		return g;
	}
};
