#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int n, i;
        ll v, ans = 0, pre = 0;
        scanf("%d", &n);
        for (i = 0 ; i < n; ++i) {
            cin >> v;
            pre += v;
            if (pre < 0) ans = max(ans, 1ll * abs(pre));
        }
        cout << ans << endl;
    }
    return 0;
}