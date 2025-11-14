#include<bits/stdc++.h>
#define int long long

using namespace std;

struct ST{
    int n,t;
    vector<int> a;
    vector<array<int,24>> f;
    ST(vector<int> &a) : a(a){
        n = a.size() - 1;
        t = __lg(n) + 1;
        f.resize(n+1);
    }

    int cal(int x,int y){
        return __gcd(x,y); //¿É»»Îª__gcd(x,y) min(x,y)
    }

    void work(){
        for(int j = 0; j <= t; j ++){
            for(int i = 1; i + (1ll << j) - 1 <= n; i ++){
                if(!j) f[i][j] = a[i];
                else f[i][j] = cal(f[i][j-1],f[i+(1ll<<(j-1))][j-1]);
            }
        }
    }

    int query(int l,int r){
        int k = __lg(r - l + 1);
        return cal(f[l][k],f[r - (1 << k) + 1][k]);
    }
};