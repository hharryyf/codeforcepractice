#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int up = 62;

ll shift[up + 1];

int getlevel(ll x) {
    int i;
    for (i = up; i >= 0; --i) {
        if (x & (1ll << i)) return i;
    }
    return 0;
}

int main() {
    int Q, i;
    scanf("%d", &Q);
    while (Q-- > 0) {
        int tp;
        ll x, k;
        scanf("%d", &tp);
        if (tp == 1) {
            scanf("%I64d%I64d", &x, &k);
            k *= -1;
            int level = getlevel(x);
            shift[level] = (shift[level] + k) % (1ll << level);
            if (shift[level] < 0) shift[level] += (1ll << level);
        } else if (tp == 2) {
            scanf("%I64d%I64d", &x, &k);
            k *= -1;
            int level = getlevel(x);
            k = k % (1ll << level);
            for (i = level; i <= up; ++i) {
                shift[i] = (shift[i] + k) % (1ll << i);
                if (shift[i] < 0) shift[i] += (1ll << i);
                k = k * 2;
            }
        } else {
            scanf("%I64d", &x);
            int level = getlevel(x);
            ll pos = (x - shift[level]) % (1ll << level);
            // pos += shift[level];
            if (pos < 0) {
                pos += (1ll << level);
            }

            // cout << "pos= " << pos << " level= " << shift[level] << endl;
            while (level >= 0) {
                x = (1ll << level) + (pos + shift[level]) % (1ll << level);
                printf("%I64d ", x);
                pos = pos / 2;
                level--;
            }
            printf("\n");
        }
    }
    return 0;
}