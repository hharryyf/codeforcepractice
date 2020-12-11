#include <bits/stdc++.h>

using namespace std;
const int inf = 1000000000;
int dp[31111], cnt[29];
char st[200011];
int ans = 0;
int N, M, K, T;

int main() {
    int i, j, k;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d%d%d", &N, &M, &K);
        scanf("%s", st);
        int n = max(N, M);
        ans = inf;
        for (i = 0 ; i < 29; ++i) cnt[i] = 0;
        for (i = 0 ; i < K; ++i) {
            cnt[st[i] - 'A' + 1]++;
        }
        
        for (k = 1; k <= 26; ++k) {
            for (i = 0 ; i <= n; ++i) dp[i] = 0;
            dp[0] = 1;
            for (i = 1; i <= 26; ++i) {
                if (i == k) continue;
                for (j = n; j >= 0; --j) {
                    if (j >= cnt[i]) dp[j] |= dp[j - cnt[i]];
                }
            }

            for (j = n; j >= 0; --j) {
                if (dp[j] == 1) {
                    if (j <= N && j + cnt[k] >= N) {
                        int rem = max(0, M - (K - j - cnt[k]));
                        ans = min(ans, rem * (N - j));
                    }

                    if (j <= M && j + cnt[k] >= M) {
                        int rem = max(0, N - (K - j - cnt[k]));
                        ans = min(ans, rem * (M - j));
                    }
                }
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}