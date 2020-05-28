#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

vector<pair<int, int>> X[MAX_SIZE];
vector<pair<int, int>> Y[MAX_SIZE];
vector<int> g[MAX_SIZE];
int color[MAX_SIZE];
int n;

void dfs(int v) {
    for (auto nv : g[v]) {
        if (color[nv] == -1) {
            color[nv] = 1 ^ color[v];
            dfs(nv);
        }
    }
}

int main() {
    int i, j;
    scanf("%d", &n);
    for (i = 0 ; i < MAX_SIZE; ++i) color[i] = -1;

    for (i = 1; i <= n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        X[x].emplace_back(y, i);
        Y[y].emplace_back(x, i);
    }

    for (i = 0; i < MAX_SIZE; ++i) {
        sort(X[i].begin(), X[i].end());
        sort(Y[i].begin(), Y[i].end());
    }

    for (i = 0; i < MAX_SIZE; ++i) {
        for (j = 0 ; j + 1 < (int) X[i].size(); j += 2) {
            g[X[i][j].second].push_back(X[i][j+1].second);
            g[X[i][j+1].second].push_back(X[i][j].second);
        }
    }

    for (i = 0; i < MAX_SIZE; ++i) {
        for (j = 0 ; j + 1 < (int) Y[i].size(); j += 2) {
            int v1 = Y[i][j].second, v2 = Y[i][j+1].second;
            g[v1].push_back(v2);
            g[v2].push_back(v1);
        }
    }

    for (i = 1; i <= n; ++i) {
        if (color[i] == -1) {
            color[i] = 0;
            dfs(i);
        }
    }

    for (i = 1; i <= n; ++i) {
        if (color[i] == 0) {
            printf("b");
        } else {
            printf("r");
        }
    }
    printf("\n");
    return 0;
}