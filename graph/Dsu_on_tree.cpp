#include<bits/stdc++.h>
#define int long long

using namespace std;
typedef function<void(int)> FVI;
struct DSUtree{
	int n;
	vector<vector<int>> v;
	vector<int> son;
	
	FVI addp,clrp,getans;
	
	DSUtree(vector<vector<int>> &v,FVI addp,FVI clrp,FVI getans):v(v),addp(addp),clrp(clrp),getans(getans){
		n = v.size() - 1;
		son.resize(n+1);
	}
	
	void work(int s){
		dfs0(s,-1);
		dfs1(s,-1);
	}
	
	int dfs0(int u,int p){
		int s = -1,mx = -1,cnt = 0;
		for(int i : v[u]){
			if(i != p){
				int ret = dfs0(i,u);
				cnt += ret;
				if(ret > mx){
					s = i;
					mx = ret;	
				}
			}
		}
		son[u] = s;
		return cnt + 1;
	}
	
	void add(int u,int p){
		addp(u);
		for(int i : v[u]){
			if(i != p) add(i,u);
		}
	}
	
	void clr(int u,int p){
		clrp(u);
		for(int i : v[u]){
			if(i != p) clr(i,u);
		}
	}
	
	void dfs1(int u,int p){
		for(int i : v[u]){
			if(i != p && i != son[u]){
				dfs1(i,u);
				clr(i,u);
			}
		}
		if(son[u] != -1) dfs1(son[u],u);
		addp(u);
		for(int i : v[u]){
			if(i != p && i != son[u]){
				add(i,u);
			}
		}
		getans(u);
	}
	
};

void solve(){
	
	vector<vector<int>> v;
	
	auto add = [&](int u) -> void{
		/*填入添加单个点的操作*/
	};
	auto clr = [&](int u) -> void{
		/*填入删除单个点的操作*/
	};
	auto getans = [&](int u) -> void{
		/*统计单点答案的操作*/
	};
	DSUtree dsutree(v,add,clr,getans);
	dsutree.work(1);
	
}

