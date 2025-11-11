#include<bits/stdc++.h>
#define int long long

using namespace std;

struct info{
	int l,r;
	/*填入需要维护的内容*/ 
	//	int mx,mi;
	info(){}
	info(int nl,int nr){
		l = nl,r = nr;
		/*将填入变量初始化为0*/
		// mx = 0,mi = 0;
	}
};

info operator+(const info &l,const info &r){
	info a = {l.l,r.r};
	/*填入合并区间的方式*/
	//a.mi = min(l.mi,r.mi),a.mx = max(l.mx,r.mx);
	return a;
}

struct Segtree{
	int n;
	vector<info> seg;
	vector<int> tag,init;
	
	Segtree(vector<int> a):init(a){
		n = a.size() - 1;
		seg.resize(n << 2 | 2);
		tag.resize(n << 2 | 2);
	}
	void add(int np,int v)
	{
		/*单点修改的方式*/
		//seg[np].mx += v,seg[np].mi += v;
	}
	
	void work(){
		auto build = [&](auto &&self,int np,int l,int r) -> void
		{
			if (l == r){
				seg[np] = {l, r};
				add(np,init[l]);
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
