#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m, i;
    scanf("%d%d", &n, &m);
    if (m == 3 && n == 3) {
        printf("0 0\n1 0\n0 1\n");
        return 0;
    } else if (m == 3 && n == 4) {
        printf("0 0\n3 0\n0 3\n1 1\n");
        return 0;
    } else if (m == 3) {
        printf("-1\n");
        return 0;
    }

    for (i = 1; i <= m; ++i) {
        printf("%d %d\n", i, i * i + 19260817);
    }

    for (i = 1; i <= n - m; ++i) {
        printf("%d %d\n", i, -i*i - 19260817);
    }
    return 0;
}