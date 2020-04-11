#include <bits/stdc++.h>
#define MAX_SIZE 171
using namespace std;

const double eps = 1e-9;

struct point {
	int x, y;
	point(int x = 0, int y = 0):x(x),y(y){}
};

point operator - (point A, point B){
    return point(A.x-B.x, A.y-B.y);
}

int Dot(point A, point B){
    return A.x*B.x + A.y*B.y;
}

int Cross(point A, point B){
    return A.x*B.y-A.y*B.x;
}

int sgn(double x) {
	if (x > eps) return 1;
	if (x < -eps) return -1;
	return 0;
}

double r;
point pt[MAX_SIZE];

int main() {
	int n, i, j;
	while (scanf("%d%d%lf", &pt[0].x, &pt[0].y, &r) != EOF) {
		if (r < 0) break;
		scanf("%d", &n);
		for (i = 1 ; i <= n; ++i) {
			scanf("%d%d", &pt[i].x, &pt[i].y);
		}
		
		int ans = 0;
		for (i = 1; i <= n; ++i) {
			int cnt = 0;
			if (sgn(1.0 * Dot(pt[i] - pt[0], pt[i] - pt[0]) - r * r) == 1) continue;
			for (j = 1; j <= n; ++j) {
				if (Cross(pt[i] - pt[0], pt[j] - pt[0]) >= 0 && sgn(1.0 * Dot(pt[j] - pt[0], pt[j] - pt[0]) - r * r) <= 0) {
					++cnt;
				}
			}
			ans = max(ans, cnt);
		}
		
		printf("%d\n", ans);
	}
	return 0;
}