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
bool intriangle(point p1, point p2, point p3, point q) {
    Vector v1 = p1 - q, v2 = p2 - q, v3 = p3 - q;
    ll a1 = abs(Cross(p3 - p1, p2 - p1));
    ll a2 = abs(Cross(v1, v2)) + abs(Cross(v1, v3)) + abs(Cross(v2, v3));
    return a1 == a2;
}

int main() {
    int i;
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        ll x, y;
        scanf("%I64d%I64d", &x, &y);
        pt.push_back(point(x, y));
    }

    point p = pt[0];
    int pos = 0;
    for (i = 1; i < n; ++i) {
        if (pt[i] < p) {
            p = pt[i];
            pos = i;
        }
    }

    rotate(pt.begin(), pt.begin() + pos, pt.end());
    vector<Vector> line;
    for (i = 1; i < n; ++i) {
        line.push_back(pt[i] - pt[0]);
    }

    int q;
    scanf("%d", &q);
    while (q > 0) {
        ll x, y;
        scanf("%I64d%I64d", &x, &y);
        Vector vc = Vector(x - pt[0].x, y - pt[0].y);
        int low = 0, high = (int) line.size() - 1, ans = -1;
        if (OnSegment(vc + pt[0], pt[0], pt[1]) || OnSegment(vc + pt[0], pt[0], pt[n-1])) {
            printf("NO\n");
            return 0;
        }
        // the point is in the triangle formed by the vectors
        // line[ans] and line[ans - 1]
        while (low <= high) {
            int mid = (low + high) >> 1;
            if (Cross(line[mid], vc) >= 0) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        if (ans <= 0) {
            printf("NO\n");
            return 0;
        }

        if (OnSegment(vc + pt[0], line[ans-1] + pt[0], line[ans] + pt[0])) {
            printf("NO\n");
            return 0;
        }

        if (!intriangle(pt[0], line[ans] + pt[0], line[ans - 1] + pt[0], vc + pt[0])) { 
            printf("NO\n");
            return 0;
        }
        --q;
    }

    printf("YES\n");
    return 0;
}