#include<bits/stdc++.h>
#define int long long

using namespace std;

void solve(){
    auto check = [&](double x) -> double{
		
	};
	double l = -2e6,r = 2e6;
	while(r - l > 1e-9) {
		double lmid = l + (r - l) / 3, rmid = r - (r - l) / 3;

		// �󰼺����ļ�Сֵ
		if(check(lmid) <= check(rmid)) r = rmid;
		else l = lmid;

         // ��͹�����ļ���ֵ
        if(check(lmid) <= check(rmid)) l = lmid;
        else r = rmid;
		
	}
    auto check = [&](int x)->int{

    };

    int l = -2e6,r = 2e6;
	while(l < r){
		int lmid = l + (r-l)/3, rmid = r - (r-l)/3;

		//������м�͹�ĵ��庯����<�ţ��м䰼��>�š�
		//�󰼺����ļ�Сֵ
		if(check(lmid) > check(rmid)) l = lmid + 1; 
		else r = rmid - 1;

		//��͹�����ļ���ֵ
		if(check(lmid) < check(rmid)) l = lmid + 1;
		else r = rmid - 1;
	}

}