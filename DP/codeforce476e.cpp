#include <bits/stdc++.h>
#define MAX_SIZE 2003
using namespace std;

int dp[MAX_SIZE][MAX_SIZE];
int lst[MAX_SIZE];
char s[MAX_SIZE], p[MAX_SIZE];
int n, m;

void calc_last(int right) {
    lst[right] = -1;
    int i = right, j = m;
    while (j >= 1 && i >= 1) {
        if (s[i] == p[j]) {
            j--;
        } 
        i--;
    }

    if (j == 0) {
        lst[right] = i + 1;
    }
}

int main() {
    int i, j;
    scanf("%s", s + 1);
    scanf("%s", p + 1);
    n = strlen(s + 1), m = strlen(p + 1);
    for (i = 1; i <= n; ++i) {
        calc_last(i);
        // printf("%d\n", lst[i]);
    }

    for (i = 1; i <= n; ++i) dp[0][i] = -1000000;
    for (i = 1; i <= n; ++i) {
        for (j = 0; j <= n; ++j) {
            dp[i][j] = -1000000;
            int len = i - lst[i] + 1;
            if (lst[i] != -1 && j >= len - m) {
                dp[i][j] = dp[lst[i] - 1][j - (len - m)] + 1;
            }
            dp[i][j] = max(dp[i][j], dp[i-1][j]);
            if (j > 0) {
                dp[i][j] = max(dp[i][j], dp[i-1][j-1]);
            }
        }
    }

    for (i = 0; i <= n; ++i) {
        printf("%d ", dp[n][i]);
    }
    return 0;
}