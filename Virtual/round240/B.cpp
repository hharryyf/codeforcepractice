#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    ll a, b;
    int n, i;
    cin >> n >> a >> b;
    for (i = 0 ; i < n; ++i) {
        ll w;
        cin >> w;
        ll curr = w * a / b;
        ll low = 0, high = w, ans = w;
        while (low <= high) {
            ll mid = (low + high) / 2;
            if (mid * a / b == curr) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        cout << (w - ans) << " ";
    }
    return 0;
}