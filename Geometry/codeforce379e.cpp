#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-7;

struct point {
    double x, y;
    point(double X, double Y) : x(X), y(Y) {}
    point operator -(point other) const {
        return point(x-other.x, y - other.y);
    }
    
    point operator +(point other) const {
        return point(x + other.x, y + other.y);
    }

    point operator *(double t) const {
        return point(x * t, y * t);
    }
};

typedef point Vector;

int sgn(double x) {
    if (fabs(x) <= eps) return 0;
    if (x > 0) return 1;
    return -1;
}

double Cross(point A, point B){
    return A.x*B.y-A.y*B.x;
}

// y coordinate for x on the line formed by p1, p2
// invariant: p1.y != p2.y
double ycoord(double x, point p1, point p2) {
    return p1.y + (x - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
}

point GetLineIntersection(point P, Vector v, point Q, Vector w){
    Vector u = P-Q;
    double t = Cross(w, u)/Cross(v, w);
    return P+v*t;
}

// invariant: points are sorted according to x
vector<point> outline;
vector<bool> cancel;
// the new points that should be inserted into the outline
vector<point> curr;
double ans[411];
// coord[i][j] is the ith polyline y coordinate at x=j
int coord[411][411];
int n;

vector<point> merge(vector<point> &pt1, vector<point> &pt2) {
    int i = 0, j = 0;
    vector<point> ret;
    int sz1 = pt1.size(), sz2 = pt2.size();
    while (i < sz1 && j < sz2) {
        if (pt1[i].x <= pt2[j].x) {
            if (ret.empty() || sgn(ret.back().x - pt1[i].x) != 0 || sgn(ret.back().y - pt1[i].y) != 0) {
                ret.push_back(pt1[i]);
            }
            ++i;
        }  else {
            if (ret.empty() || sgn(ret.back().x - pt2[j].x) != 0 || sgn(ret.back().y - pt2[j].y) != 0) {
                ret.push_back(pt2[j]);
            }
            ++j;
        }
    }

    while (i < sz1) {
        if (ret.empty() || sgn(ret.back().x - pt1[i].x) != 0 ||  sgn(ret.back().y - pt1[i].y) != 0) {
                ret.push_back(pt1[i]);
        }
        ++i;
    }

    while (j < sz2) {
        if (ret.empty() || sgn(ret.back().x - pt2[j].x) != 0 ||  sgn(ret.back().y - pt2[j].y) != 0) {
            ret.push_back(pt2[j]);
        }
        ret.push_back(pt2[j++]);
    
    }
    return ret;
}

// [l, l+1], find the area
void solve(int l) {
    int i, j;
    outline.clear();
    outline.push_back(point(l, coord[1][l]));
    outline.push_back(point(l+1, coord[1][l+1]));
    ans[1] += 0.5 * (coord[1][l] + coord[1][l+1]);
    for (i = 2; i <= n; ++i) {
        point L = point(l, coord[i][l]), R = point(l+1, coord[i][l+1]);
        int sz = (int) outline.size();
        curr.clear();
        cancel = vector<bool>(sz, false);
        // consider the segment outline[j] to outline [j-1]
        // see the area created by the current line 
        for (j = 0 ; j < sz - 1; ++j) {
            double y1 = ycoord(outline[j].x, L, R), y2 = ycoord(outline[j+1].x, L, R);
            double d1 = -outline[j].y + y1, d2 = -outline[j+1].y + y2;
            //cout << y1 << " " << y2 << " " << L.y << " " << R.y << endl;
            //cout << outline[j].x << " " << outline[j+1].x << endl;
            //cout << d1 << " " << d2 << endl;
            if (sgn(d1) >= 0 && sgn(d2) >= 0) {
                cancel[j] = true, cancel[j+1] = true;
                ans[i] += 0.5 * (d1 + d2) * (outline[j+1].x - outline[j].x);
                curr.push_back(point(outline[j].x, y1));
                curr.push_back(point(outline[j+1].x, y2));
            } else if (sgn(d1) > 0 && sgn(d2) < 0) {
                point pt = GetLineIntersection(L, R-L, outline[j], outline[j+1]-outline[j]);
                cancel[j] = true;
                ans[i] += 0.5 * (pt.x - outline[j].x) * d1;
                curr.push_back(point(outline[j].x, y1));
                curr.push_back(pt);
            } else if (sgn(d1) < 0 && sgn(d2) > 0) {
                point pt = GetLineIntersection(L, R-L, outline[j], outline[j+1]-outline[j]);
                cancel[j+1] = true;
                ans[i] += 0.5 * (outline[j+1].x - pt.x) * d2;
                curr.push_back(pt);
                curr.push_back(point(outline[j+1].x, y2));
            }    
        }

        // we merge the two intervals;
        vector<point> tmp;
        for (j = 0 ; j < sz; ++j) {
            if (!cancel[j]) tmp.push_back(outline[j]);
        }

        outline = merge(tmp, curr);
        /*
        cout << "outline size " << outline.size() << endl;
        for (auto o : outline) {
            cout << o.x << " " << o.y << endl;
        }
        cout << "-----" << endl;
        */
    }
}

int main() {
    int k, i, j;
    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; ++i) {
        for (j = 0 ; j <= k; ++j) {
            scanf("%d", &coord[i][j]);
        }
    }

    for (i = 0; i < k; ++i) {
        // solve for the interval [i, i+1]
        solve(i);
    }

    for (i = 1; i <= n; ++i) {
        printf("%.12lf\n", fabs(ans[i]));
    }
    return 0;
}
