#include <bits/stdc++.h>
#define MAX_SIZE 111
using namespace std;

int a[MAX_SIZE];

int main() {
    int n, i, zero = 0, sm = 0, cnt = 0;
    scanf("%d", &n);
    for (i = 1; i <= 2 * n - 1; ++i) {
        scanf("%d", &a[i]);
        if (a[i] < 0) cnt++;
        sm += abs(a[i]);
        if (a[i] == 0) zero = 1;
    }

    if (n % 2 == 1) {
        printf("%d\n", sm);
        return 0;
    } 

    if (cnt % 2 == 1) cnt += zero;

    if (cnt % 2 == 0) {
        printf("%d\n", sm);
    } else {
        int mn = 1001;
        for (i = 1; i <= 2 * n - 1; ++i) {
            mn = min(abs(a[i]), mn);
        }
        printf("%d\n", sm - 2 * mn);
    }
    return 0;
}