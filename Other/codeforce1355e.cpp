#include <bits/stdc++.h>
#define MAX_SIZE 100111
using namespace std;
typedef long long ll;
int h[MAX_SIZE];
int N, A, R, M;

ll f(int x) {
    ll up = 0, down = 0;
    int i;
    for (i = 1; i <= N; ++i) {
        if (h[i] > x) {
            down += h[i] - x;
        } else {
            up += x - h[i];
        }
    }

    if (M <= A + R) {
        if (up >= down) {
            return down * M + (up - down) * A;
        } 
        return up * M + (down - up) * R;
    }

    return up * A + down * R;
}

int main() {
    int i;
    scanf("%d%d%d%d", &N, &A, &R, &M);
    for (i = 1; i <= N; ++i) scanf("%d", &h[i]);
    int low = 0, high = 1e9;
    for (i = 0 ; i < 70; ++i) {
        int l = low + (high - low) / 3;
        int r = high - (high - low) / 3;
        if (l > r) continue;
        if (f(l) <= f(r)) {
            high = r;
        } else {
            low = l;
        }
    }

    ll ans = f(low);
    for (i = low + 1; i <= high; ++i) {
        ans = min(ans, f(i));
    }

    printf("%I64d\n", ans);
    return 0;
}