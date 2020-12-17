#include <bits/stdc++.h>
#define MAX_SIZE 200011
typedef long long ll;
using namespace std;

ll dp[MAX_SIZE];
pair<ll, ll> itv[MAX_SIZE];
vector<ll> disc;
ll N;
int M;

int main() {
    int i;
    scanf("%I64d%d", &N, &M);
    disc = vector<ll>(M + 1, 0);
    for (i = 1; i <= M; ++i) {
        scanf("%I64d%I64d", &itv[i].second, &itv[i].first);
        disc[i] = itv[i].first;
    }

    sort(itv + 1, itv + 1 + M);
    sort(disc.begin(), disc.end());
    for (i = 1; i <= M; ++i) {
        dp[i] = dp[i-1];
        int idx = lower_bound(disc.begin(), disc.end(), itv[i].second) - disc.begin() - 1;
        dp[i] = max(dp[i], dp[idx] + (itv[i].first -  itv[i].second + 1));
    }

    printf("%I64d\n", N - dp[M]);
    return 0;
}