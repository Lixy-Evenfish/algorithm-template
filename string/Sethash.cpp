#include<bits/stdc++.h>
#define int long long

using namespace std;
typedef unsigned long long ULL;


//ÎÞÐò¹þÏ£
struct Sethash{
	int n;
	vector<int> a;
	vector<ULL> xorsum,addsum;
	map<int,ULL> &mp;
	mt19937_64 rnd;
	
	Sethash(vector<int> _a, map<int,ULL> &_mp): a(_a),mp(_mp),rnd(random_device{}()){
		n = a.size()-1;
		xorsum.resize(n+1,0);
		addsum.resize(n+1,0);
	}
	
	ULL getval(int x){
		if(mp.find(x) == mp.end()){
			mp[x] = rnd();
		}
		return mp[x];
	}
	
	void work(){
		for(int i = 1; i <= n; i ++){
			ULL t = getval(a[i]);
			xorsum[i] = xorsum[i-1] ^ t;
			addsum[i] = addsum[i-1] + t;
		}	
	}
	
	pair<int,int> sum(int l,int r){
		return {xorsum[r] ^ xorsum[l-1],addsum[r] - addsum[l-1]};
	}
	
};

void solve(){
	int n;
	vector<int> a(n+1);
	map<int,ULL> table;
	
	Sethash hasha(a,table);
}
