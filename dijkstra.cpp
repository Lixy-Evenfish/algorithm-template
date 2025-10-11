#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef pair<int,int> PII;
void solve(){
	int n;
	vector<long long> dist(n+1,2e18),st(n+1);
	auto dijkstra = [&](int s) -> void
	{
		priority_queue<PII,vector<PII>,greater<PII>> heap;
   		dist[s] = 0;
		heap.push({0,s});
		while(!heap.empty())
		{
			auto [fi,se] = heap.top();
			heap.pop();
			if(st[se]) continue;
			st[se] = 1;
			for(auto [d,i] : v[se])
			{
				if(dist[i] > fi + d)
				{
					dist[i] = fi + d;
					heap.push({dist[i],i});
				}
			}
		}
    	return;
	};
	dijkstra(s);

}