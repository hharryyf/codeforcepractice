#include <bits/stdc++.h>
#define MAX_SIZE 1048597
typedef long long ll;
using namespace std;
const ll mod = 1000000007;
int dp[MAX_SIZE];
ll pw[MAX_SIZE];
int N;

int main() {
    int i, j;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        int v;
        scanf("%d", &v);
        dp[v]++;
    }

    pw[0] = 1;
    for (i = 1; i <= (1 << 20); ++i) {
        pw[i] = pw[i-1] * 2;
        pw[i] %= mod;
    }

    for (j = 0; j <= 19; ++j) {
        for (i = 1; i <= (1 << 20) - 1; ++i) {
            if (i & (1 << j)) continue; 
            dp[i] += dp[i ^ (1 << j)];
        }
    }

    ll ans = pw[N] - 1;
    for (i = 1; i <= (1 << 20); ++i) {
        int bt = __builtin_popcount(i);
        if (bt % 2 == 1) {
            ans = ans - (pw[dp[i]] - 1);
            ans %= mod;
        } else {
            ans = ans + (pw[dp[i]] - 1);
            ans %= mod;
        }
    }

    cout << ((ans + mod) % mod) << endl;
    return 0;
}