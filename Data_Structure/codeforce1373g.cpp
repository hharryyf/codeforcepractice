#include <bits/stdc++.h>
#define MAX_SIZE 1048596
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;

struct segt {
    int value, lz;
};

segt tree[MAX_SIZE];
int n;

void pushdown(int l, int r, int index) {
    if (l > r) return;
    if (tree[index].lz) {
        if (l != r) {
            tree[LEFT].lz += tree[index].lz;
            tree[RIGHT].lz += tree[index].lz;
            tree[LEFT].value += tree[index].lz;
            tree[RIGHT].value += tree[index].lz;
        }
        tree[index].lz = 0;
    }
}

void update(int start, int end, int l, int r, int index, int val) {
    if (start > end || l > r || start > r || l > end) return;
    pushdown(l, r, index);
    if (start <= l && r <= end) {
        tree[index].lz += val;
        tree[index].value += val;
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

    tree[index].value = max(tree[LEFT].value, tree[RIGHT].value);
}

int query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return 0;
    pushdown(l, r, index);
    if (start <= l && r <= end) return tree[index].value;    
    if (end <= MID) return query(start, end, l, MID, LEFT);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
    return max(query(start, end, l, MID, LEFT), 
               query(start, end, MID + 1, r, RIGHT));
}

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index].value = l - 1 - n;
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index].value = max(tree[LEFT].value, tree[RIGHT].value);
}

set<int> g[MAX_SIZE];
multiset<int> upward;

int main() {
    int q, k;
    scanf("%d%d%d", &n, &k, &q);
    build(1, 2 * n, 1);
    while (q-- > 0) {
        int x, y;
        scanf("%d%d", &x, &y);
        int Y = y + abs(k - x);
        if (g[x].find(y) != g[x].end()) {
            update(1, Y, 1, 2 * n, 1, -1);
            upward.erase(upward.find(Y));
            g[x].erase(y);
        } else {
            update(1, Y, 1, 2 * n, 1, 1);
            upward.insert(Y);
            g[x].insert(y);
        }    

        if (upward.empty()) {
            printf("0\n");
        } else {
            printf("%d\n", max(0, query(1, *upward.rbegin(), 1, 2 * n, 1)));
        }
    }
    return 0;
}