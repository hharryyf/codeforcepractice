#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_N 2097312
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;
/*
    when we maintain the prefix sum type [l, r] query, sum(l, r) = prefix[r] - prefix[l-1]
    hence be really careful on the order of updating f[prefix[x]] and cnt!!!!!!!!!
*/
int block = 1;

struct qrs {
    int l, r, id;
    bool operator < (qrs other) const {
        return make_pair(l / block, r) <
               make_pair(other.l / block, other.r);
    }
};

int k;
qrs q[MAX_SIZE];
ll f[MAX_N];
ll cnt = 0;
ll ans[MAX_SIZE];
int num[MAX_SIZE];
int prefix[MAX_SIZE];
int l = 1, r = 0;
// the order is very important!
void add(int idx) {
    cnt += f[prefix[idx] ^ k];
    f[prefix[idx]]++;
}
// the order is very important!
void del(int idx) {
    f[prefix[idx]]--;
    cnt -= f[prefix[idx] ^ k];
}

int main() {
    int i, n, m;
    scanf("%d%d%d", &n, &m, &k);
    block = sqrt(n);
    for (i = 1 ; i <= n; i++) {
        int c;
        scanf("%d", &c);
        prefix[i] = prefix[i-1] ^ c;
    }
    for (i = 0 ; i < m; i++) {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
    }
    
    sort(q, q + m);
    
    f[0] = 1;
    for (i = 0 ; i < m; i++) {
        while (r < q[i].r) {
            add(++r);
        }
        
        while (r > q[i].r) {
            del(r--);
        }
        
        while (l > q[i].l) {
            l--;
            add(l-1);
        }
        
        while (l < q[i].l) {
            del(l-1);
            l++;
        }
        
        ans[q[i].id] = cnt;
    }
    
    for (i = 0 ; i < m; i++) {
        printf("%lld\n", ans[i]);
    }
    return 0;
}
