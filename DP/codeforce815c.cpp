#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 5011
using namespace std;
typedef long long ll;
const ll INF = 1e15;
// quite standard trick, since b is too large
// we can define dp[v][sz][0/1] as the minimum
// money required to select items in subtree v 
// with size sz, given the root v is selected --1, not selected --0.
ll dp[MAX_SIZE][MAX_SIZE][2];
ll c[MAX_SIZE], d[MAX_SIZE];
int sz[MAX_SIZE];
vector<int> g[MAX_SIZE];
int n;
ll B;
// previous cost and height
void dfs(int v) {
    int i, j;
    sz[v] = 1;
    dp[v][0][0] = 0;
    dp[v][1][0] = c[v];
    dp[v][1][1] = c[v] - d[v];
    for (auto nv : g[v]) {
        dfs(nv);
        for (i = sz[v]; i >= 0; --i) {
            for (j = 0; j <= sz[nv]; ++j) {
                dp[v][i+j][0] = min(dp[v][i+j][0], dp[v][i][0] + dp[nv][j][0]);
                dp[v][i+j][1] = min(dp[v][i+j][1], min(dp[nv][j][1], dp[nv][j][0]) + dp[v][i][1]);
            }
        }
        sz[v] += sz[nv];
    }
}

int main() {
    int i, j;
    scanf("%d%I64d", &n, &B);
    for (i = 1; i <= n; ++i) {
        scanf("%I64d%I64d", &c[i], &d[i]);
        if (i > 1) {
            int v;
            scanf("%d", &v);
            g[v].push_back(i);
        }
    }

    for (i = 0; i < MAX_SIZE; ++i) {
        for (j = 0 ; j < MAX_SIZE; ++j) {
            dp[i][j][0] = dp[i][j][1] = INF;
        }
    }

    dfs(1);

    for (i = sz[1]; i >= 0; --i) {
        if (dp[1][i][0] <= B || dp[1][i][1] <= B) {
            printf("%d\n", i);
            break;
        }
    }
    return 0;
}