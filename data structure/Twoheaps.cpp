#include<bits/stdc++.h>
#define int long long

using namespace std;

struct Twoheaps{
	int k;
	multiset<int> top, bot; // top: 最大的k个
	long long s = 0;       
	
	Twoheaps(int k) : k(k) {}
	
	void push(int x){
 
		if(top.size() < k){
			top.insert(x);
			s += x;
			return;
		}
		
		if(x > *top.begin()){
			int y = *top.begin();
			top.erase(top.begin());
			s -= y;
			bot.insert(y);
			
			top.insert(x);
			s += x;
		}else{
			bot.insert(x);
		}
	}
	
	void erase(int x){
		auto it = top.find(x);
		if(it != top.end()){
			top.erase(it);
			s -= x;
			if(!bot.empty()){
				auto it2 = prev(bot.end());
				top.insert(*it2);
				s += *it2;
				bot.erase(it2);
			}
		}else{
			auto it = bot.find(x);
			if(it != bot.end()) bot.erase(it);
		}
	}
	
	int getkth(){
		return *top.begin();
	}
	
	long long sum(){
		return s;
	}
};


struct Twoheaps_priority_queue{
	int k;
	priority_queue<int, vector<int>, greater<int>> top; // 前k大
	priority_queue<int> bot;                            // 其余
	
	unordered_map<int,int> ct, cb; // top / bot 中还活着的值个数
	int nt = 0;
	long long s = 0;
	
	Twoheaps_priority_queue(int k) : k(k) {}
	
	void cleanTop(){
		while(!top.empty() && ct[top.top()] == 0) top.pop();
	}
	
	void cleanBot(){
		while(!bot.empty() && cb[bot.top()] == 0) bot.pop();
	}
	
	void up(){
		cleanBot();
		if(bot.empty()) return;
		int x = bot.top(); bot.pop();
		--cb[x];
		top.push(x); ++ct[x];
		++nt; s += x;
	}
	
	void down(){
		cleanTop();
		if(top.empty()) return;
		int x = top.top(); top.pop();
		--ct[x];
		--nt; s -= x;
		bot.push(x); ++cb[x];
	}
	
	void push(int x){
		if(k == 0){
			bot.push(x); ++cb[x];
			return;
		}
		
		cleanTop();
		if(nt < k){
			top.push(x); ++ct[x];
			++nt; s += x;
		}else if(x > top.top()){
			down();
			top.push(x); ++ct[x];
			++nt; s += x;
		}else{
			bot.push(x); ++cb[x];
		}
	}
	
	void erase(int x){
		if(ct[x]){
			--ct[x];
			--nt; s -= x;
			if(nt < k) up();
		}else if(cb[x]){
			--cb[x];
		}
	}
	
	int getkth(){
		cleanTop();
		return top.top();
	}
	
	long long sum(){
		return s;
	}
};