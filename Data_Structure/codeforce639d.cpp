#include <bits/stdc++.h>
#define MAX_SIZE 200011
typedef long long ll;
using namespace std;

ll a[MAX_SIZE];

int main() {
    int i, n, k, j;
    ll ans = 2e18;
    ll b, c;
    scanf("%d%d%lld%lld", &n, &k, &b, &c);
    b = min(b, 5 * c);
    for (i = 1; i <= n; i++) scanf("%lld", &a[i]);
    sort(a + 1, a + 1 + n);
    
    for (i = 0 ; i < 5; i++) {
        ll T = 2000000000 + i;
        ll curr = 0;
        priority_queue<ll> q;
        for (j = 1; j <= n; j++) {
            ll v = a[j];
            ll cost = 0;
            while ((T - v) % 5 != 0) {
                v++;
                cost += c;
            }
            
            cost += ((T - v) / 5) * b;
            q.push(cost);
            curr += cost;
            if (q.size() > k) {
                curr -= q.top();
                q.pop();
            }
            if (q.size() == k) {
                ans = min(ans, curr - (T - v) / 5 * b * k);
            }
        }
    }
    
    printf("%lld\n", ans);
    return 0;
}
