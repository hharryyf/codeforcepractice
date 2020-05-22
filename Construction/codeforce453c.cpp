#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;
int ep[MAX_SIZE], visited[MAX_SIZE];
vector<int> g[MAX_SIZE];
vector<int> path;

void add(int v) {
    visited[v]++;
    path.push_back(v);
}

void dfs(int v) {
    add(v);
    for (auto nv : g[v]) {
        if (!visited[nv]) {
            dfs(nv);
            add(v);
            if ((visited[nv] & 1) != ep[nv]) {
                add(nv);
                add(v);
            }
        }
    }
}

int main() {
    int n, m, i;
    scanf("%d%d", &n, &m);
    while (m > 0) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].push_back(v2);
        g[v2].push_back(v1);
        --m;
    }

    for (i = 1; i <= n; ++i) {
        scanf("%d", &ep[i]);
    }

    bool connected = true;
    for (i = 1; i <= n; ++i) {
        if (visited[i] == 0 && ep[i] == 1) {
            if (!connected) {
                printf("-1\n");
                return 0;
            }
            dfs(i);
            if ((visited[i] & 1) != ep[i]) {
                path.pop_back();
            }
            connected = false;
        }
    }

    printf("%d\n", (int) path.size());
    for (auto v : path) {
        printf("%d ", v);
    }
    printf("\n");
    return 0;
}
