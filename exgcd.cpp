#include<bits/stdc++.h>
#define int long long
using namespace std;

int x,y;
auto exgcd = [&](auto &&self,int a,int b) -> void
{
	if(b == 0)
	{
		x = 1;
		y = 0;
		return;
	}
	self(self,b,a%b);
	int t = x;
	x = y;
	y = t - a/b*y;
};  