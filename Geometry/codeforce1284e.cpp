#include <bits/stdc++.h>
#define MAX_SIZE 2511
typedef long long ll;
using namespace std;

struct point {
    ll x, y;
    point operator -(point other) const {
        return point{x - other.x, y - other.y};
    }
};

point pt[MAX_SIZE];
vector<point> angle;

ll Cross(point p1, point p2) {
    return p1.x * p2.y - p1.y * p2.x;
}

static bool cmp(point &p1, point &p2) {
    pair<int, int> pp1 = make_pair(p1.x, p1.y);
    pair<int, int> pp2 = make_pair(p2.x, p2.y);

    if ((pp1 < make_pair(0, 0)) != (pp2 < make_pair(0, 0))) {
        return pp1 < pp2;
    }

    return Cross(p1, p2) > 0;
}

int main() {
    int i, n, j;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%I64d%I64d", &pt[i].x, &pt[i].y);
    }

    // ans = c(n, 4)
    ll ans = 1ll * n * (n - 1) * (n - 2) * (n - 3) * (n - 4) / 24;
    for (i = 1; i <= n; ++i) {
        angle.clear();
        for (j = 1; j <= n; ++j) {
            if (j == i) continue;
            angle.emplace_back(pt[j] - pt[i]);
        }

        sort(angle.begin(), angle.end(), cmp);

        int curr = 0;
        for (j = 0 ; j < n - 1; ++j) {
            while (curr < j + n - 1) {
                 if (Cross(angle[j], angle[curr % (n - 1)]) >= 0) {
                     curr++;
                 } else {
                     break;
                 }
            }

            // curr is the first failing spot
            // [j+1, curr - 1] select another 3 points
            int tol = curr - j - 1;
            ans = ans - 1ll * tol * (tol - 1) * (tol - 2) / 6;
        }
    }

    cout << ans << endl;
    return 0;
}