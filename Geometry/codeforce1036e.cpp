#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define MAX_SIZE 1011
const ll inf = 1e12;
const double eps = 1e-9;

struct pt {
    double x, y;
    bool operator<(const pt& p) const {
        return x < p.x - eps || (abs(x - p.x) < eps && y < p.y - eps);
    }
};

struct segt {
    pt u, v;
};

struct line {
    double a, b, c;
    line() {}
    line(pt p, pt q) {
        a = p.y - q.y;
        b = q.x - p.x;
        c = -a * p.x - b * p.y;
        norm();
    }

    void norm() {
        double z = sqrt(a * a + b * b);
        if (abs(z) > eps) {
            a /= z, b /= z, c /= z;
        }
    }

    double dist(pt p) const { 
        return a * p.x + b * p.y + c; 
    }
};

double det(double a, double b, double c, double d) {
    return a * d - b * c;
}

inline bool betw(double l, double r, double x) {
    return min(l, r) <= x + eps && x <= max(l, r) + eps;
}

inline bool intersect_1d(double a, double b, double c, double d) {
    if (a > b) {
        swap(a, b);
    }

    if (c > d) {
        swap(c, d);
    }

    return max(a, c) <= min(b, d) + eps;
}

bool intersect(segt s1, segt s2, pt& left, pt& right) {
    pt a = s1.u, b = s1.v, c = s2.u, d = s2.v; 
    if (!intersect_1d(a.x, b.x, c.x, d.x) || !intersect_1d(a.y, b.y, c.y, d.y))
        return false;
    line m(a, b);
    line n(c, d);
    double zn = det(m.a, m.b, n.a, n.b);
    if (abs(zn) < eps) {
        if (abs(m.dist(c)) > eps || abs(n.dist(a)) > eps)
            return false;
        if (b < a)
            swap(a, b);
        if (d < c)
            swap(c, d);
        left = max(a, c);
        right = min(b, d);
        return true;
    } else {
        left.x = right.x = -det(m.c, m.b, n.c, n.b) / zn;
        left.y = right.y = -det(m.a, m.c, n.a, n.c) / zn;
        return betw(a.x, b.x, left.x) && betw(a.y, b.y, left.y) &&
               betw(c.x, d.x, left.x) && betw(c.y, d.y, left.y);
    }
}
int n;
segt st[MAX_SIZE];
// the intersection points that are on the segment i
set<pair<int, int>> ist[MAX_SIZE];
// all of the intersection points 
set<pair<int, int>> allist;

int main() {
    int i, j;
    ll ans = 0;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        int ax, ay, bx, by;
        scanf("%d%d%d%d", &ax, &ay, &bx, &by);
        int dx = abs(bx - ax), dy = abs(by - ay);
        ans += __gcd(dx, dy) + 1;
        st[i].u = pt{1.0 * ax, 1.0 * ay};
        st[i].v = pt{1.0 * bx, 1.0 * by};
    }

    // cout << ans << endl;
    for (i = 1; i <= n; ++i) {
        for (j = 1; j < i; ++j) {
            pt L = pt{0, 0}, R = pt{0, 0};
            if (intersect(st[i], st[j], L, R)) {
                double x = round(L.x), y = round(L.y);
                if (fabs(x - L.x) <= eps && fabs(y - L.y) <= eps) {
                    ist[i].insert(make_pair(x, y));
                    ist[j].insert(make_pair(x, y));
                    allist.insert(make_pair(x, y));
                }
            }
        }
    }

    for (i = 1; i <= n; ++i) {
        ans -= (int) ist[i].size();
    }

    ans += (int) allist.size();
    printf("%I64d\n", ans);
    return 0;
}