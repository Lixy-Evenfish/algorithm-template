#include<bits/stdc++.h>
#define int long long

using namespace std;


//高斯消元
struct Xorbasis{
	const int bit = 64;
	int n,k;
	vector<int> a,idx;
	
	void insert(int x){
		a.push_back(x);
	}
	
	vector<int> work(){
		n = a.size();
		k = 0;
		idx.resize(bit,-1);
		for(int i = bit-2; i >= 0; i --){
			for(int j = k; j < n; j ++){
				if((a[j]>>i&1)){
					swap(a[j],a[k]);
					break;
				}
			}
			if(!(a[k]>>i&1)){
				idx[i] = -1;
				continue;
			}
			idx[i] = k;
			for(int j = 0; j < n; j ++){
				if(j != k && (a[j]>>i&1)){ 
					a[j] ^= a[k];	
				}
			}
			k ++;
			if(k == n) break;
		}
		return a;
	}
	
	
	//判断第i位是否有主元
	int getbit(int i){
		if(idx[i] == -1)  return -1;
		else return a[idx[i]];
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
