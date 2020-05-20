#include <bits/stdc++.h>

using namespace std;

const double Pi = acos(-1.0);
const double eps = 1e-10;

struct point {
    double x, y;
    point(double x=0, double y=0) : x(x), y(y) {} 
    point operator -(point other) const {
        return point(x - other.x, y - other.y);
    }
};

typedef point Vector;

double Dot(Vector v1, Vector v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

struct circle {
    point c;
    double r;
};

double dist(point p1, point p2) {
    return sqrt(Dot(p1-p2, p1-p2));
}

int sgn(double x) {
    if (fabs(x) <= eps) return 0;
    if (x > 0) return 1;
    return -1;
}

int dcmp(double v1, double v2) {
    return sgn(v1 - v2);
}

// TODO
double find_union(vector<pair<double, double>> &vc) {
    if (vc.empty()) return 0.0;
    sort(vc.begin(), vc.end());
    double ans = 0.0, currR = vc[0].second, currL = vc[0].first;
    
    int i;
    // cout << currL << " " << currR << endl;
    for (i = 1; i < (int) vc.size(); ++i) {
        // cout << vc[i].first << " " << vc[i].second << endl;
        if (sgn(currR - vc[i].first) < 0) {
            ans += currR - currL;
            currL = vc[i].first;
            currR = vc[i].second;
        } else {
            currR = max(currR, vc[i].second);
        }
    }

    ans += currR - currL;
    return ans;
}

int main() {
    // all the valid ranges of angles
    vector<pair<double, double> > rg;
    circle c0, cr;
    double v, t;
    scanf("%lf%lf%lf%lf", &c0.c.x, &c0.c.y, &v, &t);
    c0.r = v * t;
    int i, n;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%lf%lf%lf", &cr.c.x, &cr.c.y, &cr.r);
        // if point c0.c is in the circle cr, then
        // we can walk in any direction 
        double di = dist(c0.c, cr.c);
        if (dcmp(di, cr.r) <= 0) {
            printf("1.0000000000\n");
            return 0;
        }
        
        if (dcmp(di, cr.r + c0.r) >= 0) continue;
        // the direction angle
        double dir = atan2(cr.c.y - c0.c.y, cr.c.x - c0.c.x);
        // make the direction angle from [0, 2*Pi]
        if (sgn(dir) < 0) dir += 2 * Pi;
        // use cosine law to calculate the second angle
        double agl;
        // edge case !!!!!
        if (dcmp(sqrt(di * di - cr.r * cr.r), c0.r) < 0) {
            agl = asin(cr.r / di);
        } else {
            agl = acos((c0.r * c0.r + di * di - cr.r * cr.r) / (2.0 * di * c0.r));
        }

        double aleft = dir - agl, aright = dir + agl;
        // cout << aleft << " " << aright << endl;
        if  (sgn(aleft) < 0) {
            rg.emplace_back(aleft + 2.0 * Pi, 2.0 * Pi);
            rg.emplace_back(0, aright);
        } else if (sgn(aright - 2.0 * Pi) > 0) {
            rg.emplace_back(aleft, 2.0 * Pi);
            rg.emplace_back(0, aright - 2.0 * Pi);
        } else {
            rg.emplace_back(aleft, aright);
        }
    }
    
    printf("%.12lf\n", 0.5 * find_union(rg) / Pi);
    return 0;
}