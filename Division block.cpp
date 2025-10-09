#include<bits/stdc++.h>
#define int long long
using namespace std;
void solve(){
	int n,k;
	cin >> n >> k;
	//上取整
	long long r;
	for(int l = 1; l <= n; l = r + 1)
	{
    	if(k/l == 0)
    	{
    	    r = 8e18;       
    	}
    	else r = min(k/(k/l),n);
	}


	//下取整
	long long r;
	for(int l = 1; l <= n ; l = r + 1)
	{
		if((k-1)/l == 0)
		{
			r = 8e18;
		}
		else r = min((k-1)/((k-1)/l),n);
	}
}
