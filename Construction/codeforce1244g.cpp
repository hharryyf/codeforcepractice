#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 1000111
using namespace std;

int a[MAX_SIZE], b[MAX_SIZE];
int tmp[MAX_SIZE];

int main() {
    int n, i;
    ll k, tk;
    scanf("%d%I64d", &n, &k);
    tk = 0;
    ll tol = 1ll * n * (n + 1) / 2;
    if (k < tol) {
        printf("-1\n");
        return 0;
    }

    for (i = 1; i <= n; ++i) {
        a[i] = b[i] = i;
        tmp[i] = n - i + 1;
    }

    for (i = 1; i <= n; ++i) {
        tk += max(a[i], tmp[i]);
    }

    k = min(k, tk);

    for (i = 1; i <= n / 2; ++i) {
        // we want to do a swap between i and n - i + 1
        // the increasing in sum is 2 * (n - i + 1) - (n + 1) = 2n - 2i + 2 - n - 1 = n - 2i + 1
        int del = n - 2 * i + 1;
        if (tol + del > k) {
            del = k - tol;
            // here we want to swap i and idx
            // so that 2 * idx - (i + idx) = del
            // idx = i + del
            swap(a[i], a[i + del]);
            break;
        }

        swap(a[i], a[n - i + 1]);
        tol += del;
    }

    printf("%I64d\n", k);
    for (i = 1; i <= n; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
    for (i = 1; i <= n; ++i) {
        printf("%d ", b[i]);
    }
    printf("\n");
    tol = 0;
    for (i = 1; i <= n; ++i) {
        tol += max(a[i], b[i]);
    }

    if (tol != k) {
        printf("wrong answer!");
    }
    return 0;
}