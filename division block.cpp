#include<bits/stdc++.h>
#define int long long

//��ȡ��
long long r;
for(int l = 1; l <= n; l = r + 1)
{
		r = k/(k/l);
		/*
		your code
		*/
}

//��ȡ��
int r;
for(int l = 1; l <= n; l = r + 1)
{
	if((m-1)/l == 0) r = 8e18;
	else r = (m-1)/((m-1)/l);
	ans = min(ans,((m+l-1)/l)*l - m + n - l);
}