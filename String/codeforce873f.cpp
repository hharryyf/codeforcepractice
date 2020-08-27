#include <bits/stdc++.h>
#define MAX_SIZE 262192
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
#define MAXLOG 19
typedef long long ll;
using namespace std;
/*
    The most excited fact is this is the second suffix array problem I faced,
    and I solved it completely by myself.
    Like KMP the focal point is the fail table, for SA the focal point is the height array.
*/
struct SA {
    int p[MAX_SIZE];
    int cnt[MAX_SIZE];
    int c[MAXLOG][MAX_SIZE];
    int logs[MAX_SIZE];
    const int alphabet = 256;
    int n;
    
    void init() {
        memset(p, 0, sizeof(p));
        memset(cnt, 0, sizeof(cnt));
        memset(c, 0, sizeof(c));
    }

    void sort_cyclic_shifts(string &s) {
        int h, i;
        n = (int) s.size();    
        for (i = 2; i < MAX_SIZE; ++i) logs[i] = logs[i/2]+1;
        for (i = 0; i < n; i++)
            cnt[(int) s[i]]++;
        for (i = 1; i < alphabet; i++)
            cnt[i] += cnt[i-1];
        for (i = 0; i < n; i++)
            p[--cnt[(int) s[i]]] = i;
        c[0][p[0]] = 0;
        int classes = 1;
        for (i = 1; i < n; i++) {
            if (s[p[i]] != s[p[i-1]])
                classes++;
            c[0][p[i]] = classes - 1;
        }

        vector<int> pn(n), cn(n);
        for (h = 0; (1 << h) < n; ++h) {
            for (i = 0; i < n; i++) {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0)
                    pn[i] += n;
            }
            fill(cnt, cnt + classes, 0);
            for (i = 0; i < n; i++)
                cnt[c[h][pn[i]]]++;
            for (i = 1; i < classes; i++)
                cnt[i] += cnt[i-1];
            for (i = n-1; i >= 0; i--)
                p[--cnt[c[h][pn[i]]]] = pn[i];
            cn[p[0]] = 0;
            classes = 1;
            for (i = 1; i < n; i++) {
                pair<int, int> cur = {c[h][p[i]], c[h][(p[i] + (1 << h)) % n]};
                pair<int, int> prev = {c[h][p[i-1]], c[h][(p[i-1] + (1 << h)) % n]};
                if (cur != prev)
                    ++classes;
                cn[p[i]] = classes - 1;
            }
            
            for (i = 0 ; i < n; ++i) {
                c[h+1][i] = cn[i];
            }
        }
    }

    int lcp(int i, int j) {
        int ans = 0, k;
        for (k = logs[n]; k >= 0; k--) {
            if (c[k][i] == c[k][j]) {
                ans += 1 << k;
                i += 1 << k;
                j += 1 << k;
            }
        }
        return ans;
    }
};

struct segt {
    int L, R, ans, len;
};

segt tree[MAX_SIZE << 1];

segt pullup(segt t1, segt t2) {
    segt ret;
    ret.len = t1.len + t2.len;
    ret.ans = max(max(t1.ans, t2.ans), t1.R + t2.L);
    ret.L = t1.L + (t1.L == t1.len) * t2.L;
    ret.R = t2.R + (t2.R == t2.len) * t1.R;
    return ret;
}

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index].len = 1;
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index].len = tree[LEFT].len + tree[RIGHT].len;
}

void update(int pt, int l, int r, int index, int val) {
    if (l > r || pt < l || pt > r) return;
    if (l == r) {
        tree[index].ans += val;
        tree[index].L += val;
        tree[index].R += val;
        return;
    }

    if (pt <= MID) {
        update(pt, l, MID, LEFT, val);
    } else {
        update(pt, MID + 1, r, RIGHT, val);
    }

    tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}


SA sa;
int N;
char st[MAX_SIZE];
char pos[MAX_SIZE];
string s;
vector<int> valid;
// height and pos
vector<pair<int, int>> height;

int main() {
    int i, j;
    ll ans = 0;
    scanf("%d", &N);
    scanf("%s", st);
    scanf("%s", pos);
    for (i = 0 ; i < N; ++i) {
        if (pos[i] == '0') {
            ans = max(ans, 1ll * (i + 1));
        }
    }
    reverse(st, st + N);
    reverse(pos, pos + N);
    s = string(st);
    s += '$';
    sa.sort_cyclic_shifts(s);
    for (i = 0 ; i < sa.n; ++i) {
        if (sa.p[i] < N && pos[sa.p[i]] == '0') {
            valid.push_back(sa.p[i]);
        }
    }

    for (i = 0 ; i < (int) valid.size() - 1; ++i) {
        height.emplace_back(sa.lcp(valid[i], valid[i+1]), i);
        if (height.back().first == 0) height.pop_back();
    }

    int sz = height.size();
    build(0, sz - 1, 1);
    for (auto h : height) {
        update(h.second, 0, sz - 1, 1, 1);
    }

    sort(height.begin(), height.end());
    int mx = height.empty() ? 0 : height.back().first;
    for (i = 1, j = 0; i <= mx; ++i) {
        ans = max(ans, 1ll * (tree[1].ans + 1) * i);
        while (j < sz && height[j].first == i) {
            update(height[j].second, 0, sz - 1, 1, -1);
            ++j;
        }
    }

    printf("%I64d\n", ans);
    return 0;
}