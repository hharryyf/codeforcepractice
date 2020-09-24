#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;

ll m[MAX_SIZE], a[MAX_SIZE];

int main() {
    int n, i;
    ll ans = 0;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        cin >> m[i];
        a[i] = m[i] + 1;
    }

    for (i = 2; i <= n; ++i) {
        a[i] = max(a[i-1], a[i]);
    }

    for (i = n - 1; i >= 1; --i) {
        a[i] = max(a[i], a[i+1] - 1);
    }

    for (i = 1; i <= n; ++i) {
        ans = ans + a[i] - m[i] - 1;
    }

    cout << ans << endl;
    return 0;
}