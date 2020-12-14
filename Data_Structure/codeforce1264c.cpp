#include <bits/stdc++.h>
#define MAX_SIZE 200111
typedef long long ll;
using namespace std;

const ll mod = 998244353;

ll den[MAX_SIZE], num[MAX_SIZE], p[MAX_SIZE], ans = 0;
set<int> st;
int N, Q;

ll inv(ll v) {
    v %= mod;
    ll p = mod - 2, ret = 1;
    while (p > 0) {
        if (p % 2 == 1) {
            ret = ret * v;
            ret %= mod;
            p--;
        } else {
            v = v * v;
            v %= mod;
            p /= 2;
        }
    }
    return ret;
}

ll query(int l, int r) {
    if (l > r) return 0;
    // calculate numerator = 1 + p[l] + p[l]p[l+1] + p[l]p[l+1]p[l+2] + ... + p[l]p[l+1]p[l+2]...p[r-1]
    // denominator = p[l]p[l+1]...p[r]
    ll d = den[r] * inv(den[l-1]) % mod;
    ll n = ((num[r-1] - num[l-1]) * inv(den[l-1])) % mod;
    n = n + 1;
    return (n * inv(d)) % mod;
}

void insert(int v) {
    auto iter = st.lower_bound(v);
    int r = *iter, l = *prev(iter);
    ans = ans - query(l, r - 1);
    ans += query(l, v - 1);
    ans += query(v, r - 1);
    ans %= mod;
    st.insert(v);
}

void del(int v) {
    auto iter = st.find(v);
    int l = *prev(iter), r = *next(iter);
    ans = ans - query(l, v - 1);
    ans = ans - query(v, r - 1);
    ans = ans + query(l, r - 1);
    ans %= mod;
    st.erase(v);
}

int main() {
    ll i_100 = inv(100);
    int i;
    st.insert(1);
    scanf("%d%d", &N, &Q);
    st.insert(N + 1);
    den[0] = 1;
    num[0] = 1;
    for (i = 1; i <= N; ++i) {
        scanf("%I64d", &p[i]);
        den[i] = den[i-1] * p[i];
        den[i] %= mod;
        den[i] = den[i] * i_100;
        den[i] %= mod;
        num[i] = num[i-1] + den[i];
        num[i] %= mod;
    }
    ans = query(1, N);
    while (Q-- > 0) {
        int u;
        scanf("%d", &u);
        if (!st.count(u)) {
            insert(u);
        } else {
            del(u);
        }

        printf("%I64d\n", (ans % mod + mod) % mod);
    }
    return 0;
}