#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef unsigned long long ULL;

struct query {
	int l, r, id;
};
void solve() {
	
	int n,q;
	cin >> n >> q;

	int B = max(1ll, (int)sqrt(n));
	vector<query> node(q+1);
	vector<int> ans(q+1);
	for(int i = 1; i <= q; i ++){
		int l,r;
		cin >> l >> r;
		node[i] = {l,r,i};
	}
	sort(node.begin()+1, node.end(), [&](query a, query b) {
		int x = a.l / B, y = b.l / B;
		if (x != y) return x < y;
		if (x & 1) return a.r > b.r;
		return a.r < b.r;
	});
	
	//0-idx l = 0,r = -1
	//1-idx l = 1,r = 0;
	int l = 0, r = -1,nowans = 0;
	auto add = [&](int np){

	};
	auto del = [&](int np){

	};
	for (int i = 1; i <= q; ++i) {
		auto &e = node[i];
		while (l > e.l) add(--l);
		while (r < e.r) add(++r);
		while (l < e.l) del(l++);
		while (r > e.r) del(r--);
		ans[e.id] = nowans;
	}
	
	for (int i = 1; i <= q; ++i) {
		cout << ans[i] << '\n';
	}
}
