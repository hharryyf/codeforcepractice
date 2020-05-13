#include <bits/stdc++.h>
#define MAX_SIZE 500011
using namespace std;

vector<int> g[MAX_SIZE];
vector<int> ret;
int visited[MAX_SIZE];
bool flag = true;

void dfs(int v) {
    visited[v] = 1;
    for (auto nv : g[v]) {
        if (visited[nv] == 1) {
            flag = false;
        } else if (visited[nv] == 0) {
            dfs(nv);
        }
    }

    ret.push_back(v);
    visited[v] = 2;
}

int main() {
    int n, m, i, j;
    // the vertices we care are from 1 to m
    // the additional nodes are from m + 1
    scanf("%d%d", &n, &m);
    int add = m + 1;
    for (i = 1; i <= n; ++i) {
        vector<pair<int, int>> vc;
        vector<int> disc;
        vector<int> index;
        for (j = 1; j <= m; ++j) {
            int value;
            scanf("%d", &value);
            if (value != -1) {
                vc.emplace_back(value, j);
            }
        }

        sort(vc.begin(), vc.end());
        for (auto v : vc) {
            if (disc.empty() || v.first != disc.back()) {
                disc.push_back(v.first);
                index.push_back(add);
                add += 2;
            }
        }

        for (auto v : vc) {
            int idx = lower_bound(disc.begin(), disc.end(), v.first) - disc.begin();
            g[index[idx]].push_back(v.second);
            g[v.second].push_back(index[idx] + 1);
        }

        for (j = 0 ; j < (int) index.size() - 1; ++j) {
            g[index[j] + 1].push_back(index[j + 1]);
        }
    }

    for (i = 1; i <= add; ++i) {
        g[0].push_back(i);
    }

    dfs(0);
    if (!flag) {
        printf("-1\n");
        return 0;
    }
    reverse(ret.begin(), ret.end());

    for (auto r : ret) {
        if (r >= 1 && r <= m) {
            printf("%d ", r);
        }
    }

    printf("\n");
    return 0;
}