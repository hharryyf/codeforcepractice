#include <bits/stdc++.h>
#define MAX_SIZE 1000111
typedef long long ll;
using namespace std;

ll scorerank[MAX_SIZE], score[MAX_SIZE];
ll tol[MAX_SIZE], scorelz[MAX_SIZE];
int N, K;

int main() {
    int i;
    scanf("%d%d", &N, &K);
    for (i = 0 ; i < MAX_SIZE; ++i) {
        scorerank[i] = 1;
        scorelz[i] = K;
    }

    for (i = 1; i <= K; ++i) {
        int d;
        scanf("%d", &d);
        while (d-- > 0) {
            int v;
            scanf("%d", &v);
            ll v1 = scorelz[score[v]] - scorerank[score[v]] * (K - i + 1);
            ll v2 = scorelz[score[v] + 1] - scorerank[score[v] + 1] * (K - i + 1);
            tol[v] += v1 - v2;
            score[v]++;
            scorerank[score[v] - 1]++;
            scorelz[score[v] - 1] += K - i + 1;
        }
    }

    for (i = 1; i <= N; ++i) {
        double ans = tol[i] + scorelz[score[i]];
        printf("%.12lf\n", ans / K);
    }
    return 0;
}