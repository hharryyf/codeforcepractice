#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void solve(int N, int K) {
    int i, j, k;
    ll ret = -1;
    for (i = 0 ; i <= 9; ++i) {
        ll sm = 0;
        if (i + K > 9) {
            int c1 = 0, c2 = 0;
            for (j = 0 ; j <= K; ++j) {
                sm += (i + j) % 10;
                if (i + j <= 9) {
                    c1++;
                } else {
                    c2++;
                }
            }

            if (sm > N) continue;
            for (j = 0 ; j <= 17; ++j) {
                if (sm + 9 * c1 * j > N) continue;
                for (k = 0 ; k <= 8; ++k) {
                    ll curr = sm + 9 * c1 * j + c1 * k + c2 * (k + 1);
                    if (curr > N) continue;
                    if ((N - curr) % (K + 1) != 0) continue;
                    int rem = (N - curr) / (K + 1);
                    int fr = rem % 9, t9 = rem / 9;
                    ll num = fr;
                    while (t9-- > 0) {
                        num = num * 10;
                        num += 9;
                    }

                    num = num * 10;
                    num += k;
                    t9 = j;
                    while (t9-- > 0) {
                        num = num * 10;
                        num += 9;
                    }

                    num = num * 10;
                    num += i;
                    if (num < ret || ret == -1) ret = num;
                }
            }
        } else {
            for (j = 0 ; j <= K; ++j) {
                sm += (i + j);
            }

            if (sm > N || (N - sm) % (K + 1) != 0) continue;
            int rem = (N - sm) / (K + 1);
            int fr = rem % 9, t9 = rem / 9;
            ll num = fr;
            while (t9-- > 0) {
                num = num * 10;
                num += 9;
            }
            num = num * 10;
            num += i;
            if (ret == -1 || ret > num) ret = num;
        }
    }

    printf("%I64d\n", ret);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int n, k;
        scanf("%d%d", &n, &k);
        solve(n, k);
    }
    return 0;
}