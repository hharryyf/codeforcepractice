#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

struct Point{
    int x, y;
    Point(int x = 0, int y = 0):x(x),y(y){}
};

typedef Point Vector;

int Cross(Vector A, Vector B){
    return A.x*B.y-A.y*B.x;
}

Vector pt[111];

int gcd(int x, int y) {
	return x == 0 ? y : gcd(y % x, x);
}

int main() {
	int T, i, j;
	scanf("%d", &T);
	for (i = 1; i <= T; ++i) {
		int n;
		// area
		int ara = 0;
		// boarder point
		int bpt = 0;
		scanf("%d", &n);
		pt[0].x = 0, pt[0].y = 0;
		for (j = 1; j <= n; ++j) {
			int dx, dy;
			scanf("%d%d", &dx, &dy);
			pt[j].x = pt[j-1].x + dx;
			pt[j].y = pt[j-1].y + dy;
			ara += Cross(pt[j-1], pt[j]);
			bpt += gcd(abs(dx), abs(dy));
		}
		
		ara = abs(ara);
		printf("Scenario #%d:\n", i);
		// pick's theorem
		printf("%d %d %.1lf\n\n", (ara - bpt + 2) / 2, bpt, 0.5 * ara);
	}
	return 0;
}