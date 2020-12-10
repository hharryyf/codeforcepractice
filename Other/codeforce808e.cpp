#include <bits/stdc++.h>
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;

vector<int> g[4];
vector<ll> pre[4];
ll cost[MAX_SIZE << 4];

ll f(int x, int dim) {
    if (x == 0 || pre[dim].empty()) return 0;
    if (x >= (int) pre[dim].size()) return pre[dim].back();
    return pre[dim][x-1];
}

int N, M;

int main() {
    int i, j;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= N; ++i) {
        int w, c;
        scanf("%d%d", &w, &c);
        g[w].push_back(c);
    }

    for (i = 1; i <= 3; ++i) {
        sort(g[i].begin(), g[i].end(), greater<int>());
        if (g[i].empty()) continue;
        pre[i] = vector<ll>(g[i].size(), 0ll);
        pre[i][0] = g[i][0];
        for (j = 1; j < (int) g[i].size(); ++j) {
            pre[i][j] = pre[i][j-1] + g[i][j];
        }
    }

    // for all spaces calculate the maximum cost by the items of weight 1 and weight 2
    for (i = 1; i <= M; ++i) {
        int low = 0, high = i / 2;
        for (j = 0 ; j < 70; ++j) {
            int l = low + (high - low) / 3;
            int r = high - (high - low) / 3;
            if (l > r) continue;
            ll f1 = f(l, 2) + f(i - 2 * l, 1);
            ll f2 = f(r, 2) + f(i - 2 * r, 1);
            if (f1 <= f2) {
                low = l;
            } else {
                high = r;
            }
        }

        for (j = low; j <= high; ++j) {
            cost[i] = max(cost[i], f(j, 2) + f(i - 2 * j, 1));
        }
    }

    ll ans = cost[M];
    for (i = 0; i < (int) pre[3].size() && (i + 1) * 3 <= M; ++i) {
        ans = max(ans, cost[M - 3 * (i + 1)] + pre[3][i]);
    }

    printf("%I64d\n", ans);
    return 0;
}