#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 200011
using namespace std;
// the dp itself is very simple, the only difficulty is to realize
// the minimum path cover for tree can be found by dp ...

int dp[MAX_SIZE][2];
ll X, Y;
vector<int> g[MAX_SIZE];
int N;

void dfs(int v, int pre) {
    dp[v][0] = dp[v][1] = MAX_SIZE;
    vector<pair<int, int>> nxt;
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs(nv, v);
            nxt.emplace_back(dp[nv][0], dp[nv][1]);
        }
    }

    if (nxt.empty()) {
        dp[v][0] = dp[v][1] = 1;
    } else if ((int) nxt.size() == 1) {
        dp[v][0] = min(nxt.front().first, nxt.front().second + 1);
        dp[v][1] = min(nxt.front().second + 1, nxt.front().first);
    } else {
        int sm = 0;
        dp[v][0] = 1;
        vector<int> diff;
        for (auto np : nxt) {
            dp[v][0] += np.second;
            sm = sm + np.second;
            diff.push_back(np.first - np.second);
        }

        sort(diff.begin(), diff.end());
        dp[v][0] = min(dp[v][0], sm + diff[0]);
        dp[v][1] = min(dp[v][0], sm + diff[0] + diff[1] - 1);
    }
}

int main() {
    int i;
    scanf("%d%I64d%I64d", &N, &X, &Y);
    for (i = 1; i < N; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    if (X > Y) {
        bool ok = false;
        for (i = 1; i <= N; ++i) {
            if ((int) g[i].size() == N - 1) {
                ok = true;
            }
        }

        if (ok) {
            printf("%I64d\n", Y * (N - 2) + X);
        } else {
            printf("%I64d\n", Y * (N - 1));
        }
    } else {
        dfs(1, 0);
        // cout << dp[1][1] << " " << dp[1][0] << endl;
        printf("%I64d\n",  Y * (min(dp[1][0], dp[1][1]) - 1) + X * (N  - min(dp[1][0], dp[1][1])));
    }
    return 0;
}