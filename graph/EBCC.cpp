#include<bits/stdc++.h>
#define int long long 

using namespace std;

struct EBCC{
	int n;
	vector<vector<int>> &v;
	vector<int> dfn,low,stk,bel;
	int cur,cnt;
	EBCC(vector<vector<int>> &g) : v(g){
		n = g.size()-1;
		dfn.resize(n+1);
		low.resize(n+1);
		bel.resize(n+1);
		cur = cnt = 0;
	}
	
	void tarjan(int u,int p){
		low[u] = dfn[u] = ++ cur;
		stk.push_back(u);
		bool flag = false;
		for(int i : v[u]){
			if(i == p && !flag){
				flag = 1;
				continue;
			}
			if(!dfn[i]){
				tarjan(i,u);
				low[u] = min(low[u],low[i]);
			}
			else low[u] = min(low[u],dfn[i]);
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
	
	void work(){
		for(int i = 1; i <= n; i ++){
			if(!dfn[i]){
				tarjan(i,-1);
			}
		}
	}
	struct Graph {
		int n;
		std::vector<std::pair<int, int>> edges;
		std::vector<int> siz;
		std::vector<int> cnte;
	};
	Graph compress() {
		Graph g;
		g.n = cnt + 1;
		g.siz.resize(cnt + 1);
		g.cnte.resize(cnt + 1);
		for (int i = 1; i <= n; i++) {
			g.siz[bel[i]]++;
			for (auto j : v[i]) {
				if (bel[i] < bel[j]) {
					g.edges.emplace_back(bel[i], bel[j]);
				} else if (i < j) {
					g.cnte[bel[i]]++;
				}
			}
		}
		return g;
	}
};