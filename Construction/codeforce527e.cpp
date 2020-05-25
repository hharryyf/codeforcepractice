#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

multiset<int> g[MAX_SIZE];
vector<pair<int, int>> edg;

void euler(int v) {
    while (!g[v].empty()) {
        int nv = *g[v].begin();
        g[nv].erase(g[nv].find(v));
        g[v].erase(g[v].find(nv));
        euler(nv);
        edg.emplace_back(v, nv);
    }
}

int main() {
    int n, m, i;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].insert(v2);
        g[v2].insert(v1);
    }

    vector<int> odd;
    for (i = 1; i <= n; ++i) {
        if ((int) g[i].size() & 1) odd.push_back(i);
    }

    for (i = 0 ; i < (int) odd.size(); i += 2) {
        g[odd[i]].insert(odd[i+1]);
        g[odd[i+1]].insert(odd[i]);
        ++m;
    }

    if (m & 1) g[1].insert(1), g[1].insert(1);

    euler(1);

    reverse(edg.begin(), edg.end());

    printf("%d\n", (int) edg.size());
    for (i = 0 ; i < (int) edg.size(); ++i) {
        if (i & 1) {
            printf("%d %d\n", edg[i].second, edg[i].first);
        } else {
            printf("%d %d\n", edg[i].first, edg[i].second);
        }
    }
    return 0;
}