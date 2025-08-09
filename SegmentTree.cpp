#include<bits/stdc++.h>
#define int long long

using namespace std;


struct info {
	int l,r;
	int sum;
};
info operator+ (const info &l,const info &r) {
	info a;
	a.l = min(l.l,r.l),a.r = max(l.r,r.r);
	a.sum = l.sum + r.sum;
	return a;
}
struct segment_tree{
	const int len;
	vector<info> seg;
	vector<int> tag;
	segment_tree(int n1) :len(n1),seg(4*n1+1),tag(4*n1+1) {}
	void add(int np,int v)
	{
		tag[np] += v;
		seg[np].sum += (seg[np].r-seg[np].l+1)*v;
	}
	void push(int np)
	{
		add(2*np,tag[np]),add(2*np+1,tag[np]);
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
				self(self,np*2, l, mid), self(self,np*2 + 1, mid + 1, r);
				pull(np);
			}
		};
		build(build,1,0,len);
	}
	void modify(int np,int x,info &v)
	{
		if(seg[np].l == seg[np].r)
		{
			seg[np] = v;
		}
		int mid = seg[np].l + seg[np].r >> 1;
		push(np);
		if(x <= mid) modify(2*np,x,v);
		else modify(2*np+1,x,v);
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
			if(x <= mid) rangeadd(2*np,x,y,v);
			if(y > mid) rangeadd(2*np+1,x,y,v);
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
			return query(np*2,x,y) + query(np*2+1,x,y);
		}
		else if(x <= mid) return query(np*2,x,y);
		else return query(np*2+1,x,y);
	}
};
