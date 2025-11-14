#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e6 + 10;
int dfn[N],low[N],cnt;
stack<int> stk;
bool ins[N];
int id[N],scc_cnt,sz[N];
vector<int> g[N];
int n,m;

void tarjan(int u)
{
	dfn[u] = low[u] = cnt ++;
	stk.push(u);
	ins[u] = 1;
	for(auto j : g[u]){
		if(!dfn[j])
		{
			tarjan(j);
			low[u] = min(low[u],low[j]);
		}
		else if(ins[j])
		{
			low[u] = min(low[u],dfn[j]);
		}
	}
	if(dfn[u] == low[u])
	{
		int y;
		++scc_cnt;
		do{
			y = stk.top();
			stk.pop();
			ins[y] = 0;
			id[y] = scc_cnt;
			sz[scc_cnt] ++;
		}while(y != u);
	}
}



    //判断有无解
	for(int i = 1; i <= 2*n; i ++)
	{
		if(!dfn[i]) tarjan(i);
	}
	for(int i = 1; i <= n; i ++)
	{
		if(id[i] == id[i+n])
		{
			cout << "NO\n";
			return;
		}
    }
    //存储答案
	vector<int> ans;
	for(int i = 1; i <= n; i ++)
	{
		if(id[i] < id[i + n])
			ans.push_back(i);
	}
