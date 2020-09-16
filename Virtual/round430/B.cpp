#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

int main() {
    int i, d, r;
    scanf("%d%d", &r, &d);
    int n, cnt = 0;
    scanf("%d", &n);
    for (i = 0 ; i < n; ++i) {
        int xi, yi, ri;
        scanf("%d%d%d", &xi, &yi, &ri);
        int d2 = xi * xi + yi * yi;
        // cout << "d2= " << d2 << endl;
        if (d2 >= (r - d + ri) * (r - d + ri) && ri <= r) {
            if (d2 <= (r - ri) * (r - ri)) {
                ++cnt;
                //cout << "ok " << i + 1 << endl;
            }
        }
    }

    cout << cnt << endl;
    return 0;
}