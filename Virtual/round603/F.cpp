#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 2111
using namespace std;

vector<int> g[MAX_SIZE][2];
int L[MAX_SIZE][2], R[MAX_SIZE][2];
int val[MAX_SIZE][MAX_SIZE][2];
int sz[MAX_SIZE][2];
int dp[MAX_SIZE];
int n, a, b;

void dfs(int v, int dim) {
    sz[v][dim] = (v != 1);
    for (auto nv : g[v][dim]) {
        dfs(nv, dim);
        sz[v][dim] += sz[nv][dim];
        L[v][dim] = min(L[nv][dim], L[v][dim]);
        R[v][dim] = max(R[nv][dim], R[v][dim]);
    }

    val[L[v][dim]][R[v][dim]][dim] = max(val[L[v][dim]][R[v][dim]][dim], sz[v][dim]);
}

int main() {
    int i, j;
    for (i = 0 ; i < MAX_SIZE; ++i) L[i][0] = L[i][1] = MAX_SIZE, R[i][0] =  R[i][1] = -MAX_SIZE;
    scanf("%d%d", &n, &a);
    for (i = 1; i < a; ++i) {
        int p;
        scanf("%d", &p);
        g[p][0].push_back(i+1);
    }

    for (i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        L[x][0] = R[x][0] = i;
    }

    scanf("%d", &b);

    for (i = 1; i < b; ++i) {
        int p;
        scanf("%d", &p);
        g[p][1].push_back(i+1);
    }

    for (i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        L[x][1] = R[x][1] = i;
    }

    dfs(1, 0);
    dfs(1, 1);

    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= i; ++j) {
            dp[i] = max(dp[i], dp[j-1] + max(val[j][i][0], val[j][i][1]));
        }
    }

    printf("%d\n", dp[n]);
    return 0;
}