#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct point {
    ll x, y;
    point(ll x=0, ll y=0) : x(x), y(y) {}
};

ll area(const vector<point>& fig) {
    double res = 0;
    for (unsigned i = 0; i < fig.size(); i++) {
        point p = i ? fig[i - 1] : fig.back();
        point q = fig[i];
        res += (p.x - q.x) * (p.y + q.y);
    }
    return abs(res);
}

int N;

int main() {
    int i;
    ll ans = 0;
    scanf("%d", &N);
    for (i = 0 ; i < N; ++i) {
        int P;
        vector<point> curr;
        scanf("%d", &P);
        while (P-- > 0) {
            ll x, y;
            scanf("%I64d%I64d", &x, &y);
            curr.push_back(point(x, y));
        }
        ans += area(curr);
    }
    printf("%I64d\n", ans / 2);
    return 0;
}