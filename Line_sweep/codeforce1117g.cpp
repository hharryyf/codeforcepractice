#pragma GCC optimize(3)
#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 2097312
using namespace std;

struct qrs {
    int l, r;
    int id;
};

class rangetree {
public:
    rangetree() {
        int i;
        for (i = 0 ; i < MAX_SIZE; i++) {
            tree[i].value = tree[i].lz = 0;
        }
    }
    
    void pushdown(int l, int r, int index) {
        if (l > r) return;
        if (tree[index].lz) {
            if (l != r) {
                int mid = l + (r - l) / 2;
                int len1 = mid - l + 1, len2 = r - mid;
                tree[index * 2].lz += tree[index].lz;
                tree[index * 2 + 1].lz += tree[index].lz;
                tree[index * 2].value += tree[index].lz * len1;
                tree[index * 2 + 1].value += tree[index].lz * len2;
            }
            tree[index].lz = 0;
        }
    }
    
    ll query(int start, int end, int l, int r, int index) {
        if (start > end || l > r) return 0ll;
        pushdown(l, r, index);
        if (start <= l && r <= end) return tree[index].value;
        int mid = l + (r - l) / 2;
        if (end <= mid) return query(start, end, l, mid, index * 2);
        if (start >= mid + 1) return query(start, end, mid + 1, r, index * 2 + 1);
        return query(start, end, l, mid, index * 2) + query(start, end, mid + 1, r, index * 2 + 1);
    }
    
    void update(int start, int end, int l, int r, int index, int val) {
        if (start > end || l > r) return;
        pushdown(l, r, index);
        if (start <= l && r <= end) {
            tree[index].lz += 1ll * val;
            tree[index].value += 1ll * (r - l + 1) * val;
            return;
        }
        
        int mid = l + (r - l) / 2;
        if (end <= mid) {
            update(start, end, l, mid, index * 2, val);
        } else if (start >= mid + 1) {
            update(start, end, mid + 1, r, index * 2 + 1, val);
        } else {
            update(start, end, l, mid, index * 2, val);
            update(start, end, mid + 1, r, index * 2 + 1, val);
        }
        tree[index].value = tree[index * 2].value + tree[index * 2 + 1].value;
    }
    
    struct segt {
        ll value, lz;
    };

    segt tree[MAX_SIZE];
};

int a[MAX_SIZE >> 1];
ll ans[MAX_SIZE >> 1];
// ql[i] refers to the leftmost index j such that num[i] is no less than
int ql[MAX_SIZE];
// qr[i] referse to the rightmost index j such that num[i] is no less than
int qr[MAX_SIZE];
qrs q[MAX_SIZE << 1];
rangetree t1, t2;
int n, m;

void preprocess() {
    stack<int> s1;
    int i;
    for (i = 1; i <= n; i++) {
        if (s1.empty()) {
            ql[i] = 1;
        } else {
            while (!s1.empty() && a[s1.top()] < a[i]) {
                s1.pop();
            }
            if (s1.empty()) {
                ql[i] = 1;
            } else {
                ql[i] = s1.top() + 1;
            }
        }
        s1.push(i);
    }
    
    while (!s1.empty()) s1.pop();
    
    for (i = n; i >= 1; i--) {
        if (s1.empty()) {
            qr[i] = n;
        } else {
            while (!s1.empty() && a[s1.top()] < a[i]) {
                s1.pop();
            }
            if (s1.empty()) {
                qr[i] = n;
            } else {
                qr[i] = s1.top() - 1;
            }
        }
        s1.push(i);
    }
}

static bool cmp_1(const qrs &q1, const qrs &q2) {
    return q1.r < q2.r;
}

static bool cmp_2(const qrs &q1, const qrs &q2) {
    return q1.l < q2.l;
}

void solve_1() {
    int i, j;
    sort(q, q + m, cmp_1);
    for (i = 0, j = 1 ; i < m; i++) {
        while (j <= n && q[i].r >= j) {
            t1.update(ql[j], j, 1, n, 1, 1);
            j++;
        }
        
        ans[q[i].id] += t1.query(q[i].l, q[i].r, 1, n, 1);
    }
}

void solve_2() {
    int i, j;
    sort(q, q + m, cmp_2);
    for (i = m - 1, j = n; i >= 0; i--) {
        while (j >= 1 && q[i].l <= j) {
            t2.update(j, qr[j], 1, n, 1, 1);
            j--;
        }
        
        ans[q[i].id] += t2.query(q[i].l, q[i].r, 1, n, 1);
    }
}

int main() {
    int i;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    for(i = 0; i < m; i++) {
        scanf("%d", &q[i].l);
        q[i].id = i;
    }
    
    for (i = 0 ; i < m; i++) {
        scanf("%d", &q[i].r);
        ans[i] = -(q[i].r - q[i].l + 1);
        
    }
    preprocess();
    
    solve_1();
    
    solve_2();
    
    for (i = 0 ; i < m; i++) {
        printf("%lld ", ans[i]);
    }
    printf("\n");
    return 0;
}
