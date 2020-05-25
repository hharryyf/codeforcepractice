#include <bits/stdc++.h>
#define MAX_SIZE 300011
using namespace std;

vector<int> g[MAX_SIZE];
set<int> s[MAX_SIZE];
int ans[MAX_SIZE << 1];

void dfs(int v, int pre) {
    set<int> bann;
    for (auto ns : s[v]) {
        if (s[pre].find(ns) != s[pre].end()) {
            bann.insert(ans[ns]);
        }
    }

    int i = 1;
    for (auto ns : s[v]) {
        if (ans[ns] == 0) {
            while (bann.find(i) != bann.end()) ++i;
            ans[ns] = i++;
        }
    }

    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs(nv, v);
        }
    }
}

int main() {
    int n, m, i;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) {
        int si;
        scanf("%d", &si);
        while (si > 0) {
            int v;
            scanf("%d", &v);
            s[i].insert(v);
            --si;
        }
    }

    for (i = 1; i < n; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }

    dfs(1, 0);

    int v = 0;
    for (i = 1; i <= m; ++i) v = max(v, ans[i]);
    printf("%d\n", max(1, v));
    for (i = 1; i <= m; ++i) {
        printf("%d ", max(1, ans[i]));
    }
    printf("\n");
    return 0;
}