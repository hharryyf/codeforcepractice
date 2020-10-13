#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
#define MAX_SIZE 200111
typedef long long ll;
using namespace std;

const ll mod = 1e9 + 7;
struct segt {
    int left, right;
    int val;
};
// decreasing stack of factor[i] (power, pos)
vector<pair<int, int>> power[MAX_SIZE];
// cost is the initially multiplied power
vector<int> cost[MAX_SIZE];
vector<int> prime;
segt tree[MAX_SIZE * 200];
int root[MAX_SIZE << 4];
int rcnt = 0, cnt = 0, n;
int version[MAX_SIZE >> 1];
int visited[MAX_SIZE];

ll fastpower(ll val, ll p) {
    ll ret = 1;
    while (p > 0) {
        if (p % 2 == 1) {
            ret = ret * val;
            ret %= mod;
            p--;
        } else {
            val = val * val;
            val %= mod;
            p /= 2;
        }
    }
    return ret;
}

int build(int l, int r) {
    if (l > r) return 0;
    int curr = ++cnt;
    if (l == r) {
        tree[curr].val = 1;
        return curr;
    }

    tree[curr].left = build(l, MID);
    tree[curr].right = build(MID + 1, r);
    ll ret = 1ll * tree[tree[curr].left].val * tree[tree[curr].right].val;
    tree[curr].val = ret % mod;
    return curr;
}
// multiply pt by val given rt
int update(int pt, int rt, int l, int r, int val) {
    if (pt < l || pt > r || rt == 0 || l > r) return rt;
    int curr = ++cnt;
    tree[curr] = tree[rt];
    if (l == r) {
        ll ret = 1ll * tree[curr].val * val;
        tree[curr].val = ret % mod;
        return curr;
    }

    if (pt <= MID) {
        tree[curr].left = update(pt, tree[curr].left, l, MID, val);
    } else {
        tree[curr].right = update(pt, tree[curr].right, MID + 1, r, val);
    }
    ll ret = 1ll * tree[tree[curr].left].val * tree[tree[curr].right].val;
    tree[curr].val = ret % mod;
    return curr;
}

int query(int rt, int start, int end, int l, int r) {
    if (start > end || l > r || start > r || l > end || rt == 0) return 1;
    if (start <= l && r <= end) return tree[rt].val;
    if (end <= MID) return query(tree[rt].left, start, end, l, MID);
    if (start >= MID + 1) return query(tree[rt].right, start, end, MID + 1, r);
    auto p1 = 1ll * query(tree[rt].left, start, end, l, MID);
    auto p2 = 1ll * query(tree[rt].right, start, end, MID + 1, r);
    return (p1 * p2) % mod;
}

void updateT(int pos, ll val) {
    if (val == 1) return;
    root[rcnt + 1] =  update(pos, root[rcnt], 1, n, val);
    rcnt++;
}

// we must make sure that pri is prime
void upd(int pos, int pri, int pw) {
    auto p = make_pair(pw, pos);
    while (!power[pri].empty()) {
        auto p2 = power[pri].back();
        int sz = power[pri].size();
        if (p < p2) {
            cost[pri][sz - 1] -= pw;
            updateT(power[pri][sz - 1].second, fastpower(fastpower(pri, pw), mod - 2));        
            power[pri].push_back(p);
            cost[pri].push_back(pw);
            updateT(pos, fastpower(pri, pw));
            break;
        }

        // we eliminate sz-1 and restore sz-2 if exists
        updateT(p2.second, fastpower(fastpower(pri, cost[pri][sz - 1]), mod - 2));
        cost[pri].pop_back();
        power[pri].pop_back();
        sz--;
        if (sz > 0) {
            updateT(power[pri][sz - 1].second, fastpower(pri, power[pri][sz - 1].first - cost[pri][sz - 1]));
            cost[pri][sz - 1] = power[pri][sz - 1].first;
        }
    }

    if (power[pri].empty()) {
        power[pri].push_back(p);
        cost[pri].push_back(pw);
        updateT(pos, fastpower(pri, pw));
    }
}

void insert(int pos, int val) {
    if (val == 1) {
        version[pos] = root[rcnt];
        return;
    }

    int sz = prime.size(), i;
    for (i = 0 ; i < sz; ++i) {
        int cnt = 0;
        while (val % prime[i] == 0) {
            cnt++;
            val /= prime[i];
        }
        if (cnt > 0) upd(pos, prime[i], cnt);
    }

    if (val > 1) upd(pos, val, 1); 
    version[pos] = root[rcnt];
}

int a[MAX_SIZE];



int main() {
    int i, j;
    scanf("%d", &n);
    for (i = 2; i <= 200000; ++i) {
        if (visited[i]) continue;
        if (i < 500) prime.push_back(i);
        for (j = 1; j * i <= 200000; ++j) visited[j * i] = 1;
    }
    version[0] = root[0] = build(1, n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        insert(i, a[i]);
    }

    int q;
    scanf("%d", &q);
    ll lst = 0;
    while (q-- > 0) {
        int l, r;
        scanf("%d%d", &l, &r);
        l = (lst + l) % n + 1;
        r = (lst + r) % n + 1;
        if (l > r) swap(l, r);
        printf("%I64d\n", lst = query(version[r], l, r, 1, n));
    
    }

    return 0;
}