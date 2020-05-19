#include <bits/stdc++.h>
#define MAX_SIZE 5111
using namespace std;

bool dp[MAX_SIZE][MAX_SIZE];
vector<int> g[MAX_SIZE];
int n, n1, n2, n3;
int visited[MAX_SIZE];
vector<int> component[MAX_SIZE][2];
int sz = 1;
bool fail = false;
int ans[MAX_SIZE];

void dfs(int v) {
    for (auto nv : g[v]) {
        if (visited[nv] == -1) {
            visited[nv] = 1 ^ visited[v];
            component[sz][visited[nv]].push_back(nv);
            dfs(nv);
        } else if (visited[nv] == visited[v]) {
            fail = true;
        }
    }
}

int main() {
    int i, m, j;
    scanf("%d%d", &n, &m);
    scanf("%d%d%d", &n1, &n2, &n3);
    for (i = 1; i <= m; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }

    for (i = 1; i <= n; ++i) visited[i] = -1;

    for (i = 1; i <= n; ++i) {
        if (visited[i] == -1) {
            visited[i] = 0;
            component[sz][0].push_back(i);
            dfs(i);
            sz++;
        }
    }

    if (fail) {
        printf("NO\n");
        return 0;
    }

    // every set we either select component[i][0] or component[i][1]
    // if it is possible to make up the sum n2 then return true, otherwise return false
    dp[0][0] = true;
    for (i = 1; i < sz; ++i) {
        int sz1 = component[i][0].size(), sz2 = component[i][1].size();
        for (j = 0; j <= n; ++j) {
            if (j >= sz1) {
                dp[i][j] = dp[i][j] || dp[i-1][j-sz1];
            }

            if (j >= sz2) {
                dp[i][j] = dp[i][j] || dp[i-1][j-sz2];
            }
        }
    }

    if (!dp[sz - 1][n2]) {
        printf("NO\n");
        return 0;
    }
    printf("YES\n");
    i = sz - 1, j = n2;
    while (i > 0 && j > 0) {
        int sz1 = component[i][0].size(), sz2 = component[i][1].size();
        if (j >= sz1 && dp[i - 1][j - sz1]) {
            for (auto v : component[i][0]) {
                ans[v] = 2;
            }
            j -= sz1;
            --i;
        } else if (j >= sz2 && dp[i-1][j - sz2]) {
            for (auto v : component[i][1]) {
                ans[v] = 2;
            }
            j -= sz2;
            --i;
        } else {
            --i;
        }
    }

    for (i = 1; i <= n; ++i) {
        if (ans[i] == 0) {
            if (n1 > 0) {
                --n1;
                putchar('1');
            } else {
                putchar('3');
            }
        } else {
            putchar('2');
        }
    }
    return 0;
}