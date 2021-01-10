#include <bits/stdc++.h>
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;

int Xmax[MAX_SIZE], Xmin[MAX_SIZE];
int del[MAX_SIZE], add[MAX_SIZE];
int upcnt = 0, downcnt = 0;
ll uptol = 0, downtol = 0;
ll tol = 0;

int main() {
    int i, N, X, Y;
    ll ans = 0, curr = 0;
    scanf("%d%d", &X, &Y);
    for (i = 0; i < MAX_SIZE; ++i) Xmin[i] = MAX_SIZE, Xmax[i] = -1;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        Xmax[x] = max(Xmax[x], y);
        Xmin[x] = min(Xmin[x], y);
    }

    for (i = 0; i < X; ++i) {
        if (Xmax[i] >= Xmin[i]) {
            tol += (Xmax[i] - Xmin[i]) * 2;
            uptol += Xmin[i] * 2;
            upcnt++;
            del[Xmin[i]]++, add[Xmax[i]]++;
        }
    }

    ans = curr = tol + uptol;
    for (i = 0; i <= Y; ++i) {
        ans = min(ans, curr);
        upcnt -= del[i];
        uptol -= upcnt * 2;
        downcnt += add[i];
        downtol += downcnt * 2;
        curr = downtol + uptol + tol;
    }

    printf("%I64d\n", ans + X - 1);
    return 0;
}