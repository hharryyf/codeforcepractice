// I solved this problem
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct point {
    ll x, y;
    point(ll x = 0, ll y = 0) : x(x), y(y) {}
    point operator -(point other) const {
        return point(x-other.x, y - other.y);
    }

    bool operator < (point other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }

    point operator +(point other) const {
        return point(x + other.x, y + other.y);
    }
};

typedef point Vector;
ll Cross(Vector v1, Vector v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

ll Dot(Vector v1, Vector v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

vector<point> pt;
int n;


// check if p is on segment a1, a2
bool OnSegment(point p, point a1, point a2){
    return Cross(a1-p, a2-p) == 0 && Dot(a1-p, a2-p) <= 0;
}

// check if q is in the triangle formed by p1, p2, p3
bool intriangle(point q, point p1, point p2, point p3) {
    Vector v1 = p1 - q, v2 = p2 - q, v3 = p3 - q;
    ll a1 = abs(Cross(p3 - p1, p2 - p1));
    ll a2 = abs(Cross(v1, v2)) + abs(Cross(v1, v3)) + abs(Cross(v2, v3));
    return a1 == a2;
}

point rec[2][4];

bool inrec(point pt, int dim) {
    return intriangle(pt, rec[dim][0], rec[dim][1], rec[dim][2]) ||
           intriangle(pt, rec[dim][0], rec[dim][1], rec[dim][3]) ||
           intriangle(pt, rec[dim][1], rec[dim][2], rec[dim][3]) ||
           intriangle(pt, rec[dim][0], rec[dim][2], rec[dim][3]);
}

int main() {
    int i, j;
    for (i = 0 ; i < 4; ++i) cin >> rec[0][i].x >> rec[0][i].y;
    for (i = 0 ; i < 4; ++i) cin >> rec[1][i].x >> rec[1][i].y;
    // cout << inrec(point(6, 6), 0) << " " << inrec(point(6, 6), 1) << endl;
    for (i = -200; i <= 200; ++i) {
        for (j = -200; j <= 200; ++j) {
            point np = point(i, j);
            if (inrec(np, 0) && inrec(np, 1)) {
                printf("YES\n");
                return 0;
            }
        }
    }
    printf("NO\n");
    return 0;
}