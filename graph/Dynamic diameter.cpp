#include<bits/stdc++.h>
#define int long long

using namespace std;
typedef pair<int,int> PII;
struct info{
	int l,r;
	/*填入需要维护的内容*/
	tuple<int,int,int> ans;
	tuple<int,int> ltmp,rtmp; //第二维是取最大值的点
	tuple<int,int> mx,mi; //第二维取最大值的点
	//info(){}
	//info(int nl,int nr){l = nl,r = nr,ans = 0,ltmp = 0,rtmp = 0,mx = 0,mi = 0;}
};
const int inf = 1e18;

info operator+(const info &l,const info &r){

	info a = {l.l,r.r,{-inf,0,0},{-inf,0},{-inf,0},{-inf,0},{inf,0}};
	a.mi = min(l.mi,r.mi);
	a.mx = max(l.mx,r.mx);
	a.ltmp = max(l.ltmp,r.ltmp);
	//if(get<0>(l.ltmp) > a.ltmp) a.ltmp = l.ltmp;
	if(get<0>(l.mx) - 2*get<0>(r.mi) > get<0>(a.ltmp)){
		a.ltmp = {get<0>(l.mx) - 2*get<0>(r.mi),get<1>(l.mx)};
	}
	a.rtmp = max(l.rtmp,r.rtmp);
	if(get<0>(r.mx) - 2*get<0>(l.mi) > get<0>(a.rtmp)){
		a.rtmp = {get<0>(r.mx) - 2*get<0>(l.mi),get<1>(r.mx)};
	}
	
	a.ans = max(l.ans,r.ans);
	if(get<0>(l.ltmp) + get<0>(r.mx) > get<0>(a.ans)){
		a.ans = {get<0>(l.ltmp) + get<0>(r.mx),get<1>(l.ltmp),get<1>(r.mx)};
	}
	if(get<0>(r.rtmp) + get<0>(l.mx) > get<0>(a.ans)){
		a.ans = {get<0>(r.rtmp) + get<0>(l.mx),get<1>(l.rtmp),get<1>(l.mx)};
	}
	return a;
}

struct Segtree{
	int n;
	vector<info> seg;
	vector<int> tag;
	vector<tuple<int,int>> init;
	
	Segtree(vector<tuple<int,int>> a):init(a){
		n = a.size() - 1;
		seg.resize(n << 2 | 2);
		tag.resize(n << 2 | 2);
	}
	void add(int np,int v)
	{
		/*单点修改的方式*/
		get<0>(seg[np].mx) += v;
		get<0>(seg[np].mi) += v;
		get<0>(seg[np].rtmp) -= v;
		get<0>(seg[np].ltmp) -= v;
	}
	
	void work(){
		auto build = [&](auto &&self,int np,int l,int r) -> void
		{
			if (l == r){
				int dfn = get<1>(init[l]),val = get<0>(init[l]);
				seg[np] = {l, r,{0,dfn,dfn},{-val,dfn},{-val,dfn},{val,dfn},{val,dfn}};
			}
			else
			{
				seg[np] = {l, r};
				int mid = l + r >> 1;
				self(self,np << 1, l, mid), self(self,np << 1 | 1, mid + 1, r);
				pull(np);
			}
		};
		build(build,1,1,n);
	}
	void push(int np)
	{
		add(np << 1,tag[np]),add(np << 1 | 1,tag[np]);
		tag[np << 1] += tag[np],tag[np << 1 | 1] += tag[np];
		tag[np] = 0;
	}
	void pull(int id) {
		seg[id] = seg[id << 1] + seg[id << 1 | 1];
	}
	
	void modify(int np,int x, int v)
	{
		if(seg[np].l == seg[np].r)
		{
			add(np,v);
		}
		else
		{
			int mid = seg[np].l + seg[np].r >> 1;
			push(np);
			if(x <= mid) modify(np << 1,x,v);
			else modify(np << 1 | 1,x,v);
			pull(np);
		}
	}
	void rangeadd(int np,int x,int y,int v)
	{
		if(seg[np].l >= x && seg[np].r <= y)
		{
			add(np,v);
			tag[np] += v;
		}
		else{
			push(np);
			int mid = seg[np].l + seg[np].r >> 1;
			if(x <= mid) rangeadd(np << 1,x,y,v);
			if(y > mid) rangeadd(np << 1 | 1,x,y,v);
			pull(np);
		}
	}
	info query(int np,int x,int y)
	{
		if(seg[np].l >= x && seg[np].r <= y) return seg[np];
		push(np);
		int mid = seg[np].l + seg[np].r >> 1;
		if(x <= mid && y > mid)
		{
			return query(np << 1,x,y) + query(np << 1 | 1,x,y);
		}
		else if(x <= mid) return query(np << 1,x,y);
		else return query(np << 1 | 1,x,y);
	}
};




void solve(){
	int n,q,w;
	cin >> n >> q >> w;
	vector<vector<PII>> v(n+1);
	vector<tuple<int,int,int>> edge(n+1);
	for(int i = 1; i <= n - 1; i ++){
		int a,b,c;
		cin >> a >> b >> c;
		edge[i] = {a,b,c};
		v[a].push_back({c,b});
		v[b].push_back({c,a});
	}
	vector<int> dfn(2*n+3),fi(n+1,-1),se(n+1,-1),depth(n+1);
	int tot = 0;
	auto dfs = [&](auto &&self,int u,int p,int dis) -> void{
		dfn[++tot] = u;
		if(fi[u] == -1) fi[u] = tot;
		else se[u] = tot;
		depth[u] = dis;
		for(auto [d,i] : v[u]){
			if(i != p){
				self(self,i,u,dis + d);
				dfn[++tot] = u;
				if(fi[u] == -1) fi[u] = tot;
				else se[u] = tot;
			}
		}
	};
	dfs(dfs,1,-1,0);
	vector<tuple<int,int>> dist(tot + 1);
	for(int i = 1; i <= tot; i ++){
		dist[i] = {depth[dfn[i]],dfn[i]};
	}
	Segtree tr(dist);
	tr.work();
	int last = 0;
	//last = get<0>(tr.query(1,1,tot + 1).ans);
	
	//cout << "tmp:" << last << endl;
	for(int i = 1; i <= q; i ++){
		int d,e;
		cin >> d >> e;
		d = ((d + last) % (n-1)) + 1;
		e = (e + last) % w;
		int diff = e - get<2>(edge[d]);
		get<2>(edge[d]) = e;
		int idx;
		if(depth[get<0>(edge[d])] > depth[get<1>(edge[d])]){
			idx = get<0>(edge[d]);
		}else idx = get<1>(edge[d]);
		int l = fi[idx],r = se[idx];
		if(r == -1) r = l;
		tr.rangeadd(1,l,r,diff);
		last = get<0>(tr.query(1,1,tot + 1).ans);
		cout << last << '\n';
	}
	cout << endl;
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
