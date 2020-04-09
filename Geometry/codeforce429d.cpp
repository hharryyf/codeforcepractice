#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;
typedef long long ll;
struct point {
	int x, y;
	bool operator < (point other) const {
		return y < other.y;
	}
};

const ll inf = 5e18;
point pt[MAX_SIZE];

int a[MAX_SIZE];

ll dist(point p1, point p2) {
	return 1ll * (p1.x - p2.x) * (p1.x - p2.x) + 
	       1ll * (p1.y - p2.y) * (p1.y - p2.y);
}

ll divc(int l, int r) {
	int i, j;
	ll ret = inf;
	if (l >= r) return inf;
	if (r - l == 1) {
		ret = dist(pt[l], pt[r]);
		return ret;
	}
	
	int mid = (l + r) >> 1;
	ll h1 = divc(l, mid), h2 = divc(mid + 1, r);
	ret = min(h1, h2);
	vector<point> can;
	for (i = mid; i >= l; --i) {
		if (1ll * (pt[mid].x - pt[i].x) * (pt[mid].x - pt[i].x) > ret) break;
		can.push_back(pt[i]);
	}
	
	for (i = mid + 1; i <= r; ++i) {
		if (1ll * (pt[mid].x - pt[i].x) * (pt[mid].x - pt[i].x) > ret) break;
		can.push_back(pt[i]);
	}
	
	sort(can.begin(), can.end());
	
	int sz = can.size();
	for (i = 0; i < sz; ++i) {
		for (j = i + 1; j < sz; ++j) {
			if (1ll * (can[i].y - can[j].y) * (can[i].y - can[j].y) > ret) break;
			ret = min(ret, dist(can[i], can[j]));
			// cout << i << " " << j << "  " << ret << endl;
		}
	}
	
	return ret;
}

int main() {
	int n, i;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		scanf("%d",  &a[i]);
		pt[i].x = i, pt[i].y = a[i] + pt[i-1].y;
	}
	
	ll ans = divc(1, n);
	printf("%I64d\n", ans);
	return 0;
}