#include<bits/stdc++.h>
#define int long long

using namespace std;

struct Exgcd{
	int a,b,k;
	//类内没有判断无解，注意在外面判断是否有 k % __gcd(a,b) == 0
	Exgcd(int a,int b,int k):a(a),b(b),k(k){}
	array<__int128,4> work(){
		__int128 g = __gcd(a,b);
		int x,y;
		auto exgcd = [&](auto &&self,int a,int b){
			if(b == 0){
				x = 1;
				y = 0;
				return;
			}
			self(self,b,a%b);
			int t = x;
			x = y;
			y = t - a/b*y;
		};
		exgcd(exgcd,a,b);
		__int128 dx = b/g,dy = -a/g;
		__int128 x0 = (__int128)x*(k/g),y0 = (__int128)y*(k/g);
		return {x0,y0,dx,dy};
	}
};