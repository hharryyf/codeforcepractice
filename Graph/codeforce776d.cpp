#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;
// (v, color)
vector<pair<int, int>> g[MAX_SIZE];
int color[MAX_SIZE];
int a[MAX_SIZE];
pair<int, int> cl[MAX_SIZE];
bool fail = false;

void dfs(int v) {
    // cout << v << " " << color[v] << endl;
    for (auto ne : g[v]) {
        int nv = ne.first;
        int c = ne.second;
        if (color[nv] == -1) {
            color[nv] = c ^ color[v];
            dfs(nv);
        }
        
        if ((color[v] ^ color[nv]) != c) {
            fail = true;
        }
    }
}

int main() {
    int i, n, m;
    memset(color, -1, sizeof(color));
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for (i = 1; i <= m; ++i) {
        int v;
        scanf("%d", &v);
        while (v-- > 0) {
            int p;
            scanf("%d", &p);
            if (cl[p].first == 0) {
                cl[p].first = i;
            } else {
                cl[p].second = i;
            }
        }
    }

    for (i = 1; i <= n; ++i) {
        g[cl[i].first].emplace_back(cl[i].second, 1 ^ a[i]);
        g[cl[i].second].emplace_back(cl[i].first, 1 ^ a[i]);
        // cout << "addedge " << cl[i].first << " " << cl[i].second << " " << (1 ^ a[i]) << endl;
    }

    for (i = 1; i <= m; ++i) {
        if (color[i] == -1) {
            color[i] = 1;
            dfs(i);
            if (fail) {
                printf("NO\n");
                return 0;
            }
        }
    }

    printf("YES\n");
    return 0;
}