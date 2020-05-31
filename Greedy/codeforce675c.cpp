#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;
typedef long long ll;
ll a[MAX_SIZE];
map<ll, int> cnt;

int main() {
    int n, i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%I64d", &a[i]);
    }
    // dp[i] = max(dp[j] + 1, dp[i-1]), here j is the last index
    // sum(j+1, i) = 0, which means pre[i] == pre[j]
    ll pref = 0;
    int ans = 0;
    for (i = 1; i <= n; ++i) {
        pref += a[i];
        cnt[pref]++;
        ans = max(ans, cnt[pref]);
    }

    printf("%d\n", n - ans);
    return 0;
}