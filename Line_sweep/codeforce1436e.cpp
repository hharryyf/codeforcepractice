#include <bits/stdc++.h>
#define MAX_SIZE 262192
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;
int tree[MAX_SIZE];
int a[MAX_SIZE], pre[MAX_SIZE], ok[MAX_SIZE];
int n;

void check() {
    int i, all_1 = 1;
    for (i = 1; i <= n; ++i) {
        if (a[i] != 1) all_1 = 0;
    }

    if (all_1) {
        printf("1\n");
        exit(0);
    }
}

void update(int pt, int l, int r, int index, int val) {
    if (l > r || pt < l || pt > r) return;
    if (l == r) {
        tree[index] = max(tree[index], val);
        return;
    }

    if (pt <= MID) {
        update(pt, l, MID, LEFT, val);
    } else {
        update(pt, MID + 1, r, RIGHT, val);
    }
    tree[index] = min(tree[LEFT], tree[RIGHT]);
}

int query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return 0;
    if (start <= l && r <= end) return tree[index];
    if (end <= MID) return query(start, end, l, MID, LEFT);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
    return min(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}

int main() {
    int i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) scanf("%d", &a[i]);
    check();
    for (i = 1; i <= n; ++i) {
        if (query(1, a[i] - 1, 1, n, 1) > pre[a[i]]) {
            ok[a[i]] = 1;
        }
        pre[a[i]] = i;
        update(a[i], 1, n, 1, i);
    }

    for (i = 1; i <= n; ++i) {
        if (query(1, i, 1, n, 1) > pre[i+1]) {
            ok[i+1] = 1;
        }
    }

    for (i = 2; i <= n + 2; ++i) {
        if (!ok[i]) {
            printf("%d\n", i);
            break;
        }
    }
    return 0;
}