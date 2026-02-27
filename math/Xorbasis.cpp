#include<bits/stdc++.h>
#define int long long

using namespace std;

struct Xorbasis{
	int n,k;
	vector<int> a;
	
	void insert(int x){
		a.push_back(x);
	}
	
	//高斯消元求线性基
	vector<int> work(){
		n = a.size();
		k = 0;
		for(int i = 62; i >= 0; i --){
			for(int j = k; j < n; j ++){
				if((a[j]>>i&1)){
					swap(a[j],a[k]);
					break;
				}
			}
			if(!(a[k]>>i&1)){
				continue;
			}
			for(int j = 0; j < n; j ++){
				if(j != k && (a[j]>>i&1)) a[j] ^= a[k];
			}
			k ++;
			if(k == n) break;
		}
		return a;
	}
	
	//求最大
	int getmax(){
		int ret = 0;
		for(int i : a){
			ret ^= i;
		}
		return ret;
	}
	
	//求第x小
	int getxth(int x){
		int ret = 0;
		if(k < n){
			x --;
		}
		if(x >= (1ll << k)){
			return -1;
		}
		for(int i = 0; i < k; i ++){
			if(x >> i & 1){
				ret ^= a[k-i-1];
			}
		}
		return ret;
	}

};

void solve(){
	int n,q;
	cin >> n;
	Xorbasis basis;
	for(int i = 1; i <= n; i ++){
		int x;
		cin >> x;
		basis.insert(x);
	}
	cin >> q;
	basis.work();
	while(q --){
		int x;
		cin >> x;
		cout << basis.getxth(x) << '\n';
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	int tt = 1;
	while(t --){
		cout << "Case #" << tt ++ << ':'<< '\n';
		solve();
	}
}