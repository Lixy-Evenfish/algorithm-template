#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef pair<int,int> PII;

void Hierholzer_easy_undirected() {
	int n, m;
	cin >> n >> m;
	
	// 邻接表存 {邻居, 边编号}
	vector<vector<pair<int, int>>> v(n + 1);
	vector<int> used(m + 1, 0);   // 标记边是否被用过
	int eid = 0;
	
	// 加边函数：无向边 = 两条有向边，共用同一个 eid
	auto add_edge = [&](int l, int r) {
		v[l].push_back({r, eid});
		v[r].push_back({l, eid});
		eid++;
	};
	
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		add_edge(x, y);
	}
	
	vector<int> p(n + 1, 0);   // 每个点走到第几条邻接边
	vector<int> path;
	
	auto dfs = [&](auto &&self, int u) -> void {
		while (p[u] < (int)v[u].size()) {
			auto [ne, id] = v[u][p[u]++];
			if (used[id]) continue;   // 反向边已被走过
			used[id] = 1;             // 标记这条无向边已用
			self(self, ne);
		}
		path.push_back(u);
	};
	
	int st = 1;   // 若题目没给起点，就选第一个有边的点
	dfs(dfs, st);
	reverse(path.begin(), path.end());
	
	for (int x : path) cout << x << ' ';
	cout << '\n';
}

void Hierholzer_easy_directed(){
	int n;
	vector<vector<int>> v(n + 1);   // 只存有向出边
	vector<int> p(n + 1);           // 当前点扫到第几条出边
	vector<int> path;               
	
	auto dfs = [&](auto &&self, int u) -> void {
		while (p[u] < v[u].size()) {
			int ne = v[u][p[u]++];
			self(self, ne);
		}
		path.push_back(u);     
	};
	int st; 
	dfs(dfs, st);
	reverse(path.begin(), path.end());
}

void Hierholzer_undirected() {
	int n, m;
	cin >> n >> m;
	
	vector<vector<PII>> v(n + 1); // v[u] = {to, eid}
	vector<int> from, to, used, deg(n + 1, 0);
	int eid = 0;
	
	auto addedge = [&](int l, int r) -> int {
		v[l].push_back({r, eid});
		v[r].push_back({l, eid});
		from.push_back(l);
		to.push_back(r);
		used.push_back(0);
		deg[l]++;deg[r]++;
		return eid++;
	};
	
	for (int i = 1; i <= m; i++) {
		int x,y;
		cin >> x >> y;
		addedge(x, y);
	}
	
	auto check = [&]() -> pair<int,int> {
		vector<int> odd, vis(n + 1, 0);
		int st = -1;
		
		for (int i = 1; i <= n; i++) {
			if (deg[i] && st == -1) st = i;
			if (deg[i] & 1) odd.push_back(i);
		}
		
		// 无向图欧拉路径条件：奇度点个数只能是 0 或 2
		if (!(odd.size() == 0 || odd.size() == 2)) return {0, -1};
		
		int cnt = 0;
		auto dfs = [&](auto &&self, int u) -> void {
			vis[u] = 1;
			cnt ++;
			for (auto [r, id] : v[u]) {
				if (!vis[r]) self(self, r);
			}
		};
		
		dfs(dfs, st);

		if (cnt < n) return {0, -1};         // 不存在
		if (odd.size() == 0) return {2, st};  // 欧拉回路
		return {1, odd[0]};                   // 欧拉路径
	};
	
	auto [type, st] = check();
	if (type == 0) {
		cout << "No\n";
		return;
	}
	
	vector<int> p(n + 1), edge, node;
	
	auto dfs = [&](auto &&self, int u, int peid) -> void {
		while (p[u] < (int)v[u].size()) {
			auto [r, id] = v[u][p[u]++];
			if (used[id]) continue;
			used[id] = 1;
			self(self, r, id);
		}
		edge.push_back(peid);
		node.push_back(u);
	};
	
	dfs(dfs, st, -1);
	reverse(edge.begin(), edge.end());
	reverse(node.begin(), node.end());
	
	// node: 点序列
	// edge: 边序列，edge[0] = -1
	for (int x : node) cout << x << ' ';
	cout << '\n';
}

void Hierholzer_directed() {
	int n, m;
	cin >> n >> m;
	
	vector<vector<PII>> v(n + 1); // 只存有向边：v[u] = {to, eid}
	vector<vector<int>> ug(n + 1); // 忽略方向后的图，只给 check 用
	vector<int> from, to;
	vector<int> indeg(n + 1, 0), outdeg(n + 1, 0);
	int eid = 0;
	
	auto addedge = [&](int l, int r) -> int {
		v[l].push_back({r, eid});
		ug[l].push_back(r);
		ug[r].push_back(l);
		from.push_back(l);
		to.push_back(r);
		outdeg[l]++;
		indeg[r]++;
		return eid++;
	};
	
	for (int i = 1; i <= m; i++) {
		int u, vtx;
		cin >> u >> vtx;
		addedge(u, vtx);
	}
	
	auto check = [&]() -> pair<int,int> {
		vector<int> vis(n + 1, 0);
		int st = -1;
		int s1 = -1, s2 = -1; // s1: out-in = 1, s2: in-out = 1
		
		for (int i = 1; i <= n; i++) {
			if (indeg[i] + outdeg[i] && st == -1) st = i;
			
			if (outdeg[i] - indeg[i] == 1) {
				if (s1 != -1) return {0, -1};
				s1 = i;
			} else if (indeg[i] - outdeg[i] == 1) {
				if (s2 != -1) return {0, -1};
				s2 = i;
			} else if (indeg[i] != outdeg[i]) {
				return {0, -1};
			}
		}
		
		// 连通性：忽略方向后必须连通
		int cnt = 0;
		auto dfs = [&](auto &&self, int u) -> void {
			vis[u] = 1;
			cnt ++;
			for (int r : ug[u]) {
				if (!vis[r]) self(self, r);
			}
		};
		
		dfs(dfs, st);
		
		if (cnt < n) return {0, -1};
		if (s1 == -1 && s2 == -1) return {2, st};
		if (s1 != -1 && s2 != -1) return {1, s1};
		
		return {0, -1};
	};
	
	auto [type, st] = check();
	if (type == 0) {
		cout << "No\n";
		return;
	}
	
	vector<int> p(n + 1), edge, node;
	
	auto dfs = [&](auto &&self, int u, int peid) -> void {
		while (p[u] < (int)v[u].size()) {
			auto [r, id] = v[u][p[u]++];
			self(self, r, id);
		}
		edge.push_back(peid);
		node.push_back(u);
	};
	
	dfs(dfs, st, -1);
	reverse(edge.begin(), edge.end());
	reverse(node.begin(), node.end());
	
	// node: 点序列
	// edge: 边序列，edge[0] = -1
	for (int x : node) cout << x << ' ';
	cout << '\n';
}


