#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 31;
struct z2_basis {    
    ll a[N];
    bool flag = false; // if the set is linearly dependent
    void insert(ll x) {
        int i;
        for(i = N - 1; i >= 0; i--) {
            if(x & (1ll << i)) {
                if(!a[i]) {
                    a[i] = x;
                    return;
                } else {
                    x ^=a[i];
                }
            }
        }

        flag = true;
    }
    
    bool check(ll x) {
        int i;
        for(i = N - 1; i >= 0; i--) {
            if (x & (1ll<<i)) {
                if(!a[i]) {
                    return false;
                } else {
                    x^=a[i];
                }
            }
        }

        return true;
    }

    ll qmax(ll res=0) {
        int i;
        for(i = N - 1; i >= 0; i--) {
            res = max(res, res ^ a[i]);
        }
        return res;
    }

    
    ll qmin() {
        int i;
        if(flag) {
            return 0;
        }

        for(i = 0; i <= N - 1; i++) {
            if(a[i]) return a[i];
        }
    }
    // return the dimension of the set
    int dim() {
        int i, cnt = 0;
        for (i = N - 1; i >= 0; --i) {
            if (a[i]) ++cnt;
        }   

        return cnt;
    }
};

z2_basis z2;

int main() {
    int n, i, pre = 0;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        int v;
        scanf("%d", &v);
        pre ^= v;
        z2.insert(pre);
    }
    if (pre == 0) {
        printf("-1\n");
        return 0;
    }
    printf("%d\n", z2.dim());
    return 0;
}