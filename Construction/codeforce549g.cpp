#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

int a[MAX_SIZE], offset[MAX_SIZE];
int n;

int main() {
    int i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        offset[i] = n - i + 1;
        a[i] = a[i] - offset[i];
    }

    sort(a + 1, a + 1 + n);

    for (i = 1; i <= n; ++i) {
        a[i] = a[i] + offset[i];
        if (i > 1 && a[i] < a[i-1]) {
            printf(":(\n");
            return 0;
        }
    }

    for (i = 1; i <= n; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}