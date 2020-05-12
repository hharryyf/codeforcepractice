#include <bits/stdc++.h>
#define MAX_SIZE 10111
using namespace std;

int num[MAX_SIZE][4];

int main() {
    int i, n, k, j = 1;
    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; ++i) {
        num[i][0] = j;
        num[i][1] = j + 1;
        num[i][2] = j + 2;
        num[i][3] = j + 4;
        j += 6;
    }   

    int ans = 0;
    for (i = 1; i <= n; ++i) {
        for (j = 0 ; j < 4; ++j) {
            num[i][j] *= k;
            ans = max(ans, num[i][j]);
        }
    }

    printf("%d\n", ans);
    for (i = 1; i <= n; ++i) {
        for (j = 0 ; j < 4; ++j) {
            printf("%d ", num[i][j]);
        }
        printf("\n");
    }
    return 0;
}