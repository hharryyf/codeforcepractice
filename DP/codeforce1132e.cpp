#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll W, cnt[9];
ll curr[9];
ll up[9], down[9];

int main() {
    int i;
    ll tol = 0;
    cin >> W;
    for (i = 1; i <= 8; ++i) {
        cin >> cnt[i];
        tol += cnt[i] * i;
    }

    if (tol <= W) {
        cout << tol << endl;
        return 0;
    }

    tol = 0;
    for (i = 1; i <= 8; ++i) {
        curr[i] = min(cnt[i], (W + 8 - tol) / i);
        tol += curr[i] * i;
    }

    for (i = 1; i <= 8; ++i) {
        up[i] = min(cnt[i] - curr[i], 1ll * 8);
        down[i] = min(curr[i], 1ll * 8);
    }

    vector<int> cost;
    for (i = 1; i <= 8; ++i) {
        while (up[i] > 0) {
            cost.push_back(i);
            up[i]--;
        }

        while (down[i] > 0) {
            cost.push_back(-i);
            down[i]--;
        }
    }
/*
    for (auto v : cost) {
        cout << v << " ";
    }*/
    set<int> visited;
    visited.insert(0);
    for (auto v : cost) {
        vector<int> ist;
        for (auto nv : visited) {
            if (abs(nv + v) > 289) continue;
            if (visited.find(nv + v) != visited.end()) continue;
            ist.push_back(nv + v);
            // cout << "insert " << nv + v << endl;
        }

        for (auto nv : ist) visited.insert(nv);
    }

    // cout << "here" << endl;
    ll c;
    for (c = W; c >= W - 8; --c) {
        if (visited.count(c - tol)) {
            cout << c << endl;
            break;
        }
    }
    return 0;
}