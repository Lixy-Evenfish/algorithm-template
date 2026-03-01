#include<bits/stdc++.h>
#define int long long

using namespace std;

//贪心 + 掩码方案还原
struct Xorbasis{
	const int bit = 64;
	vector<int> idx,mask;
	vector<int> idd;
	Xorbasis(){
		idx.resize(bit,-1);
		mask.resize(bit,0);
		idd.resize(bit,0);
	}
	void insert(int x,int num){
		int msk = 0;
		for(int i = bit-1; i >= 0; i --){
			if(x >> i & 1){
				if(idx[i] != -1){
					x ^= idx[i];
					msk ^= mask[i];
				}
				else{
					idd[i] = num;
					idx[i] = x;
					msk ^= (1ll << i);
					mask[i] = msk;
					break;
				}
			}
		}		
	}
	int getbit(int x){
		return idx[x];
	}
	
	int getmask(int x){
		return mask[x];
	}
	
	vector<int> decode(int msk){
		vector<int> ret;
		for(int i = 0; i <= bit-1; i ++){
			if((msk >> i & 1)){
				ret.push_back(idd[i]);
			}  
		}
		return ret;
	}

};