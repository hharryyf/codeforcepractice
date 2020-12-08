#include <bits/stdc++.h>
#define MAX_SIZE 524292
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
typedef long long ll;
using namespace std;
const ll mod = 1e9 + 7;

struct segt {
    ll val, cnt;
};


pair<int, int> doll[MAX_SIZE];
segt tree[MAX_SIZE];
int tmp[MAX_SIZE], dcnt[MAX_SIZE];
vector<int> disc;
int N;

segt pullup(segt t1, segt t2) {
    segt ret;
    ret.val = min(t1.val, t2.val);
    ret.cnt = 1ll * (ret.val == t1.val) * t1.cnt + 1ll * (ret.val == t2.val) * t2.cnt;
    ret.cnt %= mod;
    return ret;
}

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index].val = mod + disc[l];
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

void update(int pt, int l, int r, int index, ll val, ll cnt) {
    if (pt < l || pt > r || l > r) return;
    if (l == r) {
        if (tree[index].val == val) {
            tree[index].cnt += cnt;
            tree[index].cnt %= mod;
        } else if (tree[index].val > val) {
            tree[index].val = val;
            tree[index].cnt = cnt % mod;
        }
        return;
    }

    if (pt <= MID) {
        update(pt, l, MID, LEFT, val, cnt);
    } else {
        update(pt, MID + 1, r, RIGHT, val, cnt);
    }

    tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

segt query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return segt{mod, 0};
    if (start <= l && r <= end) return tree[index];
    if (end <= MID) {
        return query(start, end, l, MID, LEFT);
    } else if (start >= MID + 1) {
        return query(start, end, MID + 1, r, RIGHT);
    }

    return pullup(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}

int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d%d", &doll[i].second, &doll[i].first);
        tmp[i] = doll[i].first;
    }

    sort(doll + 1, doll + 1 + N);
    sort(tmp + 1, tmp + 1 + N);

    for (i = 1; i <= N; ++i) {
        if (i == 1 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
    }

    int sz = disc.size();
    build(0, sz - 1, 1);
    for (i = N; i >= 1; --i) {
        int idx = lower_bound(disc.begin(), disc.end(), doll[i].second) - disc.begin();
        if (idx <= sz - 1) {
            // cout << "doll in= " << doll[i].first << " out= " << doll[i].second << endl;
            // cout << "get idx= " << idx << endl;
            auto ret = query(idx, sz - 1, 0, sz - 1, 1);
            // cout << "get " << ret.val << " " << ret.cnt << " nxt= " << ret.val + doll[i].first - doll[i].second << endl;
            idx = lower_bound(disc.begin(), disc.end(), doll[i].first) - disc.begin();
            update(idx, 0, sz - 1, 1, ret.val + doll[i].first - doll[i].second, ret.cnt);
        } else {
            idx = lower_bound(disc.begin(), disc.end(), doll[i].first) - disc.begin();
            update(idx, 0, sz - 1, 1, doll[i].first, 1);
        }
    }

    printf("%I64d\n", tree[1].cnt);
    return 0;
}