#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 4000011
using namespace std;
const ll mod = 1e9 + 7;

int a[MAX_SIZE];
char st[MAX_SIZE];
int L;
int N;


void solve() {
    int i, j, k;
    ll ans = L;
    // cout << "solve" << endl;
    for (i = 1; i <= N; ++i) {
        // paste s[i+1] to s[] for j times
        // cout << ans << endl;
        // cout << "paste " << a[i] << "times " << endl;
        if (L > N) {
            ans = ans + 1ll * (ans - i) * (a[i] - 1);
            ans = ans % mod;
            ans += mod;
            ans %= mod;
            continue;
        }  

        for (j = 1; j <= a[i]-1; ++j) {
            // cout << i + 1 << " to " << L << endl;
            for (k = i + 1; k <= L; ++k) {
                a[++ans] = a[k];
            }
        }

        L = ans;
    }

    cout << ans << endl;
}

int main() {
    int T, i;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        scanf("%s", st);
        L = strlen(st);
        for (i = 1; i <= L; ++i) {
            a[i] = st[i-1] - '0';
        }

        solve();
    }
    return 0;
}