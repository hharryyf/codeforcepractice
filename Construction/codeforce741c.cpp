#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

vector<int> g[MAX_SIZE];
int color[MAX_SIZE];
pair<int, int> edg[MAX_SIZE];

void dfs(int v) {
    for (auto nv : g[v]) {
        if (color[nv] == -1) {
            color[nv] = 1 ^ color[v];
            dfs(nv);
        }
    }
}

int main() {
    int n, i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].push_back(v2);
        g[v2].push_back(v1);
        edg[i].first = v1, edg[i].second = v2;
    }

    for (i = 1; i <= 2 * n - 1; i += 2) {
        g[i].push_back(i+1);
        g[i+1].push_back(i);
    }

    for (i = 1; i <= 2 * n; ++i) color[i] = -1;

    for (i = 1; i <= 2 * n; ++i) {
        if (color[i] == -1) {
            color[i] = 1;
            dfs(i);
        }
    }

    for (i = 1; i <= 2 * n; ++i) {
        if (color[i] == 0) color[i] = 2;
    }

    for (i = 1; i <= n; ++i) {
        printf("%d %d\n", color[edg[i].first], color[edg[i].second]);
    }
    return 0;
}