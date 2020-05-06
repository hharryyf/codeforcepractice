#include <bits/stdc++.h>

using namespace std;
int a[1011];

int main() {
    int n, i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }

    for (i = 2; i <= n; ++i) {
        if (a[i] % a[1] != 0) {
            printf("-1\n");
            return 0;
        }
    }

    printf("%d\n", 2 * n - 1);
    printf("%d", a[1]);
    for (i = 2; i <= n; ++i) {
        printf(" %d %d", a[1], a[i]);
    }
    printf("\n");
    return 0;
}