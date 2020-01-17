#include <bits/stdc++.h>
#define MAX_SIZE 2097312
typedef long long ll;

using namespace std;

struct segt {
    ll lz, value;
};

segt tree[MAX_SIZE];
int L[MAX_SIZE >> 1], R[MAX_SIZE >> 1];
int a[MAX_SIZE >> 1];
int k[MAX_SIZE >> 1];
int n;

// for L[i] fill it with the index of the nearest left number
// that is less than a[i]
// for R[i] fill it with the index of the nearest right number
// that is no greater than a[i]
void fillL() {
    stack<int> s;
    int i;
    for (i = 1; i <= n; i++) {
        if (s.empty()) {
            L[i] = 0;
        } else {
            while (!s.empty() && a[s.top()] >= a[i]) {
                s.pop();
            }
            
            if (!s.empty()) {
                L[i] = s.top();
            } else {
                L[i] = 0;
            }
        }
        
        s.push(i);
    }
}

void fillR() {
    stack<int> s;
    int i;
    for (i = n; i >= 1; i--) {
        if (s.empty()) {
            R[i] = n + 1;
        } else {
            while (!s.empty() && a[s.top()] > a[i]) {
                s.pop();
            }
            
            if (!s.empty()) {
                R[i] = s.top();
            } else {
                R[i] = n + 1;
            }
        }
        
        s.push(i);
    }
}

void pushdown(int l, int r, int index) {
    if (l >= r) return;
    if (tree[index].lz || tree[index].value) {
        int mid = l + (r - l) / 2;
        int len = mid - l + 1;
        tree[index * 2].lz += tree[index].lz;
        tree[index * 2 + 1].lz += tree[index].lz;
        tree[index * 2].value += tree[index].value;
        tree[index * 2 + 1].value += tree[index].value + tree[index].lz  * len;
        tree[index].lz = 0;
        tree[index].value = 0;
    }
}

void update(int start, int end, int l, int r, int index, ll val) {
    if (start > end || l > r) return;
    int mid = l + (r - l) / 2;
    pushdown(l, r, index);
    if (start > r || l > end) return;
    if (start <= l && r <= end) {
        tree[index].value += val * (l - start + 1); 
        tree[index].lz += val;
        return;
    }
    
    if (end <= mid) {
        update(start, end, l, mid, index * 2, val);
    } else if (start >= mid + 1) {
        update(start, end, mid + 1, r, index * 2 + 1, val);
    } else {
        update(start, end, l, mid, index * 2, val);
        update(start, end, mid + 1, r, index * 2 + 1, val);
    }
}

ll query(int pos, int l, int r, int index) {
    if (l > r || pos < l || pos > r) return 0;
    pushdown(l, r, index);
    int mid = l + (r - l) / 2;
    if (l == r && r == pos) return tree[index].value;
    if (pos <= mid) return query(pos, l, mid, index * 2);
    return query(pos, mid + 1, r, index * 2 + 1);
}

int main() {
    int i, m;
    scanf("%d", &n);
    for (i = 1 ; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    scanf("%d", &m);
    for (i = 0 ; i < m; i++) {
        scanf("%d", &k[i]);
    }
    
    fillL();
    fillR();
    for (i = 1; i <= n; i++) {
        int l1 = i - L[i] - 1;
        int l2 = R[i] - i - 1;
        update(1, l1 + 1 + l2, 1, n, 1, a[i]);
        update(l1 + 2, l1 + l2 + 1, 1, n, 1, -a[i]);
        update(l2 + 2, l1 + l2 + 1, 1, n, 1, -a[i]);
    }
    
    for (i = 0; i < m; i++) {
        ll v = query(k[i], 1, n, 1);
        double ans = (v * 1.0) / (1.0 * (n - k[i] + 1));
        printf("%.12lf\n", ans);
    }
    return 0;
}
