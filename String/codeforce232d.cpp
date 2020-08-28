#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 200111
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
#define MAXLOG 19
// #define WRONGANSWER
using namespace std;

struct SA {
    int p[MAX_SIZE];
    int cnt[MAX_SIZE];
    int c[MAXLOG][MAX_SIZE];
    int logs[MAX_SIZE];
    int rank[MAX_SIZE];
    const int alphabet = 200011;
    int n;
    
    void init() {
        memset(p, 0, sizeof(p));
        memset(cnt, 0, sizeof(cnt));
        memset(c, 0, sizeof(c));
    }

    void sort_cyclic_shifts(vector<int> &s) {
        int h, i;
        n = (int) s.size();    
        for (i = 2; i < MAX_SIZE; ++i) logs[i] = logs[i/2]+1;
        for (i = 0; i < n; i++)
            cnt[s[i]]++;
        for (i = 1; i < alphabet; i++)
            cnt[i] += cnt[i-1];
        for (i = 0; i < n; i++)
            p[--cnt[s[i]]] = i;
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

struct Persistent_rangetree {
    struct segt {
        int left, right;
        int rsum;
    };

    segt tree[MAX_SIZE * 45];
    int root[MAX_SIZE];
    int cnt = 0;
    int n;

    int build(int l, int r) {
        if (l > r) return 0;
        int curr = ++cnt;
        if (l == r) return curr;
        tree[curr].left = build(l, MID);
        tree[curr].right = build(MID + 1, r);
        return curr;
    }

    int update(int rt, int pos, int l, int r, int val) {
        if (rt == 0 || l > r || pos < l || pos > r) return rt;
        int curr = ++cnt;
        tree[curr] = tree[rt];
        if (pos == l && l == r) {
            tree[curr].rsum += val;
            return curr;
        }
        
        if (pos <= MID) {
            tree[curr].left = update(tree[rt].left, pos, l, MID, val);
        } else {
            tree[curr].right = update(tree[rt].right, pos, MID + 1, r, val);
        }
        
        tree[curr].rsum = tree[tree[curr].left].rsum + tree[tree[curr].right].rsum;
        return curr;
    }

    int getans(int rt, int start, int end, int l, int r) {
        if (start > end || l > r || rt == 0 || start > r || l > end) return 0;
        if (start <= l && r <= end) return tree[rt].rsum;
        if (end <= MID) return getans(tree[rt].left, start, end, l, MID);
        if (start >= MID + 1) return getans(tree[rt].right, start, end, MID + 1, r);
        return getans(tree[rt].left, start, end, l, MID) + getans(tree[rt].right, start, end, MID + 1, r);
    }

    int query(int l, int r, int d, int u) {
        if (l > r || u < d) return 0; 
        int ret = getans(root[r], d, u, 0, n) - 
            (l >= 1 ? getans(root[l-1], d, u, 0, n) : 0);
        return ret;
    }
};

Persistent_rangetree t;
SA sa;
vector<int> vc;
int a[MAX_SIZE];
int tmp[MAX_SIZE];
vector<int> disc;
int N, Q;

int main() {
    int i;
    scanf("%d", &N);
    for (i = 0 ; i < N; ++i) {
        scanf("%d", &a[i]);
    }

    for (i = 0; i < N - 1; ++i) {
        a[i] = a[i+1] - a[i];
        tmp[i] = a[i];
    }
    tmp[N - 1] = a[N - 1] = -2e9 - 7;
    for (i = N; i < 2 * N - 1; ++i) {
        a[i] = -a[i - N];
        tmp[i] = a[i];
    }
    tmp[2 * N - 1] = a[2 * N - 1] = -2e9 - 4;
    
    sort(tmp, tmp + 2 * N);
    for (i = 0 ; i < 2 * N; ++i) {
        if (i == 0 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
    }

    for (i = 0 ; i < 2 * N; ++i) {
        a[i] = lower_bound(disc.begin(), disc.end(), a[i]) - disc.begin();
        vc.push_back(a[i]);
    }

    sa.sort_cyclic_shifts(vc);

    t.n = sa.n + 1;
    t.root[0] = t.build(0, t.n);
    for (i = 0; i < sa.n; ++i) {
        t.root[i+1] = t.update(t.root[i], sa.p[i], 0, t.n, 1);
    }

    #ifdef WRONGANSWER
    for (auto v : vc) cout << v << " ";
    cout << endl; 
    #endif
    scanf("%d", &Q);
    while (Q-- > 0) {
        int l, r;
        scanf("%d%d", &l, &r);
        if (l == r) {
            printf("%d\n", N - 1);
            continue;
        }

        --l, --r;
        // rank l
        int p = sa.rank[l];
        int L = p, R = p;
        int low = 0, high = p;
        while (low <= high) {
            int mid = (low + high)>>1;
            if (sa.lcp(sa.p[mid], l) >= r-l) {
                L = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        low = p, high = sa.n - 1;
        while (low <= high) {
            int mid = (low+high)>>1;
            if (sa.lcp(sa.p[mid], l) >= r-l) {
                low = mid + 1;
                R = mid;
            } else {
                high = mid - 1;
            }
        }

        #ifdef WRONGANSWER
        cout << L << " : " << R << endl;
        #endif
        ++L, ++R;
        int ans = t.query(L, R, N, 2 * l + N - r - 1);
        // cout << "get " << N << " to " << 2 * l + N - r << endl;
        ans += t.query(L, R, N + r + 1, 2 * N - r + l);
        // cout << "get " << N + r + 1 << " to " << 2 * N - r + l << endl;
        printf("%d\n", ans);
    }
    return 0;
}