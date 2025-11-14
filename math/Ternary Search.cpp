#include<bits/stdc++.h>
#define int long long

using namespace std;

void solve(){
    auto check = [&](double x) -> double{
		
	};
	double l = -2e6,r = 2e6;
	while(r - l > 1e-9) {
		double lmid = l + (r - l) / 3, rmid = r - (r - l) / 3;

		// 求凹函数的极小值
		if(check(lmid) <= check(rmid)) r = rmid;
		else l = lmid;

         // 求凸函数的极大值
        if(check(lmid) <= check(rmid)) l = lmid;
        else r = rmid;
		
	}
    auto check = [&](int x)->int{

    };

    int l = -2e6,r = 2e6;
	while(l < r){
		int lmid = l + (r-l)/3, rmid = r - (r-l)/3;

		//如果是中间凸的单峰函数是<号，中间凹是>号。
		//求凹函数的极小值
		if(check(lmid) > check(rmid)) l = lmid + 1; 
		else r = rmid - 1;

		//求凸函数的极大值
		if(check(lmid) < check(rmid)) l = lmid + 1;
		else r = rmid - 1;
	}

}