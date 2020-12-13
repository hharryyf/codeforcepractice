#include <bits/stdc++.h>

using namespace std;

map<int, int> mp;
int n, p, k;

long long mul(int u, int v) {
    return (1ll * u * v) % p;
}

int main() {
    int i;
    scanf("%d%d%d", &n, &p, &k);
    for (i = 0 ; i < n; ++i) {
        int v;
        scanf("%d", &v);
        long long rem = mul(mul(mul(v, v), v), v) - mul(k, v);
        v = rem % p;
        if (v < 0) v += p;
        mp[v]++;
    }

    long long ans = 0;
    for (auto iter : mp) {
        ans += 1ll * iter.second * (iter.second - 1) / 2;
    }

    printf("%I64d\n", ans);
    return 0;
}