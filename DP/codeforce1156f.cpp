#include <bits/stdc++.h>
#define MAX_SIZE 5011
typedef long long ll;
using namespace std;
const ll mod = 998244353;
ll dp[MAX_SIZE][MAX_SIZE], tol[MAX_SIZE][MAX_SIZE];
ll inv[MAX_SIZE];
int cnt[MAX_SIZE], a[MAX_SIZE];
int tmp[MAX_SIZE];
vector<int> disc;

ll fastpower(ll val, ll p) {
    ll ret = 1;
    while (p > 0) {
        if (p % 2 == 1) {
            ret = ret * val;
            ret %= mod;
            --p;
        } else {
            val = val * val;
            val %= mod;
            p /= 2;
        }
    }
    return ret;
}

int main() {
    int n, i, j;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        tmp[i] = a[i];
    }
    
    sort(tmp + 1, tmp + 1 + n);
    for (i = 1; i <= n; ++i) {
        if (i == 1 || tmp[i] != tmp[i-1]) {
            disc.push_back(tmp[i]);
        }
    }

    int sz = disc.size();
    for (i = 1; i <= n; ++i) {
        int idx = lower_bound(disc.begin(), disc.end(), a[i]) - disc.begin() + 1;
        cnt[idx]++;
    }
    // inv[0] = 1;
    for (i = 1; i <= n; ++i) {
        inv[i] = fastpower(i, mod - 2);
    }
    // dp[i][j] = probability of winning if you move i times and the last
    // pick is j
    // dp[i][j] = (sum(dp[i+1][k], k > j) + (cnt[j] - 1)) / (N - j)
    for (i = n-1; i >= 0; --i) {
        for (j = sz; j >= 0; --j) {
            dp[i][j] = tol[i+1][j+1] + max(cnt[j] - 1, 0);
            dp[i][j] *= inv[n - i];
            dp[i][j] %= mod;
            if (dp[i][j] < 0) dp[i][j] += mod;
            tol[i][j] = tol[i][j] + tol[i][j+1] + dp[i][j] * cnt[j];
            tol[i][j] %= mod;
            if (tol[i][j] < 0) tol[i][j] += mod; 
            // cout << i << " " << j << "= " << dp[i][j] << endl;
        }
    }

    printf("%I64d\n", dp[0][0]);
    return 0;
}