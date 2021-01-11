#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

vector<int> g[MAX_SIZE];
set<int> f[MAX_SIZE];

void dfs(int v, int pre) {
    if ((int) f[v].size() >= 2) return;
    if (f[v].count(pre)) return;
    f[v].insert(pre);
    for (auto nv : g[v]) {
        dfs(nv, pre);
    }
}

int main() {
    int N, M, S, i;
    vector<int> candidate;
    scanf("%d%d%d", &N, &M, &S);
    for (i = 0 ; i < M; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        if (v == S) {
            candidate.push_back(u);
            
        } else {
            g[v].push_back(u);
        }
    }

    for (auto s : candidate) {
        dfs(s, s);
    }
    sort(candidate.begin(), candidate.end());
    vector<int> ret;
    for (auto v : candidate) {
        if ((int) f[v].size() == 1) {
            ret.push_back(v);
        }
    }

    printf("%d\n", (int) ret.size());
    for (auto v : ret) {
        printf("%d\n", v);
    }
    return 0;
}