#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int i, n;
        ll l, r;
        bool flag = false;
        cin >> n >> l >> r;
        if (l == 1ll * (n - 1) * n + 1) {
            printf("1\n");
            continue;
        }

        if (r == 1ll * (n-1) * n + 1) {
            r--;
            flag = true;
        }
        vector<ll> cnt;
        cnt.push_back(1ll * 2 * (n - 1));
        for (i = n - 2; i > 0; --i) {
            cnt.push_back(cnt.back() + 1ll * 2 * i);
        }

        int index = lower_bound(cnt.begin(), cnt.end(), l) - cnt.begin();
        int chunk = index + 1;
        ll curr = index == 0 ? 1 : cnt[index - 1] + 1;
        int st = chunk + 1;
        while (curr <= r) {
            if (curr % 2 == 1) {
                if (curr >= l) {
                    printf("%d ", chunk);
                }
            } else {
                if (curr >= l) {    
                    printf("%d ", st);
                }
                
                st++;
                if (st == n + 1) {
                    chunk++;
                    st = chunk + 1;
                    
                }
            }
            curr++;
        }

        if (flag) {
            printf("1\n");
        } else {
            printf("\n");
        }
    }
    return 0;
}