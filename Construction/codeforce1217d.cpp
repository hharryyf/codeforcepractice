#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

vector<pair<int, int>> g[MAX_SIZE];
int ans[MAX_SIZE];
int visited[MAX_SIZE];
bool backedge = false;

void dfs(int v) {
    visited[v] = 1;
    for (auto np : g[v]) {
        int nv = np.first, id = np.second;
        if (!visited[nv]) {
            ans[id] = 1;
            dfs(nv);
        } else if (visited[nv] == 1) {
            ans[id] = 2;
            backedge = true;
        } else {
            ans[id] = 1;
        }
    }
    visited[v] = 2;
}

int main() {
    int n, m, i;
    scanf("%d%d", &n, &m);
    for (i = 0 ; i < m; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].push_back(make_pair(v2, i));
    }

    for (i = 1; i <= n; ++i) {
        if (visited[i] == 0) {
            dfs(i);
        }
    }

    if (!backedge) {
        printf("1\n");
    } else {
        printf("2\n");
    }

    for (i = 0 ; i < m; ++i) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}