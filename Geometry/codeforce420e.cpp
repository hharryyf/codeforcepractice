#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-10;
const double Pi = acos(-1.0);

struct point {
    double x, y;
};

struct circle {
    point center;
    double r;
};
// the angle, the event type 1 means add event, -1 means remove event
vector<pair<double, int>> event;

int sgn(double x) {
    if (fabs(x) <= eps) return 0;
    if (x > 0) return 1;
    return -1;
}

static bool cmp(pair<double, int> &a, pair<double, int> &b) {
    if (sgn(a.first - b.first) == 0) {
        return a.second > b.second;
    }

    return a.first < b.first;
}

double sqr(double x) {
    return x * x;
}

int main() {
    int i, n;
    double j;
    double d;
    scanf("%d%lf", &n, &d);
    circle cr;
    for (i = 1; i <= n; ++i) {
        scanf("%lf%lf%lf", &cr.center.x, &cr.center.y, &cr.r);
        // we do an iteration that calculates the angle of intersection
        double angle = atan2(cr.center.y, cr.center.x);
        if (sgn(angle) < 0) {
            angle += Pi * 2;
        }

        double dist = sqrt(sqr(cr.center.x) + sqr(cr.center.y));
        for (j = ceil((dist - cr.r) / d); j <= floor((cr.r + dist) / d) + eps; j += 1.0) {
            double R = d * j;
            double theta = acos((sqr(dist) + sqr(R) - sqr(cr.r)) / (dist * R * 2.0));
            double al = angle - theta;
            double ar = angle + theta;
            if (sgn(al) < 0) {
                event.emplace_back(al + Pi * 2, 1);
                event.emplace_back(Pi * 2, -1);
                event.emplace_back(ar, -1);
                event.emplace_back(0, 1);
            } else if (ar > Pi * 2) {
                event.emplace_back(al, 1);
                event.emplace_back(Pi * 2, -1);
                event.emplace_back(0, 1);
                event.emplace_back(ar - Pi * 2, -1);
            } else {
                event.emplace_back(al, 1);
                event.emplace_back(ar, -1);
            }
        }
    }

    sort(event.begin(), event.end(), cmp);
    int ans = 0, tol = 0;
    for (auto &e : event) {
        tol += e.second;
        ans = max(ans, tol);
    }

    printf("%d\n", ans);
    return 0;
}