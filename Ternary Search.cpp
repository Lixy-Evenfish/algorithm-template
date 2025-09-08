#include<bits/stdc++.h>
#define int long long

using namespace std;

void solve(){
    auto cal = [&](double x) -> double{
		
	};
	double l = -2e6,r = 2e6;
	while(r - l > 1e-9) {
		double lmid = (2*l + r) / 3;
		double rmid = (l + 2*r) / 3;
		double lans = cal(lmid), rans = cal(rmid);
		
		// 求凹函数的极小值
		if(lans <= rans) r = rmid;
		else l = lmid;

         // 求凸函数的极大值
        if(lans <= rans) l = lmid;
        else r = rmid;
		
	}
    auto cal = [&](int x)->int{

    };
    
}