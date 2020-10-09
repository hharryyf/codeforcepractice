#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
#define MAX_SIZE 524292
#define MAXLOG 20
typedef long long ll;
// #define WRONGANSWER
using namespace std;

struct segt {
    int rmin, cnt;
    segt operator +(segt other) const {
        segt ret;
        ret.rmin = min(rmin, other.rmin);
        ret.cnt = (ret.rmin == rmin) * cnt + (ret.rmin == other.rmin) * other.cnt;
        return ret;
    }
};

struct SA {
    int p[MAX_SIZE];
    int cnt[MAX_SIZE];
    int c[MAXLOG][MAX_SIZE];
    int logs[MAX_SIZE];
    int rank[MAX_SIZE];
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

        for (i = 0 ; i < n; ++i) {
            rank[p[i]] = i;
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

SA sa;
segt tree[MAX_SIZE << 1];
int n;
int prefix[MAX_SIZE];
char st[MAX_SIZE];
string s;

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index].rmin = prefix[l];
        tree[index].cnt = 1;
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index] = tree[LEFT] + tree[RIGHT];
}
// search the left most position that is less than val in range [start, end]
int search(int start, int end, int l, int r, int index, int val) {
    if (start > end || l > r || start > r || l > end) return MAX_SIZE;
    if (tree[index].rmin >= val) return MAX_SIZE;
    if (l == r) return l;
    if (start <= l && r <= end) {
        if (tree[LEFT].rmin < val) return search(start, end, l, MID, LEFT, val);
        return search(start, end, MID + 1, r, RIGHT, val);
    }

    if (end <= MID) return search(start, end, l, MID, LEFT, val);
    if (start >= MID + 1) return search(start, end, MID + 1, r, RIGHT, val);
    return min(search(start, end, l, MID, LEFT, val), search(start, end, MID + 1, r, RIGHT, val));
}

segt query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return tree[0];
    if (start <= l && r <= end) return tree[index];
    if (end <= MID) return query(start, end, l, MID, LEFT);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
    return query(start, end, l, MID, LEFT) + query(start, end, MID + 1, r, RIGHT);
}

int val(char ch) {
    return ch == '(' ? 1 : -1;
}

int getans(int l, int r) {
    int L = l > 0 ? prefix[l-1] : 0;
    int pos = search(l, r, 0, n - 1, 1, L);
    if (pos < n) {
        auto ret = query(l, pos - 1, 0, n - 1, 1);
        if (ret.rmin == L) return ret.cnt;
        return 0;
    }

    auto ret = query(l, r, 0, n - 1, 1);
    if (ret.rmin == L) return ret.cnt;
    return 0;
}

int main() {
    int i;
    ll ans = 0;
    scanf("%d", &n);
    scanf("%s", st);
    s = string(st);
    s += '$';
    sa.sort_cyclic_shifts(s);
    prefix[0] = val(st[0]);
    for (i = 1; i < n; ++i) prefix[i] = prefix[i-1] + val(st[i]);
    build(0, n - 1, 1);
    for (i = 0 ; i < n; ++i) {
        ans += getans(i, n - 1);
    }

    for (i = 0 ; i < sa.n - 1; ++i) {
        int lcp = sa.lcp(sa.p[i], sa.p[i+1]);
        ans -= getans(sa.p[i], sa.p[i] + lcp - 1);
    }

    cout << ans << endl;
    return 0;
}