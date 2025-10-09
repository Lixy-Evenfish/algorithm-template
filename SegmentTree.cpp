#include<bits/stdc++.h>
#define int long long
using namespace std;

struct info {
	//需要修改！！！
	int l,r;
	int sum;
	int mi,mx;
};
info operator+ (const info &l,const info &r) {
	//需要修改！！！
	info a;
	a.l = min(l.l,r.l),a.r = max(l.r,r.r);
	a.sum = l.sum + r.sum;
	a.mx = max(l.mx,r.mx);
	a.mi = min(l.mi,r.mi);
	return a;
}
struct Segtree{
	const int len;
	vector<info> seg;
	vector<int> tag;
	Segtree(int n1) :len(n1),seg(4*n1+1),tag(4*n1+1) {}
	void add(int np,int v)
	{
		//需要修改！！！
		tag[np] += v;
		seg[np].mx += v;
		seg[np].mi -= v;
		seg[np].sum += (seg[np].r-seg[np].l+1)*v;
	}
	void push(int np)
	{
		add(np << 1,tag[np]),add(np << 1 | 1,tag[np]);
		tag[np] = 0;
	}
	void pull(int id) {
		seg[id] = seg[id << 1] + seg[id << 1 | 1];
	}
	void init(vector<int> init)
	{
		auto build = [&](auto &&self,int np,int l,int r) -> void
		{
			if (l == r) seg[np] = {l, r, init[r]};
			else
			{
				seg[np] = {l, r};
				int mid = l + r >> 1;
				self(self,np << 1, l, mid), self(self,np << 1 | 1, mid + 1, r);
				pull(np);
			}
		};
		build(build,1,0,len);
	}
	void init(){
		auto build = [&](auto &&self,int np,int l,int r) -> void
		{
			if (l == r) seg[np] = {l, r, 0};
			else
			{
				seg[np] = {l, r};
				int mid = l + r >> 1;
				self(self,np << 1, l, mid), self(self,np << 1 | 1, mid + 1, r);
				pull(np);
			}
		};
		build(build,1,0,len);
	}
	void modify(int np,int x, int v)
	{
		if(seg[np].l == seg[np].r)
		{
			//需要修改！！！
			seg[np].sum += v;
			seg[np].mx += v;
			seg[np].mi += v;
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