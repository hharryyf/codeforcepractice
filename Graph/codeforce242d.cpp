#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

int deg[MAX_SIZE];
int n, m;
vector<int> g[MAX_SIZE];

int main() {
    queue<int> q;
    scanf("%d%d", &n, &m);
    int i;
    for (i = 0 ; i < m; i++) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }
    
    unordered_set<int> h;
    for (i = 1 ; i <= n; i++) {
        scanf("%d", &deg[i]);
        if (deg[i] == 0) q.push(i);
    }
    
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (deg[v] != 0) continue;
        h.insert(v);
        deg[v]--;
        for (auto nv : g[v]) {
            deg[nv]--;
            if (deg[nv] == 0) {
                q.push(nv);
            }
        }
    }
    
    printf("%d\n", h.size());
    for (auto num : h) {
        printf("%d ", num);
    }
    if (h.size()) {
        printf("\n");
    }
    return 0;
}
