#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;

vector<pair<int, int>> edg;
vector<int> odd;
// to->id
multiset<int> g[MAX_SIZE];
vector<pair<int, int>> ans;
vector<int> sel;

void euler(int v) {
    while (!g[v].empty()) {
        auto nv = *g[v].begin();
        g[v].erase(g[v].find(nv));
        g[nv].erase(g[nv].find(v));
        euler(nv);
        edg.emplace_back(v, nv);
    }
}

int main() {
    int n, m, i, j;
    scanf("%d%d", &n, &m);
    i = 1;
    while (i <= m) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].insert(v2);
        g[v2].insert(v1);
        ++i;
    }

    for (i = 1; i <= n; ++i) {
        if ((int) g[i].size() % 2 == 1) {
            odd.push_back(i);
        }
    }

    j = m + 1;
    for (i = 0 ; i < (int) odd.size(); ++i) {
        g[odd[i]].insert(0);
        g[0].insert(odd[i]);
        ++j;
    }

    for (j = 1; j <= n; ++j) {
        if (!g[j].empty()) {
            euler(j);

            reverse(edg.begin(), edg.end());

            for (i = 0 ; i < (int) edg.size(); ++i) {
                if (i == 0) {
                    sel.push_back(edg[i].first);
                }
                sel.push_back(edg[i].second);
            }

           
            for (i = 0 ; i + 1 < (int) sel.size(); i += 2) {
                if (sel[i] != 0 && sel[i+1] != 0) {
                    ans.emplace_back(sel[i], sel[i+1]);
                }
            }

            for (i = 1; i + 1 < (int) sel.size(); i += 2) {
                int nxt = i + 2;
                if (nxt == (int) sel.size()) nxt = 1;
                if (!(sel[i-1] && sel[i] && sel[i+1] && sel[nxt]) && sel[i] && sel[i+1]) {
                    ans.emplace_back(sel[i], sel[i+1]);
                }
            }
            sel.clear();
            edg.clear();
        }
    }

    printf("%d\n", (int) ans.size());
    for (auto p : ans) {
        printf("%d %d\n", p.first, p.second);
    }
    return 0;
}