#include <bits/stdc++.h>
#define MAX_SIZE 2511
using namespace std;

struct point {
	double x, y;
};

double dist(point a, point b) {
	return  sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
// dp[i][j][0] refers to the maximum distance such that you visit all
// the nodes between [i, j] in a clockwise direction with i as a start point
//
// dp[i][j][1] refers to the maximum distance such that you visit all
// the nodes between [i, j] in a clockwise direction with j as a start point
//
double dp[MAX_SIZE][MAX_SIZE][2];
point pt[MAX_SIZE];

int main() {
	int n, i, l, r;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) {
		scanf("%lf%lf", &pt[i].x, &pt[i].y);
	}
	// base case: dp[i][i][0/1] = 0
	
	for (i = 2; i <= n; ++i) {
		// i is the number of points in the clockwise direction
		for (l = 0; l < n; ++l) {
			r = (l + i - 1) % n;
			dp[l][r][0] = max(dp[(l+1)%n][r][0] + dist(pt[l], pt[(l+1)%n]), dp[(l+1)%n][r][1] + dist(pt[l], pt[r]));
			dp[l][r][1] = max(dp[l][(r-1+n)%n][0] + dist(pt[l], pt[r]), dp[l][(r-1+n)%n][1] + dist(pt[r], pt[(r-1+n)%n]));
		}
	}
	
	double ans = 0.0;
	for (i = 0 ; i < n; ++i) {
		ans = max(ans, max(dp[i][(i+n-1)%n][0], dp[i][(i+n-1)%n][1]));
	}
	
	printf("%.10lf\n", ans);
	return 0;
}