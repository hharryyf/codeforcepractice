#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    if (n > m) {
        swap(n, m);
    }

    if (n == 1) {
        if (m % 6 == 0) {
            printf("%d\n", m);
        } else if (m % 6 == 1) {
            printf("%d\n", m / 6 * 6);
        } else if (m % 6 == 2) {
            printf("%d\n", m / 6 * 6);
        } else if (m % 6 == 3) {
            printf("%d\n", m / 6 * 6);
        } else if (m % 6 == 4) {
            printf("%d\n", m / 6 * 6 + 2);
        } else {
            printf("%d\n", m / 6 * 6 + 4);
        }
    } else if (n == 2) {
        if (m == 2) {
            printf("0\n");
        } else if (m == 3) {
            printf("4\n");
        } else if (m == 7) {
            printf("12\n");
        } else {
            printf("%I64d\n", 1ll * n * m);
        }
    } else {
        printf("%I64d\n", 1ll * n * m - ((1ll * n * m) % 2));
    }
    return 0;
}