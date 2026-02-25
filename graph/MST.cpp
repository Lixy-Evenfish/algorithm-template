#include<bits/stdc++.h>
#define int long long

using namespace std;

typedef pair<int,int> PII;
typedef tuple<int,int,int> TI;
struct MST{
	int n;
	vector<int> p;
	vector<TI> edge;
	MST(int _n) : n(_n){
		p.resize(n);
		iota(p.begin()+1,p.end(),1);
	};
	
	int find(int u){
		if(u != p[u]) p[u] = find(p[u]);
		return p[u];
	}
	void merge(int x,int y)
	{
		x = find(x),y = find(y);
		if(x != y){
			p[y] = x;
		}
	}
	
	void addedge(TI e){
		edge.push_back(e);
	}
	
	int work(){
		sort(edge.begin(),edge.end());
		int ret = 0,cnt = 1;
		for(auto [l,x,y] : edge){
			if(find(x) != find(y)){
				ret += l;
				merge(x,y);
				cnt ++;
				if(cnt == n - 1){
					return ret;
				}
			}
		}
		return -1;
	}	
};