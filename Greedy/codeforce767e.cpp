#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 100011
using namespace std;

int n;
ll m;
ll c[MAX_SIZE], w[MAX_SIZE];
int bad[MAX_SIZE];

int main() {
    int i;
    ll ans = 0;
    priority_queue<pair<ll, int>> q;
    scanf("%d%I64d", &n, &m);
    for (i = 1; i <= n; ++i) {
        scanf("%I64d", &c[i]);
    }

    for (i = 1; i <= n; ++i) {
        scanf("%I64d", &w[i]);
    }

    for (i = 1; i <= n; ++i) {
        if (c[i] % 100 == 0) continue;
        ll wt = c[i] % 100;
        m -= wt;
        q.push(make_pair(-w[i] * (100 - wt), i));
        if (m < 0) {
            m += 100;
            ans -= q.top().first;
            bad[q.top().second] = 1;
            q.pop();
        }
    }

    printf("%I64d\n", ans);
    for (i = 1; i <= n; ++i) {
        if (bad[i]) {
            ll num = c[i] / 100;
            if (c[i] % 100 != 0) num++;
            printf("%I64d %d\n", num, 0);
        } else {
            printf("%I64d %I64d\n", c[i] / 100, c[i] % 100);
        }
    }
    return 0;
}