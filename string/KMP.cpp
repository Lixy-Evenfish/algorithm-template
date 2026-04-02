#include<bits/stdc++.h>
#define int long long

using namespace std;

struct KMP{
	string p;
	int m;
	vector<int> ne;
	KMP(string p) : p(p){
		m = p.size() - 1;
		ne.resize(m+1,0);
		for(int i = 2,j = 0; i <= m; i ++){
			while(j && p[i] != p[j+1]) j = ne[j];
			if(p[i] == p[j+1]) j ++;
			ne[i] = j;
		}
	}
	
	vector<int> work(string s){
		int n = s.size() + 1;
		vector<int> st(n+1);
		for(int i = 1,j = 0; i <= n; i ++){
			while(j && s[i] != p[j+1]) j = ne[j];
			if(s[i] == p[j+1]) j ++;
			if(j == m){
				st[i - m + 1] = 1;
				j = ne[j];
			}
		}
		return st;
	}
	
};
