#include<bits/stdc++.h>
#define int long long

using namespace std;

struct Dsu{
	int n;
	vector<int> f,siz;
	Dsu(int _n) : n(_n),f(n+1){
		iota(f.begin()+1,f.end(),1);
		siz.assign(n+1,1);
	}
	
	int find(int x)
	{
		if(f[x] != x) f[x] = find(f[x]);
		return f[x];
	}
	
	bool same(int x,int y)
	{
		return find(x) == find(y);
	}
	
	void merge(int x,int y)
	{
		x = find(x),y = find(y);
		siz[x] += siz[y];
		f[y] = x;
	}
	
	int size(int x) {
		return siz[find(x)];
	}
};
