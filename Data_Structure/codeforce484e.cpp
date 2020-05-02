#include <bits/stdc++.h>
#define MAX_SIZE 262192
#define MID ((l+r)>>1)
using namespace std;
/*
    The hardest part is realizing the divide and conquer direction works
*/

struct divc {
    // maxleft, maxright, maxans, range length
    int maxl, maxr, ans, len;
};

struct segt {
    int left, right;
    divc ans;
};

segt tree[MAX_SIZE * 30];
int cnt = 0;
int root[MAX_SIZE >> 1];
pair<int, int> pannel[MAX_SIZE >> 1]; 

int build(int l, int r) {
    if (l > r) return 0;
    int curr = ++cnt;
    if (l == r) {
        tree[curr].ans.len = 1;
        return curr;
    }

    tree[curr].left = build(l, MID);
    tree[curr].right = build(MID + 1, r);
    tree[curr].ans.len = tree[tree[curr].left].ans.len + tree[tree[curr].right].ans.len;
    return curr;
}

divc pullup(divc &t1, divc &t2) {
    divc ret;
    ret.len = t1.len + t2.len;
    ret.maxl = t1.maxl + (t1.maxl == t1.len) * t2.maxl;
    ret.maxr = t2.maxr + (t2.maxr == t2.len) * t1.maxr;
    ret.ans = max(max(t1.ans, t2.ans), t1.maxr + t2.maxl);
    return ret;
}

int update(int rt, int pos, int l, int r) {
    if (rt == 0 || pos < l || pos > r || l > r) return rt;
    int curr = ++cnt;
    tree[curr] = tree[rt];
    if (pos == l && l == r) {
        tree[curr].ans.maxl = tree[curr].ans.maxr = tree[curr].ans.ans = 1;
        return curr;
    }

    if (pos <= MID) {
        tree[curr].left = update(tree[rt].left, pos, l, MID);
    } else {
        tree[curr].right = update(tree[rt].right, pos, MID + 1, r);
    }

    tree[curr].ans = pullup(tree[tree[curr].left].ans, tree[tree[curr].right].ans);
    return curr;
}

divc query(int rt, int start, int end, int l, int r) {
    if (rt == 0 || start > end || l > r || start > r || l > end) return tree[0].ans;
    if (start <= l && r <= end) return tree[rt].ans;
    if (end <= MID) {
        return query(tree[rt].left, start, end, l, MID);
    } else if (start >= MID + 1) {
        return query(tree[rt].right, start, end, MID + 1, r);
    }

    divc t1 = query(tree[rt].left, start, end, l, MID), t2 = query(tree[rt].right, start, end, MID + 1, r);
    return pullup(t1, t2);
}

int n, q;
vector<int> disc;

int main() {
    int i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &pannel[i].first);
        pannel[i].first = -pannel[i].first;
        pannel[i].second = i;
        disc.push_back(-pannel[i].first);
    }

    sort(pannel + 1, pannel + 1 + n);
    sort(disc.begin(), disc.end(), greater<int>());
    root[0] = build(1, n);
    for (i = 1; i <= n; ++i) {
        root[i] = update(root[i-1], pannel[i].second, 1, n);
    }

    scanf("%d", &q);
    while (q > 0) {
        int l, r, w;
        scanf("%d%d%d", &l, &r, &w);
        int low = 0, high = n-1, ans = 0;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (query(root[mid + 1], l, r, 1, n).ans >= w) {
                ans = disc[mid];
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        printf("%d\n", ans);
        --q;
    }
    return 0;
}