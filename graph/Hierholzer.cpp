#include<bits/stdc++.h>
#define int long long

using namespace std;
typedef pair<int,int> PII;

void Hierholzer_node(){
	int n;
	vector<vector<int>> g(n + 1);
	vector<int> p(n + 1);   // 当前点扫到第几条边
	vector<int> path;          
	
	auto dfs = [&](auto &&self, int u) -> void {
		while (p[u] < g[u].size()) {
			int v = g[u][p[u]++];
			self(self, v);
		}
		path.push_back(u);     
	};
	int st; 
	dfs(dfs, st);
	reverse(path.begin(), path.end());
}

void Hierholzer(){
	int n;
	cin >> n;
	vector<vector<PII>> v(n + 1); // v[l] = {r, eid}
	vector<int> from, to,used;                       
	int eid = 0;
	
	auto addedge = [&](int l, int r) -> int {
		v[l].push_back({r, eid});
		// 有向图删掉下面一行
		v[r].push_back({l, eid}); // 有向图删该行
		from.push_back(l);
		to.push_back(r);
		used.push_back(0);        
		return eid++;
	};

	vector<int> p(n + 1),edge,node; 
	
	auto dfs = [&](auto &&self, int u, int peid) -> void {
		while (p[u] < (int)v[u].size()) {
			auto [r, eid] = v[u][p[u]++];
			if (used[eid]) continue;
			used[eid] = 1;
			self(self, r, eid);
		}
		edge.push_back(peid); 
		node.push_back(u);      
	};
	
	int st;
	dfs(dfs, st, -1);
	// node 即点序列
	// edge 即边序列（edge[0] 为 -1)
	reverse(edge.begin(), edge.end());
	reverse(node.begin(), node.end());

}
