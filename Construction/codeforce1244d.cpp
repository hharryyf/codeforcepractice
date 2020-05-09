#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 100111
using namespace std;

ll cost[MAX_SIZE][4];
int permu[6][3] = {{1,2,3},{1,3,2},{2,1,3},{2,3,1},{3,1,2},{3,2,1}};
vector<int> g[MAX_SIZE];
int n;
ll ans = 1e18, curr = 0;
int ret[MAX_SIZE];

void dfs(int v, int pre, int dep, int dim, int tp=0) {
    curr += cost[v][permu[dim][dep % 3]];
    if (tp == 1) {
        ret[v] = permu[dim][dep % 3];
    }
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs(nv, v, dep + 1, dim, tp);
        }
    }
}

int main() {
    int i;
    scanf("%d", &n);
    for (int j = 1; j <= 3; ++j) {
        for (i = 1; i <= n; ++i) {
            scanf("%I64d", &cost[i][j]);
        }
    }

    for (i = 1; i < n; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].push_back(v2);
        g[v2].push_back(v1);
        if ((int) g[v1].size() > 2 || (int) g[v2].size() > 2) {
            printf("-1\n");
            return 0;
        }
    }

    int pos = 1;
    for (i = 1; i <= n; ++i) {
        if ((int) g[i].size() == 1) {
            pos = i;
            break;
        }
    }
    int index = 0;
    for (i = 0 ; i < 6; ++i) {
        curr = 0;
        dfs(pos, 0, 0, i);
        if (ans >= curr) {
            ans = min(ans, curr);
            index = i;
        }
    }

    printf("%I64d\n", ans);
    dfs(pos, 0, 0, index, 1);
    for (i = 1; i <= n; ++i) printf("%d ", ret[i]);
    return 0;
}