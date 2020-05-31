#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define MAX_SIZE 100011
ll a[MAX_SIZE];

int main() {
    int n, i;
    ll ans = 0;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) scanf("%I64d", &a[i]);
    for (i = 1; i <= n; ++i) {
        ans += 1ll * a[i] * (n - a[i] + 1);
    }

    for (i = 2; i <= n; ++i) {
        ans -= 1ll * min(a[i], a[i-1]) * (n - max(a[i], a[i-1]) + 1);
    }

    printf("%I64d\n", ans);
    return 0;
}