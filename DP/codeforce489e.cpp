#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;

const double eps = 1e-9;
double dp[MAX_SIZE];
int x[MAX_SIZE], b[MAX_SIZE], pre[MAX_SIZE];
int n, l;
bool check(double mid) {
    int i, j;
    for (i = 1; i <= n; ++i) {
        dp[i] = 1e8;
        pre[i] = 0;
    }

    for (i = 1; i <= n; ++i) {
        for (j = 0 ; j < i; ++j) {
            if (dp[i] > dp[j] + sqrt(fabs(1.0 * l - (x[i] - x[j]))) - mid * b[i]) {
                pre[i] = j;
                dp[i] = dp[j] + sqrt(fabs(1.0 * l - (x[i] - x[j]))) - mid * b[i];
            }
        }
    }
    // if (dp[n] <= eps) cout << "ok " << mid << endl;
    return dp[n] <= eps;
}

int main() {
    int i;
    scanf("%d%d", &n, &l);
    for (i = 1; i <= n; ++i) {
        scanf("%d%d", &x[i], &b[i]);
    }

    double low = 0.0, high = 5e7, ans = 5e7;
    for (i = 1; i <= 50; ++i) {
        double mid = 0.5 * (low + high);
        if (check(mid)) {
            ans = mid;
            high = mid;
        } else {
            low = mid;
        }
    }

    check(ans);
    // cout << ans << endl;
    int target = n;
    vector<int> ret;
    while (target != 0) {
        ret.push_back(target);
        target = pre[target];
    }

    reverse(ret.begin(), ret.end());
    for (auto v : ret) {
        printf("%d ", v);
    }
    return 0;
}