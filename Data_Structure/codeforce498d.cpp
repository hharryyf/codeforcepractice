#include <bits/stdc++.h>
#define MAX_SIZE 262192
using namespace std;

struct segt {
   int value[60];
};

segt ept;
segt tree[MAX_SIZE];
int a[MAX_SIZE];

segt pullup(segt t1, segt t2) {
    segt t;
    int i;
    for (i = 0 ; i < 60; i++) {
        t.value[i] = t1.value[i] + t2.value[(i + t1.value[i]) % 60];
    }
    return t;
}

void build(int l, int r, int index) {
    int i, mid = l + (r - l) / 2;
    if (l > r) return;
    if (l == r) {
        for (i = 0; i < 60; i++) {
            if (i % a[l] == 0) {
                tree[index].value[i] = 2;
            } else {
                tree[index].value[i] = 1;
            }
        }
        return;
    }
    
    build(l, mid, index * 2);
    build(mid + 1, r, index * 2 + 1);
    tree[index] = pullup(tree[index * 2], tree[index * 2 + 1]);
}

void update(int pos, int l, int r, int index, int val) {
    if (pos < l || l > r || r < pos) return;
    int mid = l + (r - l) / 2;
    int i;
    if (l == r && pos == l) {
        for (i = 0; i < 60; i++) {
            if (i % val == 0) {
                tree[index].value[i] = 2;
            } else {
                tree[index].value[i] = 1;
            }
        }
        return;
    }
    
    if (pos <= mid) {
        update(pos, l, mid, index * 2, val);
    } else {
        update(pos, mid + 1, r, index * 2 + 1, val);
    }
    
    tree[index] = pullup(tree[index * 2], tree[index * 2 + 1]);
}

segt query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return ept;
    if (start <= l && r <= end) {
        return tree[index];
    }
    
    int mid = l + (r - l) / 2;
    if (end <= mid) return query(start, end, l, mid, index * 2);
    if (start >= mid + 1) return query(start, end, mid + 1, r, index * 2 + 1);
    return pullup(query(start, end, l, mid, index * 2), 
                  query(start, end, mid + 1, r, index * 2 + 1));
}

char st[4];

int main() {
    int n;
    scanf("%d", &n);
    int i;
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    build(1, n, 1);
    
    int q;
    scanf("%d", &q);
    while (q > 0) {
        int v1, v2;
        scanf("%s%d%d", st, &v1, &v2);
        if (st[0] == 'C') {
            update(v1, 1, n, 1, v2);
        } else {
            printf("%d\n", query(v1, v2 - 1, 1, n, 1).value[0]);
        }
        q--;
    }
    return 0;
}
