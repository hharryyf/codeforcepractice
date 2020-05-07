#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, i, j;
    scanf("%d", &n);
    if (n % 2 == 0) {
        printf("NO\n");
        return 0;
    }

    printf("YES\n");
    if (n == 1) {
        printf("2 1\n1 2\n");
        return 0;
    }

    printf("%d %d\n", 2 * (n + 2), n * (n + 2));
    for (i = 2; i <= n; ++i) {
        printf("1 %d\n", i);
    }

    for (i = 2; i <= n + 2; ++i) {
        for (j = i + 1; j <= n + 2; ++j) {
            if (i <= n && (j == (i ^ 1))) continue;
            printf("%d %d\n", i, j);
        }
    }
    printf("1 %d\n", n + 3);
    for (i = 2; i <= n; ++i) {
        printf("%d %d\n", 1 + n + 2, i + n + 2);
    }

    for (i = 2; i <= n + 2; ++i) {
        for (j = i + 1; j <= n + 2; ++j) {
            if (i <= n && (j == (i ^ 1))) continue;
            printf("%d %d\n", i + n + 2, j + n + 2);
        }
    }
    
    return 0;
}