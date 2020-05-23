#include <bits/stdc++.h>
#define MAX_SIZE 200011
typedef long long ll;
using namespace std;

ll dp[MAX_SIZE][10];
const ll inf = 1e15;
// from -> from + 1
void update(int from, vector<ll> &item) {
    sort(item.begin(), item.end());
    ll cost = 0;
    for (auto it : item) {
        cost += it;
    }
    int i;
    int len = item.size();
    for (i = 0 ; i < 10; ++i) {
        ll delta = 0;
        if (i + len >= 10) {
            delta = item.back();
        }
        dp[from+1][(i+len) % 10] = max(dp[from+1][(i+len) % 10], dp[from][i] + cost + delta);
    }
}

int main() {
    int i, n, j;
    scanf("%d", &n);
    for (i = 1; i < 10; ++i) dp[0][i] = -inf;
    for (i = 0; i < n; ++i) {
        int k;
        scanf("%d", &k);
        vector<ll> c1, c2, c3;
        while (k > 0) {
            int c;
            ll d;
            scanf("%d%I64d", &c, &d);
            if (c == 1) {
                c1.push_back(d);
            } else if (c == 2) {
                c2.push_back(d);
            } else {
                c3.push_back(d);
            }
            --k;
        }

        for (j = 0 ; j < 10; ++j) {
            // initialize with no choice
            dp[i+1][j] = dp[i][j];
        }

        sort(c1.begin(), c1.end());
        sort(c2.begin(), c2.end());
        sort(c3.begin(), c3.end());
        vector<ll> item;
        // case 1: we select cost 3 max
        if (!c3.empty()) {
            item.push_back(c3.back());
            update(i, item);
        }

        if (!c2.empty()) {
            item.clear(), item.push_back(c2.back());
            update(i, item);
            if (!c1.empty()) {
                item.push_back(c1.back());
                update(i, item);
            }
        }

        if (!c1.empty()) {
            item.clear();
            j = 0;
            while (j < 3 && !c1.empty()) {
                item.push_back(c1.back());
                c1.pop_back();
                update(i, item);
                j++;
            }
        }
    }

    ll ans = 0;
    for (i = 0 ; i < 10; ++i) {
        ans = max(ans, dp[n][i]);
    }

    printf("%I64d\n", ans);
    return 0;
}