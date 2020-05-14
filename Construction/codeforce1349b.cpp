#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

int a[MAX_SIZE];

bool check(int n, int k) {
    int i, flag = 0;
    if (n == 1) return a[1] == k;
    if (n == 2) return min(a[1], a[2]) == k;
    for (i = 1; i <= n; ++i) {
        if (a[i] == k) {
            flag = 1;
            break;
        }
    }

    if (!flag) return false;

    for (i = 1; i < n; ++i) {
        if (a[i] >= k && a[i+1] >= k) {
            return true;
        }
    }

    for (i = 1; i < n - 1; ++i) {
        if (a[i] >= k && a[i+2] >= k) {
            return true;
        }
    }

    return false;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T > 0) {
        int i, n, k;
        scanf("%d%d", &n, &k);
        for (i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }

        printf("%s\n", check(n, k) ? "yes" : "no");
        --T;
    }
    return 0;
}