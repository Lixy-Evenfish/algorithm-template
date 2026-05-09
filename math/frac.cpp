#include<bits/stdc++.h>
#define int long long

using namespace std;

struct frac {
	int a, b;
	frac(int a, int b) : a(a), b(b) {}
	
	bool operator < (const frac& r) const {
		return (__int128)a * r.b < (__int128)r.a * b;
	}
	bool operator > (const frac& r) const {
		return (__int128)a * r.b > (__int128)r.a * b;
	}
	bool operator == (const frac& r) const {
		return (__int128)a * r.b == (__int128)r.a * b;
	}
	
	frac operator + (const frac& r) const {
		return {a * r.b + r.a * b, b * r.b};
	}
	frac operator - (const frac& r) const {
		return {a * r.b - r.a * b, b * r.b};
	}
	frac operator * (const frac& r) const {
		return {a * r.a, b * r.b};
	}
	frac operator / (const frac& r) const {
		return {a * r.b, b * r.a};
	}
};