struct Matrix{
    int n,m;
    vector<vector<int>> a;
    Matrix(int n1,int m1) : n(n1),m(m1),a(n1+1,vector<int>(m1+1)){}
    vector<int>& operator[] (int i) { return a[i]; }
    Matrix operator*(const Matrix &r) const {
        Matrix ret(n,r.m);
        for(int i = 1; i <= n; i ++)
            for(int j = 1; j <= r.m; j ++)
            {
                for(int k = 1; k <= m; k ++)
                {
                    ret.a[i][j] = (ret.a[i][j] + a[i][k]*r.a[k][j]) % mod;
                }
            }
        return ret;
    }
};
 auto M_qmi = [&](Matrix a,int b){
        Matrix ret(a.n,a.n);
        for(int i = 1; i <= a.n; i ++) ret.a[i][i] = 1;
        while(b)
        {
            if(b&1) ret = ret * a;
            a = a * a;
            b >>= 1;
        }
        return ret;
    };