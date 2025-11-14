#include<bits/stdc++.h>
#define int long long
using namespace std;

struct Fenwick{
    const int len;
    vector<int> a;
    Fenwick(int n1) : len(n1),a(len + 1,0){}
    #define lowbit(x) ((x) & (-x))
    void init(vector<int> &b)
    {
        for(int i = 1; i <= len; i ++)
        {
            a[i] += b[i];
            int j = i + lowbit(i);
            if(j <= len) a[j] += a[i];
        }
    }
    void add(int x,int c)
    {
        for(int i = x; i <= len; i += lowbit(i))
            a[i] += c;
    }
    int sum(int x)
    {
        int ret = 0;
        for(int i = x; i; i -= lowbit(i)) ret += a[i];
        return ret;
    }
    int sum(int l,int r)
    {
        return sum(r) - sum(l - 1);
    }
};