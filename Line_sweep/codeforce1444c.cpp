#pragma GCC optimize("Ofast")
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;
// link with component c[i], connect vertex v1 and v2
vector<pair<int, pair<int, int>>> g[MAX_SIZE];
vector<int> sz[MAX_SIZE];
vector<int> f[MAX_SIZE];
vector<pair<int, int>> oper;
int pre[MAX_SIZE];
int c[MAX_SIZE];
int bad[MAX_SIZE];

struct edge {
    int from, to;
};

edge edg[MAX_SIZE];
int n;

void del() {
    if (oper.empty()) return;
    auto p = oper.back();
    oper.pop_back();
    if (p.first == -1) return;
    f[p.first].pop_back();
    sz[p.second].pop_back();
}

int find(int x) {
    if (f[x].back() == x) return x;
    return find(f[x].back());
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    if (a == b) {
        oper.emplace_back(-1, -1);
        return;
    }

    if (sz[a].back() > sz[b].back()) swap(a, b);
    oper.emplace_back(a, b);
    sz[b].push_back(sz[a].back() + sz[b].back());
    f[a].push_back(b);
}

int main() {
    int m, i, k, j;
    long long ans = 0;
    scanf("%d%d%d", &n, &m, &k);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &c[i]);
        // visited[c[i]] = 1;
    }

    for (i = 1; i <= 2 * n; ++i) {
        f[i].push_back(i), sz[i].push_back(1);
    }

    for (i = 1; i <= m; ++i) {
        scanf("%d%d", &edg[i].from, &edg[i].to);
        if (c[edg[i].from] == c[edg[i].to]) {
            unionset(edg[i].from, edg[i].to + n);
            unionset(edg[i].from + n, edg[i].to);
            if (find(edg[i].from) == find(edg[i].from + n)) {
                bad[c[edg[i].from]] = 1;
            }

            if (find(edg[i].to) == find(edg[i].to + n)) {
                bad[c[edg[i].from]] = 1;
            }
        } else {
            if (c[edg[i].from] < c[edg[i].to]) swap(edg[i].from, edg[i].to);
            g[c[edg[i].from]].push_back(make_pair(c[edg[i].to], make_pair(edg[i].from, edg[i].to)));
            // g[c[edg[i].to]].push_back(make_pair(c[edg[i].from], make_pair(edg[i].from, edg[i].to)));
        }     
    }

    int cnt = 0;
    for (i = 1; i <= k; ++i) {
        sort(g[i].begin(), g[i].end());
        cnt += bad[i];
        // printf("%d\n", bad[i]);
        if (bad[i] != 0) continue;
        int cnt = 0, ss = g[i].size();
        bool ok = false;
        for (j = 0 ; j < ss; ++j) {
            if (bad[g[i][j].first] != 0) continue;
            if (j > 0 && g[i][j].first != g[i][j-1].first) {
                while (cnt > 0) {
                    del();
                    --cnt;
                }
                ok = false;
            }

            unionset(g[i][j].second.first, g[i][j].second.second + n);
            unionset(g[i][j].second.first + n, g[i][j].second.second);
            cnt += 2;
            if (!ok) {
                if (find(g[i][j].second.first) == find(g[i][j].second.first + n) || 
                    find(g[i][j].second.second) == find(g[i][j].second.second + n)) {
                    ans -= 2;
                    // cout << "invalid " << i << " " << g[i][j].first << endl;
                    ok = true;
                }
            }
        }

        while (cnt > 0) {
            del();
            --cnt;
        }
    }
    ans += 1ll * (k - cnt) * (k - cnt - 1);
    ans /= 2;
    /*
    if (n == 100 && m == 1000 && k == 50) {
        cout << cnt << endl;
    }*/
    printf("%I64d\n", ans);
    return 0;
}