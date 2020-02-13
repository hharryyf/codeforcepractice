#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 400111
using namespace std;

vector<int> g[MAX_SIZE];
int dep[MAX_SIZE];
int n, d, k;
int cnt;
void addedge(int v1, int v2) {
    g[v1].push_back(v2), g[v2].push_back(v1);
}

void dfs(int v, int dpt) {
    if (dpt <= 0 || cnt > n) return;
    int deg = g[v].size();
    vector<int> r;
    while (deg < k && cnt <= n) {
        addedge(v, cnt);
        r.push_back(cnt);
        cnt++;
        deg++;
    }
    
    for (auto nv : r) {
        dfs(nv, dpt - 1);
    }
}

int main() {
    int i, j;
    scanf("%d%d%d", &n, &d, &k);
    if (d >= n || (k == 1 && n > 2)) {
        printf("NO\n");
        return 0;
    }
    
    for (i = 1; i <= d; i++) {
        addedge(i, i + 1);
    }
    
    cnt = 1;
    i = 2, j = d;
    while (i <= j) {
        dep[i] = dep[j] = cnt;
        cnt++, i++, j--;
    }
    
    cnt = d + 2;
    for (i = 2; i <= d; i++) {
        dfs(i, dep[i]);
    }
    
    if (cnt <= n) {
        printf("NO\n");
        return 0;
    }
    
    printf("YES\n");
    for (i = 1; i <= n; i++) {
        for (auto v : g[i]) {
            if (i < v) {
                printf("%d %d\n", i, v);
            }
        }
    }
    return 0;
}
