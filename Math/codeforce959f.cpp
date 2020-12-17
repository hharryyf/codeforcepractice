#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 20;
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
        if (x == 0) return true;
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
int n, Q;
int a[(1 << N) + 11];
ll ans[(1 << N)];
pair<pair<int, int>, int> q[(1 << N)];
const ll mod = 1e9 + 7;

int main() {
    int i, j;
    scanf("%d%d", &n, &Q);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }

    for (i = 1; i <= Q; ++i) {
        scanf("%d%d", &q[i].first.first, &q[i].first.second);
        q[i].second = i;
    }

    ll curr = 1;
    sort(q + 1, q + 1 + Q);
    for (i = 1, j = 1; i <= n; ++i) {
        if (z2.check(a[i])) {
            curr = curr * 2;
            curr %= mod;
        } else {
            z2.insert(a[i]);
        }

        while (j <= Q && q[j].first.first == i) {
            if (z2.check(q[j].first.second)) {
                ans[q[j].second] = curr;
            } else {
                ans[q[j].second] = 0;
            }
            ++j;
        }
    }

    for (i = 1; i <= Q; ++i) {
        printf("%I64d\n", ans[i]);
    }
    return 0;
}