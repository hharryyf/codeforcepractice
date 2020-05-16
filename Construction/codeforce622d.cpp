#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;

int a[MAX_SIZE];

int main() {
    int i, n;
    scanf("%d", &n);
    if (n == 1) {
        printf("1 1\n");
    } else if (n == 2) {
        printf("1 1 2 2\n");
    } else {
        a[1] = 1, a[n] = 1, a[n+1] = 2, a[2 * n - 1] = 2;
        for (i = 2; i <= n / 2; ++i) {
            a[i] = 2 * i - 1;
            a[n - i + 1] = 2 * i - 1;
        }

        int k = 4;
        for (i = n + 2; i <= 2 * n - 1; ++i) {
            // i, 3 * n - i
            if (i >= 3 * n - i) break;
            a[i] = a[3 * n - i] = k;
            k += 2;
        }

        for (i = 1; i <= 2 * n; ++i) {
            if (a[i] == 0) {
                a[i] = n;
            }
        }

        for (i = 1; i <= 2 * n; ++i) {
            printf("%d ", a[i]);
        }
        printf("\n");
    }
    return 0;
}