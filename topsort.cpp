#include<bits/stdc++.h>
#define int long long
using namespace std;

// 拓扑排序 (有向图)
    vector<int> deg(n+1);
	queue<int> q;
	for(int i = 1; i <= n; i ++)
	{
		deg[i] = v[i].size();
		if(deg[i] == 0) q.push(i);
		
	}
	while(!q.empty())
	{
		auto t = q.front();
		q.pop();
		for(auto i : v[t])
		{
			deg[i] --;
			if(deg[i] == 0)
			{
				q.push(i);
			}
		}
	}
    // if(deg[i] >= 1)

// 拓扑排序 (无向图) 找环

    vector<int> deg(n+1);
	queue<int> q;
	for(int i = 1; i <= n; i ++)
	{
		deg[i] = v[i].size();
		if(deg[i] == 1) q.push(i);
	}
	while(!q.empty())
	{
		auto t = q.front();
		q.pop();
		for(auto i : v[t])
		{
			deg[i] --;
			if(deg[i] == 1)
			{
				q.push(i);
			}
		}
	}