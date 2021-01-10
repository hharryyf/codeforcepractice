#include <bits/stdc++.h>
#define MAX_SIZE 4011
using namespace std;
typedef long long ll;
const double Pi = acos(-1.0);
const double eps = 1e-9;

int sgn(double x) {
	if (fabs(x) <= eps) return 0;
	if (x > 0) return 1;
	return -1;
}

struct point {
	double x, y;
	point(double x=0, double y=0) : x(x), y(y) {}
	point operator -(point other) {
		return point(x - other.x, y - other.y);
	}
	
	point operator +(point other) {
		return point(x + other.x, y + other.y);
	}
	
	bool operator < (point other) {
		if (x != other.x) return x < other.x;
		return y < other.y;
	}
	
	point operator *(double p) {
		return point(x*p, y*p);
	}
};

point pt[MAX_SIZE];
ll G[MAX_SIZE];
int N;
vector<pair<double, ll>> pre;

ll query(int l, int r) {
    if (l > r) return 0;
    return pre[r].second - (l != 0 ? pre[l-1].second : 0);
}

int main() {
    int i, j;
    ll ans = 1e16;
    scanf("%d", &N);    
    for (i = 1; i <= N; ++i) {
        scanf("%lf%lf%I64d", &pt[i].x, &pt[i].y, &G[i]);
    }

    for (i = 1; i <= N; ++i) {
        pre.clear();
        ll tol = 0;
        for (j = 1; j <= N; ++j) {
            if (j == i) continue;
            point p = pt[j] - pt[i];
            pre.emplace_back(atan2(p.y, p.x), G[j]);
            tol = tol + G[j];
        }

        sort(pre.begin(), pre.end());
        int sz = pre.size();
        for (j = 1; j < sz; ++j) pre[j].second += pre[j-1].second;
        for (j = 0 ; j < sz; ++j) {
            tol -= query(j, j);
            if (sgn(pre[j].first) > 0) {
                int low = 0, high = j - 1, idx = -1;
                while (low <= high) {
                    int mid = (low + high) / 2;
                    if (sgn(pre[mid].first + Pi - pre[j].first) <= 0) {
                        idx = mid;
                        low = mid + 1;
                    } else {
                        high = mid - 1;
                    }
                }

                ll pt1 = query(j + 1, sz - 1) + query(0, idx);
                ll pt2 = tol - pt1;
                ans = min(ans, abs(pt1 - pt2));
            } else {
                // get last index such that pre[idx].first  <= pre[j].first + Pi
                int low = j + 1, high = sz - 1, idx = j;
                while (low <= high) {
                    int mid = (low + high) / 2;
                    if (sgn(pre[mid].first - pre[j].first - Pi) <= 0) {
                        idx = mid;
                        low = mid + 1;
                    } else {
                        high = mid - 1;
                    }
                }

                ll pt1 = query(j + 1, idx);
                ll pt2 = tol - pt1;
                ans = min(ans, abs(pt1 - pt2));
            }
            tol += query(j, j);
        }
    }

    printf("%I64d\n", ans);
    return 0;
}