#include <bits/stdc++.h>
#define MAX_SIZE 311
using namespace std;

struct point {
    int x, y;
    point(int x=0, int y=0) : x(x), y(y) {}
    point operator -(point other) const {
        return point(x - other.x, y - other.y);
    }
};

typedef point Vector;
point pt[MAX_SIZE];

int Cross(Vector v1, Vector v2) {
    return v1.x * v2.y - v1.y * v2.x;
} 

int main() {
    int n, i, j, k;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d%d", &pt[i].x, &pt[i].y);
    }

    int ans = 0;
    for (i = 1; i <= n; ++i) {
        for (j = i + 1; j <= n; ++j) {
            Vector diagnal = pt[j] - pt[i];
            int mx = 0, mn = 0;
            for (k = 1; k <= n; ++k) {
                if (i == k || j == k) continue;
                Vector vc = pt[k] - pt[i];
                int area = Cross(diagnal, vc);
                if (mn == 0 || mn > area) mn = area;
                if (mx == 0 || mx < area) mx = area;
            }

            if (mx != 0 && mn != 0) {
                ans = max(mx - mn, ans);
            }
        }
    }

    printf("%lf\n", 0.5 * ans);
    return 0;
}