#include <bits/stdc++.h>
#define MAX_SIZE 101111
using namespace std;

multiset<int> dep[MAX_SIZE];
int f[MAX_SIZE];
int tree[MAX_SIZE][26];
int ed[MAX_SIZE];
int tol = 0;
int N;

void insert(char st[]) {
    int i, j, n = strlen(st);
    for (i = 0, j = 0 ; i < n; ++i) {
        if (!tree[j][st[i] - 'a']) {
            tree[j][st[i] - 'a'] = ++tol;
        } 
        j = tree[j][st[i] - 'a'];
        if (i == n - 1) {
            ed[j] = 1;
        }
    }
}

void dfs1(int v, int d) {
    int i;
    if (ed[v]) dep[v].insert(d);
    for (i = 0 ; i < 26; ++i) {
        if (tree[v][i]) {
            dfs1(tree[v][i], d + 1);
        }
    }
}

void merge(int u, int v) {
    if (dep[f[u]].size() > dep[f[v]].size()) swap(u, v);
    for (auto nv : dep[f[u]]) {
        dep[f[v]].insert(nv);
    }
    f[u] = f[v];
}

void dfs2(int v, int d) {
    int i;
    for (i = 0 ; i < 26; ++i) {
        if (tree[v][i]) {
            dfs2(tree[v][i], d + 1);
        }
    }
    bool ok = false;
    if (dep[f[v]].empty()) {
        ok = true;
    }

    for (i = 0 ; i < 26; ++i) {
        if (tree[v][i]) {
            merge(v, tree[v][i]);
        }
    }

    if (ok && d != 0) {
        dep[f[v]].erase(dep[f[v]].find(*dep[f[v]].rbegin()));
        dep[f[v]].insert(d);
    }
}

char s[MAX_SIZE];

int main() {
    int i;
    scanf("%d", &N);
    for (i = 0 ; i < MAX_SIZE; ++i) {
        f[i] = i;
    }

    for (i = 0 ; i < N; ++i) {
        scanf("%s", s);
        insert(s);
    }

    dfs1(0, 0);
    dfs2(0, 0);
    long long ans = 0;
    for (auto v : dep[f[0]]) {
        // cout << v << endl;
        ans += v;
    }

    cout << ans << endl;
    return 0;
}