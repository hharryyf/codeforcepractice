#include <bits/stdc++.h>
#define MAX_SIZE 8011
using namespace std;
typedef long long ll;
int a[MAX_SIZE];
ll ans = 1e17;
int k;

ll check(int s) {
    int low = 1, high = k;
    int cnt = 0;
    while (low <= high) {
        if (low == high) {
            cnt++;
            break;
        } else {
            if (a[low] + a[high] <= s) {
                cnt++;
                low++, high--;
            } else {
                cnt++;
                high--;
            }
        }
    }

    return 1ll * s * cnt;
}

int main() {
    int n, i, low = 0, high = 0;
    
    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; ++i) {
        int v;
        scanf("%d", &v);
        a[v]++;
    }

    sort(a + 1, a + 1 + k);

    low = a[k];

    for (i = 1; i <= k; ++i) {
        if (i != k - i + 1) {
            high = max(high, a[i] + a[k-i+1]);
        } else {
            high = max(high, a[i]);
        }
    }

    for (i = low; i <= high; ++i) {
        ans = min(ans, check(i));
    }

    cout << ans << endl;
    return 0;
}