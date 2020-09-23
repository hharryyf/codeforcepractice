#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<int> q[111];
int sz[111];
int cost[111];

int main() {
    int n;
    scanf("%d", &n);
    int i, j;
    for (i = 1 ; i <= n; ++i) {
        scanf("%d", &sz[i]);
        cost[i] += sz[i] * 15;
    }

    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= sz[i]; ++j) {
            int v;
            scanf("%d", &v);
            cost[i] += v * 5;
        }
    }

    int ans = cost[1];
    for (i = 1; i <= n; ++i) {
        ans = min(ans, cost[i]);
    }

    cout << ans << endl;
    return 0;
}