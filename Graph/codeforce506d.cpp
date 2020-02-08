#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 101111
using namespace std;


int f[MAX_SIZE];
unordered_map<int, int> ans[MAX_SIZE];
// stores the size of 
set<pair<int, int>> s[MAX_SIZE];
unordered_set<int> color;
vector<pair<int, int>> g[MAX_SIZE];

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    f[a] = b;
}

int get(int u, int v) {
    if (ans[u].find(v) != ans[u].end()) return ans[u][v];
    if (ans[v].find(u) != ans[v].end()) return ans[v][u];
    return -1;
}

int main() {
    int i, n, m;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) f[i] = i;
    for (i = 1; i <= m; i++) {
        int v1, v2, c;
        scanf("%d%d%d", &v1, &v2, &c);
        g[c].emplace_back(v1, v2);
    }
    
    for (i = 1; i <= m; i++) {
        for (auto v : color) {
            f[v] = v;
        }
        color.clear();
        for (auto p : g[i]) {
            unionset(p.first, p.second);
            color.insert(p.first), color.insert(p.second);
        }
        
        for (auto v : color) {
            s[v].insert(make_pair(find(v), i));
        }
    }
    int q;
    scanf("%d", &q);
    while (q > 0) {
        int u, v;
        scanf("%d%d", &u, &v);
        int ret = get(u, v);
        if (ret != -1) {
            printf("%d\n", ret);
        } else {
            ret = 0;
            if (s[u].size() < s[v].size()) {
                for (auto p : s[u]) {
                    if (s[v].find(p) != s[v].end()) ret++;
                }
            } else {
                for (auto p : s[v]) {
                    if (s[u].find(p) != s[u].end()) ret++;
                }
            }
            printf("%d\n", ret);
            ans[u][v] = ret, ans[v][u] = ret;
        }
        q--;
    }
    return 0;
}
