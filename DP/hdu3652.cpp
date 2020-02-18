#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int dp[11][14][11][2];
int a[11];

void init() {
    int i, j, k, l;
    for (i = 0 ; i < 11; i++) {
        for (j = 0; j < 14; j++) {
            for (k = 0 ; k < 11; k++) {
                for (l = 0 ; l < 2; l++) dp[i][j][k][l] = -1;
            }
        }
    }
}

int dfs(int pos, int rem, int pre, bool has13, bool limit) {
    if (pos < 0) return (rem == 0 && has13);
    if (!limit && dp[pos][rem][pre][has13] != -1) return dp[pos][rem][pre][has13];
    int up = limit ? a[pos] : 9;
    int i;
    int ans = 0;
    for (i = 0 ; i <= up; i++) {
        ans += dfs(pos - 1, (rem * 10 + i) % 13, i, (has13 || (pre == 1 && i == 3)), (limit && i == up));
    }
    
    if (!limit) dp[pos][rem][pre][has13] = ans;
    return ans;
}

int main() {
    int n;
    
    while (scanf("%d", &n) != EOF) {
        init();
        int len = 0;
        while (n > 0) {
            a[len++] = n % 10;
            n /= 10;
        }
        
        printf("%d\n", dfs(len - 1, 0, -1, false, true));
    }
    return 0;
}
