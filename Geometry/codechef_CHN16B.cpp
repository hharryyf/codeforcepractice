#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 300011
using namespace std;

struct point {
	ll x, y, w;
	bool operator < (point other) const {
		if (x != other.x) return x < other.x;
		if (y != other.y) return y < other.y;
		return w < other.w;
	}
};
// (p1,p2) cross (p1, p3)
ll cross(point p1, point p2, point p3) {
	return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

point p[MAX_SIZE];
int n;

vector<point> grahamscan() {
	int i, sz = 0, j;
	vector<point> ret(n + n);
	sort(p, p + n);
	for (i = 0 ; i < n; ++i) {
		while ((sz > 1) && (cross(ret[sz - 2], ret[sz - 1], p[i]) <= 0ll)) --sz;
		ret[sz++] = p[i];
	}
	
	for (i = n - 2, j = sz + 1; i >= 0; --i) {
		while ((sz >= j) && (cross(ret[sz - 2], ret[sz - 1], p[i]) <= 0ll)) --sz;
		ret[sz++] = p[i];
	}
	ret.resize(sz - 1);
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int i;
	cin >> n;
	for (i = 0 ; i < n; ++i) {
		cin >> p[i].x >> p[i].y >> p[i].w;
	}
	auto ret = grahamscan();
	ll ans = 0;
	for (auto r : ret) {
		ans += r.w;
	}
	
	cout << ans << endl;
	return 0;
}