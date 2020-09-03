#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 100111
using namespace std;
// dp[i] answer at st[1:i]
// g[i] answer at st[1:i] if there's a matching at st[i-|pt|+1:i]
int f[MAX_SIZE], dp[MAX_SIZE], p[MAX_SIZE];
char st[MAX_SIZE], pt[MAX_SIZE];
int N, M;

bool check(int ed) {
    int i;
    if (ed < M) return false;
    for (i = ed - M + 1; i <= ed; ++i) {
        if (st[i] != pt[i - ed + M] && st[i] != '?') return false;
    }

    return true;
}

int main() {
    int i, j = 0;
    scanf("%s", st+1);
    scanf("%s", pt+1);
    N = strlen(st+1), M = strlen(pt+1);
    for (i = 2; i <= M; ++i) {
        while (j > 0 && pt[i] != pt[j+1]) j = p[j];
        if (pt[i] == pt[j+1]) ++j;
        p[i] = j;
    }

    for (i = 1; i <= N; ++i) {
        dp[i] = dp[i-1];
        if (check(i)) {
            f[i] = dp[i - M] + 1;
            for (j = p[M]; j > 0; j = p[j]) {
                f[i] = max(f[i],f[i - (M - j)] + 1); 
            }

            dp[i] = max(dp[i], f[i]);
        }
    }

    printf("%d\n", dp[N]);
    return 0;
}