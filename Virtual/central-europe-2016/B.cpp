#include <bits/stdc++.h>
#define MAX_SIZE 20
using namespace std;

char st[MAX_SIZE][MAX_SIZE];
int bt[2][MAX_SIZE];
int tol[2][(1 << MAX_SIZE) + 11];
int a[MAX_SIZE], b[MAX_SIZE];
int dp[2][(1 << MAX_SIZE) + 11];
int N, M;

int main() {
    int i, j;
    scanf("%d%d", &N, &M);
    for (i = 0; i < N; ++i) {
        scanf("%s", st[i]);
    }

    for (i = 0; i < N; ++i) scanf("%d", &a[i]);
    for (i = 0 ; i < M; ++i) scanf("%d", &b[i]);

    for (i = 0 ; i < N; ++i) {
        int curr = 0;
        for (j = 0 ; j < M; ++j) {
            curr = curr * 2 + (st[i][j] - '0');
        }
        bt[0][i] = curr;
    }

    for (i = 0 ; i < M; ++i) {
        int curr = 0;
        for (j = 0 ; j < N; ++j) {
            curr = curr * 2 + (st[j][i] - '0');
        }
        bt[1][i] = curr;
    }

    for (i = 0 ; i < (1 << N); ++i) {
        int curr = 0;
        for (j = 0 ; j < N; ++j) {
            if (i & (1 << j)) {
                curr = curr | bt[0][j];
                tol[0][i] += a[j];
            }
        }
        dp[0][i] = min(__builtin_popcount(curr), __builtin_popcount(i));
        for (j = 0 ; j < N; ++j) {
            if (i & (1 << j)) {
                dp[0][i] = min(dp[0][i], dp[0][i ^ (1 << j)] + dp[0][1 << j]);
            }
        }
    }

    for (i = 0 ; i < (1 << M); ++i) {
        int curr = 0;
        for (j = 0 ; j < M; ++j) {
            if (i & (1 << j)) {
                curr = curr | bt[1][j];
                tol[1][i] += b[j];
            }
        }
        dp[1][i] = min(__builtin_popcount(curr), __builtin_popcount(i));
        for (j = 0 ; j < N; ++j) {
            if (i & (1 << j)) {
                dp[1][i] = min(dp[1][i], dp[1][i ^ (1 << j)] + dp[1][1 << j]);
            }
        }
    }

    int T;
    scanf("%d", &T);
    vector<int> ret;
    for (i = 0; i < (1 << M); ++i) {
        if (dp[1][i] == __builtin_popcount(i)) {
            ret.push_back(tol[1][i]);
        }
    }
    long long ans = 0;
    int sz = ret.size();
    sort(ret.begin(), ret.end());
    for (i = 0 ; i < (1 << N); ++i) {
        if (dp[0][i] == __builtin_popcount(i)) {
            int idx = lower_bound(ret.begin(), ret.end(), T - tol[0][i]) - ret.begin();
            ans = ans + max(0, sz - idx);
        }
    }

    cout << ans << endl;
    return 0;
}