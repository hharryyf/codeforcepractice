#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
typedef long long ll;
#define MAX_SIZE 524292
using namespace __gnu_pbds ;
using namespace std ;
typedef tree <int , null_type , less <int>, rb_tree_tag ,
tree_order_statistics_node_update> ordered_set ;
// we use an ordered statistic tree here to save the active positions
ordered_set st;
int a[MAX_SIZE];
int p[MAX_SIZE];
int n;

struct rangetree {
    struct segt {
        ll lz, rsum;
    };

    segt t[MAX_SIZE];

    void pushdown(int l, int r, int index) {
        if (l > r) return;
        if (t[index].lz != 0) {
            if (l != r) {
                t[LEFT].rsum += t[index].lz * (MID - l + 1);
                t[RIGHT].rsum += t[index].lz * (r - MID);
                t[LEFT].lz += t[index].lz;
                t[RIGHT].lz += t[index].lz;
            }
            t[index].lz = 0;
        }
    }

    ll query(int start, int end, int l, int r, int index) {
        if (start > end || l > r || start > r || l > end) return 0;
        pushdown(l, r, index);
        if (start <= l && r <= end) return t[index].rsum;
        if (end <= MID) return query(start, end, l, MID, LEFT);
        if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
        return query(start, end, l, MID, LEFT) + query(start, end, MID + 1, r, RIGHT);
    }

    void update(int start, int end, int l, int r, int index, int val) {
        if (start > end || l > r || start > r || l > end) return;
        pushdown(l, r, index);
        if (start <= l && r <= end) {
            t[index].rsum += 1ll * (r - l + 1) * val;
            t[index].lz += val;
            return;
        }

        if (end <= MID) {
            update(start, end, l, MID, LEFT, val);
        } else if (start >= MID + 1) {
            update(start, end, MID + 1, r, RIGHT, val);
        } else {
            update(start, end, l, MID, LEFT, val);
            update(start, end, MID + 1, r, RIGHT, val);
        }

        t[index].rsum = t[LEFT].rsum + t[RIGHT].rsum;
    }


};

rangetree t1, t2;
ll ivp = 0;

int main() {
    int i;
    int L, R = 0;
    scanf("%d", &n);
    L = n + 1;
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        p[a[i]] = i;
    }

    for (i = 1; i <= n; ++i) {
        L = min(L, p[i]);
        R = max(R, p[i]);
        st.insert(p[i]);
        ivp = ivp + (int) st.size() - (int) st.order_of_key(p[i]) - 1;
        t1.update(p[i] + 1, n, 1, n, 1, 1);
        t2.update(1, p[i] - 1, 1, n, 1, 1);
        int mid = (int) st.size() / 2;
        int pivot = *st.find_by_order(mid); 
        int left = mid + 1, right = (int) st.size() - mid - 1;
        // cout << "pivot= " << pivot << endl;
        ll ans = t2.query(pivot + 1, R, 1, n, 1) + t1.query(L, pivot, 1, n, 1) - 1ll * left * (left - 1) / 2
                 - 1ll * right * (right - 1) / 2 + ivp;
        printf("%I64d ", ans);
    }
    return 0;
}