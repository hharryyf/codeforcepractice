#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 1048592
#define Pi acos(-1.0)
using namespace std;

struct light {
    double x, y, a;
};

light a[21];
double dp[MAX_SIZE];
double l, r;
int n;

struct point {
    double x, y;
};

double Dot(point p1, point p2) {
    return p1.x * p2.x + p1.y * p2.y;
}

double length(point p1) {
    return sqrt(Dot(p1, p1));
}

double position(double x, light lt) {
    point p1 = {x - lt.x, -lt.y}, p2 = {r - lt.x, -lt.y};
    double l1 = length(p1), l2 = length(p2);
    double alpha = min(lt.a, acos(Dot(p1, p2) /(l1 * l2)));
    double b = Pi - alpha - acos((lt.x - x) / l1);
    double L = fabs(sin(alpha) * l1 / sin(b));
    return x + L;
}

int main() {
    int i, j;
    scanf("%d", &n);
    scanf("%lf%lf", &l, &r);
    for (i = 0; i < n; ++i) {
        scanf("%lf%lf%lf", &a[i].x, &a[i].y, &a[i].a);
        a[i].a = a[i].a * Pi / 180.0;
    }

    for (i = 0 ; i < MAX_SIZE; ++i) dp[i] = l;
    for (i = 0; i < (1 << n); ++i) {
        for (j = 0 ; j < n; ++j) {
            if ((i & (1 << j)) != 0) continue;
            int nextstate = i | (1 << j);
            dp[nextstate] = max(dp[nextstate], min(r, position(dp[i], a[j])));
        }
    }

    printf("%.9lf\n", dp[(1 << n) - 1] - l);
    return 0;
}