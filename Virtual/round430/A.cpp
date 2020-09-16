#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ll l, r, x, y, k;
    cin >> l >> r >> x >> y >> k;
    ll i;
    for (i = x; i <= y; ++i) {
        if (i * k >= l && i * k <= r) {
            cout << "YES" << endl;
            return 0;
        }
    }

    cout << "NO" << endl;
    return 0;
}