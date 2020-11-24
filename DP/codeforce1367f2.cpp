#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

int a[MAX_SIZE], tmp[MAX_SIZE], dp[MAX_SIZE][3];
int pos[MAX_SIZE], l[MAX_SIZE], tol[MAX_SIZE], r[MAX_SIZE];
vector<int> disc;

int main() {
    int T, N, i;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        for (i = 0 ; i <= N; ++i) {
            dp[i][0] = dp[i][1] = dp[i][2] = pos[i] = l[i] = r[i] = tol[i] = 0;
        }

        disc.clear();
        for (i = 1; i <= N; ++i) {
            scanf("%d", &a[i]);
            tmp[i] = a[i];
        }

        sort(tmp + 1, tmp + 1 + N);
        for (i = 1; i <= N; ++i) {
            if (i == 1 || tmp[i] != tmp[i-1]) {
                disc.push_back(tmp[i]);
            }
        }        

        for (i = 1; i <= N; ++i) {
            int idx = lower_bound(disc.begin(), disc.end(), a[i]) - disc.begin() + 1;
            a[i] = idx;  
            if (l[a[i]] == 0) {
                l[a[i]] = i;
            }
            r[a[i]] = i;
            tol[idx]++;
        }

        int ans = 0;
        for (i = 1; i <= N; ++i) {
            dp[i][0] = dp[pos[a[i]]][0] + 1;
            dp[i][1] = max(dp[pos[a[i]]][1] + 1, max(dp[pos[a[i] - 1]][0] + 1, dp[pos[a[i] - 1]][2] + 1));
            if (i == r[a[i]]) {
                dp[i][2] = dp[l[a[i]]][1] + tol[a[i]] - 1;
            }
            pos[a[i]] = i;
            ans = max(ans, dp[i][0]);
            ans = max(ans, dp[i][1]);
            ans = max(ans, dp[i][2]);
        }

        printf("%d\n", N - ans);
    }


    return 0;
}