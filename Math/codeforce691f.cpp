#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 3000111
typedef long long ll;
using namespace std;

int cnt[MAX_SIZE];
ll prcnt[MAX_SIZE];
ll pre[MAX_SIZE];
int N;

int main() {
    int i, j;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        int v;
        scanf("%d", &v);
        cnt[v]++;
    }

    for (i = 1; i <= 3000000; ++i) {
        for (j = 1; j * i <= 3000000; ++j) {
            if (i > j) continue;
            if (j == i) {
                prcnt[j * i] += 1ll * cnt[j] * (cnt[j] - 1) / 2;
            } else {
                prcnt[j * i] += 1ll * cnt[i] * cnt[j];
            }
        } 
    }

    for (i = 1; i <= 3000000; ++i) {
        pre[i] = pre[i-1] + prcnt[i];
    }   

    int Q;
    ll tol = 1ll * N * (N - 1) / 2;
    scanf("%d", &Q);
    while (Q-- > 0) {
        int v;
        scanf("%d", &v);
        printf("%I64d\n", (tol - pre[v-1]) * 2);
    } 
    return 0;
}