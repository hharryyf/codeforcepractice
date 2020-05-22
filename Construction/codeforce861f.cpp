#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

// (next, edge_id)
vector<pair<int, int>> g[MAX_SIZE];
// select means an edge is selected
int select[MAX_SIZE];
int visited[MAX_SIZE];
// invariant, all answer[i] must have even size
vector<int> ans[MAX_SIZE];
int cnt = 0;
// v and the previous edge id
void dfs(int v, int pre, int preid) {
    vector<pair<int, int>> candidate;
    visited[v] = 1; 
    for (auto nv : g[v]) {
        if (!visited[nv.first]) {
            dfs(nv.first, v, nv.second);
        }
    }

    if (pre != 0  && !select[preid]) {
        candidate.emplace_back(pre, preid);
    }

    for (auto nv : g[v]) {
        if (nv.first != pre && !select[nv.second]) {
            candidate.emplace_back(nv.first, nv.second);
        }
    }

    while ((int) candidate.size() >= 2) {
        auto p1 = candidate.back();
        candidate.pop_back();
        auto p2 = candidate.back();
        candidate.pop_back();
        ans[v].push_back(p1.first);
        ans[v].push_back(p2.first);
        select[p1.second] = select[p2.second] = 1;
        ++cnt;
    }
}

int main() {
    int n, m, i, j;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].emplace_back(v2, i);
        g[v2].emplace_back(v1, i);
    }

    for (i = 1; i <= n; ++i) {
        if (!visited[i]) {
            dfs(i, 0, 0);
        }
    }

    printf("%d\n", cnt);
    for (i = 1; i <= n; ++i) {
        for (j = 0 ; j < (int) ans[i].size(); j += 2) {
            printf("%d %d %d\n", ans[i][j], i, ans[i][j+1]);
        }
    }

    return 0;
}