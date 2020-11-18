#include <bits/stdc++.h>
#define MAX_SIZE 500011
using namespace std;
vector<int> g[MAX_SIZE];
int n;
int root = 0;
vector<int> dep[MAX_SIZE];

void dfs(int v, int pre, int d) {
    int has_child = 0;
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs(nv, v, d + 1);
            has_child = 1;
        }
    }

    if (has_child == 0) {
        dep[root].push_back(d);
    }
}

int main() {
    int i;
    scanf("%d", &n);
    for (i = 1; i < n; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[v].push_back(u);
        g[u].push_back(v);
    }

    int ans = 0;
    for (auto v : g[1]) {
        root = v;
        dfs(v, 1, 0);
        sort(dep[v].begin(), dep[v].end());
        for (i = 1; i < (int) dep[v].size(); ++i) {
            dep[v][i] = max(dep[v][i], dep[v][i-1] + 1);
        }
        ans = max(ans, dep[v].back());
    }

    printf("%d\n", ans + 1);
    return 0;
}