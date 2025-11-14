#include<bits/stdc++.h>
#define int long long

using namespace std;

struct TDC{
	int n;
	vector<vector<int>> v;
	vector<int> siz,mxson,done;
	/*添加处理答案需要的变量*/
	int cnt,rot;
	TDC(vector<vector<int>> &v) : v(v){
		n = v.size() - 1;
		siz.resize(n+1);
		mxson.resize(n+1);
		done.resize(n+1);
	} 
	
	void cal(){
		/*处理以rot为根的子树的信息*/
		/*注意：遇到done为1的点，需跳过*/
		
	}
	
	int getsize(int u,int p){
		siz[u] = 1;
		for(int i : v[u]){
			if(!done[i] && i != p){
				siz[u] += getsize(i,u);
			}
		}
		return siz[u];
	}
	
	int getroot(int u,int p){
		mxson[u] = cnt - siz[u];
		for(int i : v[u]){
			if(!done[i] && i != p){
				mxson[u] = max(mxson[u],siz[i]);
				getroot(i,u);
			}
		}
		if(mxson[u] < mxson[rot]) rot = u;
	}
		
	void work(int u){
		cnt = getsize(u,-1);
		rot = u,getroot(u,-1);
		
		cal();
		
		done[u] = 1;
		for(int i : v[u]){
			if(!done[i]){
				work(i);
			}
		}
	}
	
};