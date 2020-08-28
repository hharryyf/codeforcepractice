#include <bits/stdc++.h>
#define MAX_SIZE 5011

using namespace std;

int a[MAX_SIZE];

int solve(int l, int r, int curr) {
    if (l > r) return 0;
    int i, mn = a[l], idx = l;
    for (i = l; i <= r; ++i) {
        if (mn > a[i]) {
            mn = a[i], idx = i;
        }
    }

    return min(solve(l, idx - 1, mn) + mn - curr + solve(idx + 1, r, mn), r - l + 1);
}

int main() {
    int n, i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) scanf("%d", &a[i]);
    printf("%d\n", solve(1, n, 0));
    return 0;
}