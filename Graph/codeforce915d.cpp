#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 511
using namespace std;

vector<int> g[MAX_SIZE];
int visited[MAX_SIZE];
int cnt;

void dfs(int v) {
    visited[v] = 1;
    for (auto nv : g[v]) {
        if (!visited[nv]) dfs(nv);
        if (visited[nv] == 1) {
            cnt++;
        }
    }
    visited[v] = 2;
}

int main() {
    int n, m;
    int i, j;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].push_back(v2);
    }
    
    for (i = 1; i <= n; i++) {
        memset(visited, 0, sizeof(visited));
        cnt = 0;
        dfs(i);
        for (j = 1; j <= n; j++) {
            if (!visited[j]) dfs(j);
        }
        
        if (cnt <= 1) {
            printf("YES\n");
            return 0;
        }
    }
    
    printf("NO\n");
    return 0;
}
