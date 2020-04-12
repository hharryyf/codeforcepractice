#include <bits/stdc++.h>
#define MAX_SIZE 100011
#define Pi acos(-1.0)
typedef long double DB;

using namespace std;

struct point {
	int id;
	DB ag;
	bool operator < (point other) const {
		return ag < other.ag;
	}
};

point p[MAX_SIZE];

int main() {
	int n, i;
	scanf("%d", &n);
	for (i = 0 ; i < n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		p[i].id = i + 1, p[i].ag = atan2(y, x);
		// cout << p[i].ag << endl;
	}
	
	sort(p, p + n);
	DB ans;
	if (p[0].ag < 0) {
		ans = 2 * Pi + p[0].ag - p[n-1].ag;
	} else {
		ans = p[n-1].ag - p[0].ag;
	}
	int v1 = p[0].id, v2 = p[n-1].id;
	
	for (i = 1; i < n; ++i) {
		if (p[i].ag - p[i-1].ag < ans) {
			v1 = p[i-1].id, v2 = p[i].id;
			ans = p[i].ag - p[i-1].ag;
		}
	}
	
	printf("%d %d\n", v1, v2);
	return 0;
}