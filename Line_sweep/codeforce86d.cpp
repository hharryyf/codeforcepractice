#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 262192
using namespace std;

int cnt[MAX_SIZE << 2], a[MAX_SIZE << 2];
ll ans[MAX_SIZE], sm = 0;
int l = 1, r = 0;
int block_size = 1;

struct qrs {
    int l, r, id;
    bool operator < (qrs other) const {
        int b1 = l / block_size, b2 = other.l / block_size;
        return (b1 ^ b2) ? b1 < b2 : ((b1 & 1) ? r < other.r : r > other.r);
    }
};

qrs q[MAX_SIZE];

inline void add(int idx) {
    // we want to add in a[idx]
    // current sum should increase by (cnt[a[idx]] + 1) ^2 - cnt[a[idx]] ^ 2
    // which is 2 * cnt[a[idx]] + 1 and cnt[a[idx]]++
    sm += 1ll * a[idx] * ((2ll * cnt[a[idx]]) + 1);
    cnt[a[idx]]++;
}

inline void del(int idx) {
    sm -= 1ll * a[idx] * ((2ll * cnt[a[idx]]) - 1);
    cnt[a[idx]]--;
}

int main() {
    int n, m, i;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    for (i = 0; i < m; i++) {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
    }
    block_size = sqrt(n);
    sort(q, q + m);
    
    for (i = 0 ; i < m; i++) {
        while (r < q[i].r) add(++r);
        while (r > q[i].r) del(r--);
        while (l > q[i].l) add(--l);
        while (l < q[i].l) del(l++);
        
        ans[q[i].id] = sm;
    }
    
    for (i = 0 ; i < m; i++) {
        printf("%lld\n", ans[i]);
    }
    return 0;
}
