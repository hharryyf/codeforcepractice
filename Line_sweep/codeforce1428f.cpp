#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 1048592
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
#define MID ((l+r)>>1)
using namespace std;
typedef long long ll;
struct segt {
    ll lz, rsum, rmin;
};

segt tree[MAX_SIZE];

void pushdown(int l, int r, int index) {
    int len1 = MID - l + 1, len2 = r - MID;
    if (l > r) return;
    if (tree[index].lz != 0) {
        if (l != r) {
            tree[LEFT].rmin = tree[index].lz;
            tree[RIGHT].rmin = tree[index].lz;
            tree[LEFT].rsum = tree[index].lz * len1;
            tree[RIGHT].rsum = tree[index].lz * len2;
            tree[LEFT].lz = tree[RIGHT].lz = tree[index].lz;
        }
        tree[index].lz = 0;
    }
}
// search the leftmost idx such that val[idx] < val 
int search(int start, int end, int l, int r, int index, int val) {
    if (start > end || l > r || start > r || l > end) return MAX_SIZE;
    pushdown(l, r, index);
    if (tree[index].rmin >= val) return MAX_SIZE;
    if (start <= l && r <= end) {
        if (l == r) return l;
        if (tree[LEFT].rmin < val) {
            return search(start, end, l, MID, LEFT, val);
        }
        return search(start, end, MID + 1, r, RIGHT, val);
    }

    if (end <= MID) return search(start, end, l, MID, LEFT, val);
    if (start >= MID + 1) return search(start, end, MID + 1, r, RIGHT, val);
    return min(search(start, end, l, MID, LEFT, val), 
               search(start, end, MID + 1, r, RIGHT, val));
}

void update(int start, int end, int l, int r, int index, int val) {
    if (start > end || l > r || start > r || l > end) return;
    pushdown(l, r, index);
    if (start <= l && r <= end) {
        tree[index].lz = val;
        tree[index].rsum = 1ll * (r - l + 1) * val;
        tree[index].rmin = val;
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
    tree[index].rmin = min(tree[LEFT].rmin, tree[RIGHT].rmin);
    tree[index].rsum = tree[LEFT].rsum + tree[RIGHT].rsum;
}

vector<int> vc;
char st[MAX_SIZE];

int main() {
    int n, i, j;
    ll ans = 0;
    scanf("%d", &n);
    scanf("%s", st + 1);
    for (i = 1; i <= n; ++i) {
        if (st[i] == '0') {
            j = 1;
            while (!vc.empty()) {
                update(vc.back(), vc.back(), 1, n, 1, j);
                vc.pop_back();
                ++j;
            }
        } else {
            vc.push_back(i);
            int frt = vc[0];
            int sz = (int) vc.size();
            int pos = search(1, frt - 1, 1, n, 1, sz);
            if (pos <= n) {
                update(pos, frt - 1, 1, n, 1, sz);
            }
        }

        int sz = vc.size();
        ans += tree[1].rsum;
        ans += 1ll * sz * (sz + 1) / 2;
        // cout << tree[1].rsum << " " << sz << endl;
    }

    cout << ans << endl;
    return 0;
}