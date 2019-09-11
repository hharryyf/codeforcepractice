#include <bits/stdc++.h>
#define MAX_SIZE (262144 + 22)

typedef long long ll;

using namespace std;

/*
    we can observe that the 2d-array looks like
    a[1]       a[2]     a[3]     a[4] a[5]
    a[1,2]     a[2,3]   a[3,4]   a[4,5]
    a[1,2,3]   a[2,3,4] a[3,4,5]
    a[1,2,3,4] a[2,3,4,5]
    a[1,2,3,4,5]
    
    for each colunm i its total value is equal to the length of the consecutive '1',
    starts at i
    
    in other words it could be described as half the summation of all the consecutive '1'
    block's square sum
    
*/

typedef struct segt {
    // length of the segment
    // length of the consecutive prefix, consecutive suffix and current
    // interval's ans
    ll len, prefix, suffix, ans;
} segmenttree;

// the 17 segment trees
segmenttree tree[18][MAX_SIZE];

ll arr[18][MAX_SIZE >> 1];

int n, m;

void splitnum(int index, ll num);
// build the segment tree
void build(int l, int r, int index);
// merge node function
segmenttree merge_interval(segmenttree t1, segmenttree t2);
// update function
void update(int pt, int l, int r, int index, ll val);
ll query();

int main() {
    int i;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        ll v;
        scanf("%lld", &v);
        splitnum(i, v);
    }
    
    
    build(1, n, 1);
    for (i = 1; i <= m; i++) {
        int p;
        ll v;
        scanf("%d%lld", &p, &v);
        update(p, 1, n, 1, v);
        printf("%lld\n", query());    
    }
    return 0;
}

ll query() {
    ll ans = 0;
    for (int i = 0 ; i < 17; i++) {
        ans += (1 << i) * tree[i][1].ans;
    }
    return ans;
}

void update(int pt, int l, int r, int index, ll val) {
    if (l > r) return;
    if (l == r && pt == r) {
        splitnum(pt, val);
        
        for (int i = 0 ; i < 17; i++) {
            tree[i][index].len = 1;
            tree[i][index].prefix = tree[i][index].suffix = tree[i][index].ans = arr[i][l];
        }
        
        return;
    }
    
    int mid = l + (r - l) / 2;
    if (pt <= mid) {
        update(pt, l, mid, index * 2, val);
    } else {
        update(pt, mid + 1, r, index * 2 + 1, val);
    }
    
    for (int i = 0 ; i < 17; i++) {
        tree[i][index] = merge_interval(tree[i][index * 2], tree[i][index * 2 + 1]);
    }
}

void splitnum(int index, ll num) {
    int i = 0;
    
    for (i = 0 ; i < 17; i++) {
        arr[i][index] = 0;
    }
    
    i = 0;
    while (num > 0) {
        
        arr[i++][index] = num % 2;
        num /= 2;
    }
   
}

segmenttree merge_interval(segmenttree t1, segmenttree t2) {
    segmenttree t;
    t.len = t1.len + t2.len;
    ll central = t1.suffix + t2.prefix;
    t.ans = t1.ans + t2.ans - (t1.suffix * (t1.suffix + 1)) / 2 
    - (t2.prefix * (t2.prefix + 1)) / 2 + (central * (central + 1)) / 2;
    if (t2.suffix == t2.len) {
        t.suffix = t2.suffix + t1.suffix;
    } else {
        t.suffix = t2.suffix;
    }
    
    if (t1.prefix == t1.len) {
        t.prefix = t1.prefix + t2.prefix;
    } else {
        t.prefix = t1.prefix;
    }
    return t;
}

void build(int l, int r, int index) {
    int i;
    if (l > r) return;
    if (l == r) {
        for (i = 0 ; i < 17; i++) {
            tree[i][index].len = 1;
            tree[i][index].prefix = tree[i][index].suffix = tree[i][index].ans = arr[i][l]; 
        }
        return;
    }
    
    int mid = l + (r - l) / 2;
    build(l, mid, index * 2);
    build(mid + 1, r, index * 2 + 1);

    for (i = 0 ; i < 17; i++) {
        tree[i][index] = merge_interval(tree[i][index * 2], tree[i][index * 2 + 1]);
    }
}
