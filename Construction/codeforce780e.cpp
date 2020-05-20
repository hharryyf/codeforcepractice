#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

vector<int> g[MAX_SIZE];
vector<int> tr[MAX_SIZE];
vector<int> path;
int visited[MAX_SIZE];
vector<int> ans[MAX_SIZE];

void dfs1(int v) {
    visited[v] = 1;
    for (auto nv : g[v]) {
        if (!visited[nv]) {
            tr[v].push_back(nv);
            dfs1(nv);
        }
    }
}

void dfs2(int v) {
    path.push_back(v);
    for (auto nv : tr[v]) {
        dfs2(nv);
        path.push_back(v);
    }
}

int main() {
    int n, m, k, i;
    scanf("%d%d%d", &n, &m, &k);
    for (i = 0 ; i < m; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }

    dfs1(1);
    dfs2(1);
    int csz = 2 * n / k;
    if ((2 * n) % k != 0) {
        csz++;
    }

    for (i = 0 ; i < (int) path.size(); ++i) {
        ans[i / csz + 1].push_back(path[i]);
    }

    for (i = 1; i <= k; ++i) {
        if (ans[i].empty()) ans[i].push_back(1);
        // sort(ans[i].begin(), ans[i].end());
        printf("%d", (int) ans[i].size());
        for (auto v : ans[i]) {
            printf(" %d", v);
        }
        printf("\n");
    }
    return 0;
}