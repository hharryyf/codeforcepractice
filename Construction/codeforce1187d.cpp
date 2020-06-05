#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 1048597
#define MID ((l+r)>>1)
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)
using namespace std;

int tree[MAX_SIZE];
int a[MAX_SIZE >> 1];
int b[MAX_SIZE >> 1];
list<int> q[MAX_SIZE >> 1];
int n;

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index] = a[l];
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index] = min(tree[LEFT], tree[RIGHT]);
}

void update(int pt, int l, int r, int index, int val) {
    if (pt < l || l > r || pt > r) return;
    if (l == r) {
        tree[index] = val;
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
    if (start > end || l > r || start > r || l > end) return MAX_SIZE;
    if (start <= l && r <= end) return tree[index];
    if (end <= MID) {
        return query(start, end, l, MID, LEFT);
    }

    if (start >= MID + 1) {
        return query(start, end, MID + 1, r, RIGHT);
    }

    return min(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}

void init() {
    int i;
    for (i = 1 ; i <= n; ++i) {
        q[i].clear();
    }
}

int main() {
    int i, T;
    scanf("%d", &T);
    while (T > 0) {
        bool valid = true;
        scanf("%d", &n);
        init();
        for (i = 1; i <= n; ++i) scanf("%d", &a[i]);
        for (i = 1; i <= n; ++i) scanf("%d", &b[i]);
        build(1, n, 1);
        for (i = 1; i <= n; ++i) {
            q[a[i]].push_back(i);
        }

        for (i = 1; i <= n; ++i) {
            if (q[b[i]].empty()) {
                valid = false;
                break;
            }

            int pos = q[b[i]].front();
            q[b[i]].pop_front();
            if (query(1, pos, 1, n, 1) != b[i]) {
                valid = false;
                break;
            }

            update(pos, 1, n, 1, MAX_SIZE);
        }

        printf("%s\n", valid ? "YES" : "NO");
        --T;
    }
    return 0;
}