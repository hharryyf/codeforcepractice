#include <bits/stdc++.h>
#define MAX_SIZE 111
using namespace std;

int a[MAX_SIZE], b[MAX_SIZE];
int ans[MAX_SIZE][MAX_SIZE];

int main() {
    int m, n, i, j;
    int x = 0;
    scanf("%d%d", &m, &n);
    for (i = 1; i <= m; ++i) {
        scanf("%d", &a[i]);
        x ^= a[i];
    }
    for (i = 1; i <= n; ++i) {
        scanf("%d", &b[i]);
        x ^= b[i];
    }

    if (x != 0) {
        printf("NO\n");
        return 0;
    }
    printf("YES\n");
    for (i = 1; i < m; ++i) {
        ans[i][1] = a[i];
        x ^= a[i];
    }

    ans[m][1] = b[1] ^ x;
    for (i = 2; i <= n; ++i) {
        ans[m][i] = b[i];
    }

    for (i = 1; i <= m; ++i) {
        for (j = 1; j <= n; ++j) {
            printf("%d ", ans[i][j]);
        }
        printf("\n");
    }
    return 0;
}