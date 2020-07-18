#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

vector<pair<int, int>> g[MAX_SIZE];
pair<pair<int, int>,pair<int, int>> coord[MAX_SIZE];
int occ[MAX_SIZE];
int visited[MAX_SIZE];
int n;
bool valid = false;

vector<int> ret[2];
vector<int> ans;

void init() {
    int i;
    valid = true;
    for (i = 1; i <= n; ++i) {
        g[i].clear();
        coord[i].first.first = coord[i].first.second = 0;
        coord[i].second.first = coord[i].second.second = 0;
        occ[i] = 0;
        visited[i] = -1;
    }

    ret[0].clear();
    ret[1].clear();
    ans.clear();
}

void dfs(int v) {
    for (auto ne : g[v]) {
        int nv = ne.first;
        if (visited[nv] == -1) {
            visited[nv] = visited[v] ^ ne.second;
            ret[visited[nv]].push_back(nv);
            dfs(nv);
        } else if ((visited[nv] ^ visited[v]) != ne.second) {
            valid = false;
        }
    }
}

void solve() {
    int i;
    for (i = 1; i <= n; ++i) {
        if (coord[i].first.first != coord[i].second.first) {
            if (coord[i].first.second != coord[i].second.second) {
                g[coord[i].first.second].emplace_back(coord[i].second.second, 0);
                g[coord[i].second.second].emplace_back(coord[i].first.second, 0);
            }
        } else {
            g[coord[i].first.second].emplace_back(coord[i].second.second, 1);
            g[coord[i].second.second].emplace_back(coord[i].first.second, 1);
        }
    }

    for (i = 1; i <= n; ++i) {
        if (visited[i] == -1) {
            visited[i] = 1;
            ret[1].push_back(i);
            dfs(i);
            if (ret[0].size() < ret[1].size()) {
                for (auto v : ret[0]) ans.push_back(v);
            } else {
                for (auto v : ret[1]) ans.push_back(v);
            }
            ret[0].clear();
            ret[1].clear();
        }
    }

    if (!valid) {
        printf("-1\n");
    } else {
        printf("%d\n", (int) ans.size());
        for (auto v : ans) {
            printf("%d ", v);
        }
        printf("\n");
    }
}

int main() {
    int T, i;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &n);
        init();
        for (i = 1; i <= n; ++i) {
            int v;
            scanf("%d", &v);
            if (coord[v].first.first == 0) {
                coord[v].first.first = 1;
                coord[v].first.second = i;
            } else {
                coord[v].second.first = 1;
                coord[v].second.second = i;
            }
            occ[v]++;
        }

        for (i = 1; i <= n; ++i) {
            int v;
            scanf("%d", &v);
            if (coord[v].first.first == 0) {
                coord[v].first.first = 2;
                coord[v].first.second = i;
            } else {
                coord[v].second.first = 2;
                coord[v].second.second = i;
            }
            occ[v]++;
        }

        for (i = 1; i <= n; ++i) {
            if (occ[i] != 2) {
                valid = false;
            }
        }

        if (!valid) {
            printf("-1\n");
            continue;
        }

        solve();
    }
    return 0;
}