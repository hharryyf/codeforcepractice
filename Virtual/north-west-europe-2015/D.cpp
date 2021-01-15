#include <bits/stdc++.h>
#define MAX_SIZE 1000111
typedef long long ll;
using namespace std;

const ll inf = 1e17;
int N, R, P;
ll dp[MAX_SIZE];

ll f(int x) {
    if (x <= 1) return 0;
    //cout << x << endl;
    if (x > 1 && dp[x] != -1) return dp[x];
    int i;
    ll ret = 1ll * (x - 1) * P + R;
    for (i = 2; i <= x; ++i) {
        if (x % i == 0) {
            ret = min(ret, f(x / i) + 1ll * P * (i - 1) + R);
        } else {
            ret = min(ret, f(x / i + 1) + 1ll * P * (i - 1) + R);
        }
    }

    //cout << "x= " << x << " get " << ret << endl;
    return dp[x] = ret;
}

int main() {
    int i;
    scanf("%d%d%d", &N, &R, &P);
    for (i = 1; i < MAX_SIZE; ++i) dp[i] = -1;
    printf("%I64d\n", f(N));
    return 0;
}