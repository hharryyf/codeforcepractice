#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<ll> g[12];

void preprocess() {
    int i;
    for (i = 0 ; i < 9; ++i) {
        g[0].push_back(i);
    }

    for (i = 0 ; i <= 10; ++i) {
        for (auto v : g[i]) {
            g[i+1].push_back(1ll * 10 * v + 9);
        }
    }
}



int main() {
    preprocess();
    ll n;
    cin >> n;
    int pos = 11;
    for (int i = 11; i >= 0; --i) {
        if (g[i][0] <= n + (n-1)) {
            pos = i;
            break;
        }
    }

    ll ans = 0;
    for (auto v : g[pos]) {
        if (v > n + (n-1)) break;
        ll L = max(1ll, v - n);
        ll R = min(v - 1, n);
        if (L <= R) ans += (R - L + 1) / 2;    
    }

    cout << ans << endl;
    return 0;
}