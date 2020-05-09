#include <bits/stdc++.h>
#define MAX_SIZE 151111
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;

struct segt {
    int value, lz;
};

segt tree[MAX_SIZE << 2];
vector<int> disc;
int b[MAX_SIZE], a[MAX_SIZE];

void pushdown(int l, int r, int index) {
    if (l > r) return;
    if (tree[index].lz != 0) {
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

    // TODO
    tree[index].value = max(tree[LEFT].value, tree[RIGHT].value);
}


int main() {
    int i, h, n, len, ans = 0;
    scanf("%d%d%d", &n, &len, &h);
    for (i = 1; i <= len; ++i) {
        scanf("%d", &b[i]);
        b[i] = h - b[i];
    }

    sort(b + 1, b + 1 + len);
    for (i = 1; i <= len; ++i) {
        if (i == 1 || b[i] != b[i-1]) {
            disc.push_back(b[i]);
        }
    }

    int sz = disc.size();
    for (i = 1; i <= len; ++i) {
        int index = lower_bound(disc.begin(), disc.end(), b[i]) - disc.begin();
        update(0, index, 0, sz - 1, 1, 1);
        // cout << "update " << 0 << " " << index << " by " << 1 << endl;
    }

    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }

    for (i = 1; i <= n; ++i) {
        // can match with all b between [index, sz -1]
        int index;
        if (i > len) {
            // withdraw a[i-len]
            index = upper_bound(disc.begin(), disc.end(), a[i-len]) - disc.begin() - 1;
            update(0, index, 0, sz - 1, 1, 1);
            // cout << "withdraw " << 0 << " " << index << endl;
        }
        index = upper_bound(disc.begin(), disc.end(), a[i]) - disc.begin() - 1;
        // update the affect of a[i]
        update(0, index, 0, sz - 1, 1, -1);
        // cout << "update " << 0 << " " << index << " by -1 " << endl;
        // update answer
        if (i >= len) {
            ans += tree[1].value <= 0;
        }
    }

    printf("%d\n", ans);
    return 0;
}