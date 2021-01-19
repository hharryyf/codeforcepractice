#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;

int cnt[MAX_SIZE], sz[MAX_SIZE];
vector<int> g[MAX_SIZE];

void dfs(int v, int pre) {
    sz[v] = 1;
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs(nv, v);
            sz[v] += sz[nv];
        }
    }   

    cnt[sz[v]]++;
}

int main() {
    int N, i, j;
    scanf("%d", &N);
    for (i = 0 ; i < N - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);

    for (i = 2; i <= N; ++i) {
        if (N % i != 0) continue;
        int curr = 0;
        for (j = N / i; j <= N; j += N / i) {
            curr = curr + cnt[j];
        }

        if (curr == i) {
            printf("%d ", i - 1);
        }
    }
    return 0;
}