#include <bits/stdc++.h>
#define int long long
using namespace std;


template <class T>
struct Dinic {
	struct Edge {
		int to, rev;
		T cap;
	};
	
	int n;
	vector<vector<Edge>> g;
	vector<int> level, it;
	
	Dinic() {}
	Dinic(int n) { init(n); }
	
	void init(int n_) {
		n = n_;
		g.assign(n, {});
		level.assign(n, -1);
		it.assign(n, 0);
	}
	
	// 加一条 u -> v，容量为 cap 的有向边
	void addEdge(int u, int v, T cap) {
		g[u].push_back({v, g[v].size(), cap});
		g[v].push_back({u, g[u].size() - 1, 0});
	}
	
	bool bfs(int s, int t) {
		fill(level.begin(), level.end(), -1);
		queue<int> q;
		level[s] = 0;
		q.push(s);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (auto &e : g[u]) {
				if (e.cap > 0 && level[e.to] == -1) {
					level[e.to] = level[u] + 1;
					if (e.to == t) return true;
					q.push(e.to);
				}
			}
		}
		return level[t] != -1;
	}
	
	T dfs(int u, int t, T f) {
		if (u == t || f == 0) return f;
		for (int &i = it[u]; i < (int)g[u].size(); ++i) {
			Edge &e = g[u][i];
			if (e.cap > 0 && level[e.to] == level[u] + 1) {
				T ret = dfs(e.to, t, min(f, e.cap));
				if (ret > 0) {
					e.cap -= ret;
					g[e.to][e.rev].cap += ret;
					return ret;
				}
			}
		}
		return 0;
	}
	
	// 求 s 到 t 的最大流
	T maxFlow(int s, int t) {
		T flow = 0;
		while (bfs(s, t)) {
			fill(it.begin(), it.end(), 0);
			while (T f = dfs(s, t, numeric_limits<T>::max())) {
				flow += f;
			}
		}
		return flow;
	}
	
	// 最大流结束后，返回从 s 出发在残量网络中可达的点集
	vector<bool> minCutSide(int s) {
		vector<bool> vis(n, false);
		queue<int> q;
		vis[s] = true;
		q.push(s);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (auto &e : g[u]) {
				if (e.cap > 0 && !vis[e.to]) {
					vis[e.to] = true;
					q.push(e.to);
				}
			}
		}
		return vis;
	}
	
	// 导出残量网络： (u, v, residual_cap)
	vector<tuple<int,int,T>> residualNetwork() const {
		vector<tuple<int,int,T>> res;
		for (int u = 1; u < n; ++u) {
			for (auto &e : g[u]) {
				res.emplace_back(u, e.to, e.cap);
			}
		}
		return res;
	}
};

void solve(){
	int n,m,s,t;
	cin >> n >> m >> s >> t;
	
	Dinic<int> dinic(n+1);
	
	for(int i = 1; i <= m; i ++){
		int u,v,w;
		cin >> u >> v >> w;
		dinic.addEdge(u,v,w);
	}
	int ans = dinic.maxFlow(s,t);
	cout << ans << '\n';
	
}
