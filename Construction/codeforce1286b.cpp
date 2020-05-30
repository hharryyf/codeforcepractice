#include <bits/stdc++.h>
#define MAX_SIZE 2011
using namespace std;

deque<int> q[MAX_SIZE];
vector<int> g[MAX_SIZE];
int c[MAX_SIZE];
int ans[MAX_SIZE];
bool valid = true;

void dfs(int v) {
    if (!valid) return;
    for (auto nv : g[v]) {
        dfs(nv);
    }

    for (auto nv : g[v]) {
        for (auto p : q[nv]) {
            q[v].push_back(p);
        }
    }

    if ((int) q[v].size() < c[v]) {
        valid = false;
        return;
    }

    q[v].insert(q[v].begin() + c[v], v);
}

int main() {
    int rt = 0;
    int i, n;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        int p;
        scanf("%d%d", &p, &c[i]);
        if (p != 0) {
            g[p].push_back(i);
        } else {
            rt = i;
        }
    }

    dfs(rt);
    // cout << rt << endl;
    if (!valid) {
        printf("NO\n");
        return 0;
    }

    printf("YES\n");

    i = 1;
    for (auto e : q[rt]) {
        ans[e] = i++;
    }

    for (i = 1; i <= n; ++i) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}