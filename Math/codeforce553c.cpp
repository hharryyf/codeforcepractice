#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;
const int mod = 1000000007;
struct edge {
    int u, v, tp;
};

edge edg[MAX_SIZE];
int f[MAX_SIZE], color[MAX_SIZE], visited[MAX_SIZE];
vector<int> g[MAX_SIZE];
int N, M;
int ok = 1;

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int u, int v) {
    int a = find(u), b = find(v);
    f[a] = b;
}

void dfs(int v) {
    visited[v] = 1;
    for (auto nv : g[v]) {
        if (color[nv] != -1 && (color[nv] != (color[v] ^ 1))) ok = 0;
        if (!visited[nv]) {
            color[nv] = color[v] ^ 1;
            dfs(nv);
        }
    }
}

int main() {
    int i;
    for (i = 0 ; i < MAX_SIZE; ++i) {
        color[i] = -1, f[i] = i;
    }

    scanf("%d%d", &N, &M);
    for (i = 1; i <= M; ++i) {
        scanf("%d%d%d", &edg[i].u, &edg[i].v, &edg[i].tp);
        if (edg[i].tp) {
            unionset(edg[i].u, edg[i].v);
        }
    }

    for (i = 1; i <= M; ++i) {
        if (edg[i].tp == 0) {
            g[find(edg[i].u)].push_back(find(edg[i].v));
            g[find(edg[i].v)].push_back(find(edg[i].u));
        }
    }

    int cnt = 0;
    for (i = 1; i <= N; ++i) {
        if (f[i] == i && !visited[i]) {
            color[i] = 1;
            ++cnt;
            dfs(i);
        }
    }

    if (!ok) {
        printf("0\n");
        return 0;
    }

    int ret = 1;
    for (i = 0 ; i < (cnt - 1); ++i) {
        ret = ret * 2;
        ret %= mod;
    }

    printf("%d\n", ret);
    return 0;
}