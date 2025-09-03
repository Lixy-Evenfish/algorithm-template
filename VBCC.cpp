#include<bits/stdc++.h>
#define int long long 

using namespace std;

struct VBCC{
	int n;
	vector<vector<int>> &v;
	vector<int> dfn,low,stk,flag;
	vector<vector<int>> vbcc;//点双连通分量
	int cur;
	VBCC(vector<vector<int>> &g) : v(g){
		n = g.size()-1;
		dfn.resize(n+1);
		low.resize(n+1);
		flag.resize(n+1);//是否为割点
		cur = 0;
	}
	
	void tarjan(int u,int p){
		int son = 0;
		low[u] = dfn[u] = ++ cur;
		stk.push_back(u);
		for(int i : v[u]){
			if(!dfn[i]){
				son ++;
				tarjan(i,u);
				low[u] = min(low[u],low[i]);
				if(low[i] >= dfn[u]){
					vector<int> tmp;
					int x;
					do{
						x = stk.back();
						tmp.push_back(x);
						stk.pop_back();
					}while(x != i);
					if(p != -1)flag[u] = 1;
					tmp.push_back(u);
					vbcc.push_back(tmp);
				}
			}
			else if(i != p) low[u] = min(low[u],dfn[i]);
		}
		if(p == -1 && son == 0) {
			vbcc.push_back({u});
		}
		if(p == -1 && son >= 2) flag[u] = 1; 
	}
	
	void work(){
		for(int i = 1; i <= n; i ++){
			if(!dfn[i]){
				stk.clear();
				tarjan(i,-1);
			}
		}
	}
	
};