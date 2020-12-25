#include <bits/stdc++.h>
using namespace std;
const int maxn = 18;
double dp[1 << maxn][maxn];
double p[maxn][maxn];
int N;

double solve(int state, int head) {
    int i;
    //cout << "state= " << state << " head= " << head << endl;
    if (((state & 1) == 0 && head != 0) || (state & (1 << head))) return 0.0;
    //cout << "pass through" << endl;
    if (state == 0 && head == 0) return 1.0;
    if (dp[state][head] >= -0.1) return dp[state][head];
    dp[state][head] = 0;
    for (i = 0 ; i < N; ++i) {
        if ((1 << i) & state) {
            dp[state][head] = max(dp[state][head], p[head][i] * solve(state ^ (1 << i), head) + p[i][head] * solve(state ^ (1 << i), i));
        }
    }

    // cout << "state " << state << ", head " << head << " dp= " << dp[state][head] << endl; 
    return dp[state][head];
}

int main() {
    int i, j;
    double ans = 0.0;
    scanf("%d", &N);
    for (i = 0; i < (1 << maxn); ++i) {
        for (j = 0 ; j < maxn; ++j) {
            dp[i][j] = -1;
        }
    }

    for (i = 0 ; i < N; ++i) {
        for (j = 0 ; j < N; ++j) {
            scanf("%lf", &p[i][j]);
        }
    }

    for (i = 0 ; i < N; ++i) {
        ans = max(ans, solve(((1 << N) - 1) ^ (1 << i), i));
    }

    printf("%.15lf\n", ans);
    return 0;
}