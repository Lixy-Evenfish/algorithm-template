#include<bits/stdc++.h>
#define int long long

using namespace std;
const int N,M;
struct Gauss {
	int n, m;
	bitset<N> a[M];
	vector<int> where;
	
	Gauss(int n, int m, bitset<N> matrix[]) :n(n),m(m),where(n+1,-1){
		for (int i = 1; i <= m; i++) a[i] = matrix[i];
	}
	
	void elimination() {
		int row = 1;
		for (int col = 1; col <= n && row <= m; col++) {
			int sel = row;
			
			while (sel <= m && !a[sel][col]) sel++;
			if (sel > m) continue; // 自由变量
			
			swap(a[sel], a[row]);
			where[col] = row;
			
			for (int i = 1; i <= m; i++) {
				if (i != row && a[i][col]) {
					a[i] ^= a[row];
				}
			}
			row++;
		}
	}
	
	// 无解返回 {}
	// 有解返回答案，自由变量为 -1
	vector<int> work() {
		elimination();
		// 判断无解：0 = 1
		for (int i = 1; i <= m; i++) {
			bool all0 = true;
			for (int j = 1; j <= n; j++) {
				if (a[i][j]) {
					all0 = false;
					break;
				}
			}
			if (all0 && a[i][0]) return {};
		}
		
		vector<int> ans(n + 1);
		
		for (int i = 1; i <= n; i++) {
			if (where[i] != -1) {
				ans[i] = a[where[i]][0];
			}else{
				//自由变量全设为0，得到一组特解。
				ans[i] = 0;
			}
		}
		
		return ans;
	}
};
 