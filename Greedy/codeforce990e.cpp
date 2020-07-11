#include <bits/stdc++.h>
#define MAX_SIZE 1000011
using namespace std;
typedef long long ll;

int k, n, m;
int pos[MAX_SIZE];
int bad[MAX_SIZE];
int good[MAX_SIZE];
ll a[MAX_SIZE];
ll ans = 1e18;
#define WRONGANSWER

int main() {
    int i, j;
    int mx = 0;
    scanf("%d%d%d", &n, &m, &k);
    for (i = 0 ; i < m; ++i) {
        scanf("%d", &pos[i]);
        bad[pos[i]] = 1;
    }

    for (i = 1; i <= k; ++i) scanf("%I64d", &a[i]);
    // for (i = 1 ; i <= k; ++i) a[i] = i;

    if (bad[0]) {
        printf("-1\n");
        return 0;
    }

    good[0] = 0;
    for (i = 1; i < n; ++i) {
        if (bad[i]) {
            good[i] = good[i-1];
        } else {
            good[i] = i;
        }
        mx = max(i - good[i] + 1, mx);
    }  
    #ifndef WRONGANSWER
    for (i = 0 ; i < n; ++i) cout << good[i] << " ";
    cout << endl;
    #endif
    if (mx > k) {
        printf("-1\n");
        return 0;
    }

    for (i = k; i >= max(mx, 1); --i) {
        j = 0;
        int cnt = 0;
        while (j < n) {
            cnt++;
            j += i;
            if (j >= n) break;
            if (bad[j] == 1) {
                cnt++;
                j = good[j] + i;
            }
        }

        ans = min(ans, a[i] * cnt);
    }

    cout << ans << endl;
    return 0;
}