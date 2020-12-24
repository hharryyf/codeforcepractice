#include <bits/stdc++.h>
#define MAX_SIZE 111
using namespace std;

int T;

int main() {
    scanf("%d", &T);
    while (T-- > 0) {
        int n, m, i, j;
        scanf("%d%d", &n, &m);
        for (i = 1; i <= n; ++i) {
            for (j = 1; j <= m; ++j) {
                int v;
                scanf("%d", &v);
                if (v % 2 != (i + j) % 2) v++;
                printf("%d ", v);
            }
            printf("\n");
        }
    }
    return 0;
}