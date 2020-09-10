#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 400111
#define MAXLOG 19
typedef long long ll;
using namespace std;

struct SA {
    int p[MAX_SIZE];
    int cnt[MAX_SIZE];
    int c[MAXLOG][MAX_SIZE];
    int logs[MAX_SIZE];
    int rank[MAX_SIZE];
    const int alphabet = (MAX_SIZE >> 1);
    int n;
    
    void init() {
        memset(p, 0, sizeof(p));
        memset(cnt, 0, sizeof(cnt));
        memset(c, 0, sizeof(c));
        memset(rank, 0, sizeof(rank));
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

        for (i = 0 ; i < n; ++i) rank[p[i]] = i;
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
int ans[MAX_SIZE << 1];
char st[MAX_SIZE];
int Len[MAX_SIZE];
int fir[MAX_SIZE];
int L[MAX_SIZE], R[MAX_SIZE];
vector<int> ptr;
vector<int> id;
struct qrs {
    int x, y, id, si;
    bool operator < (qrs other) const {
        if (x != other.x) return x < other.x;
        return id < other.id;
    }
};

int cnt = 0;
qrs Q[MAX_SIZE << 3];

void addevent(int x, int y, int id, int si) {
    Q[cnt++] = qrs{x, y, id, si};
}

int tree[MAX_SIZE];
int n;

int shift(int x) {
    return x & (-x);
}

void update(int x) {
    if (x <= 0) return;
    while (x <= n) {
        tree[x] += 1;
        x += shift(x);
    }
}

int query(int x) {
    int ret = 0;
    while (x > 0) {
        ret += tree[x];
        x -= shift(x);
    }
    return ret;
}

int main() {
    int q, i, j;
    scanf("%d%d", &n, &q);
    for (i = 1 ; i <= n; ++i) {
        scanf("%s", st);
        Len[i] = (int) strlen(st);
        fir[i] = (int) ptr.size();
        for (j = 0 ; j < Len[i]; ++j) {
            ptr.push_back(st[j] - 'a' + n);
            id.push_back(i);
        }

        id.push_back(0);
        ptr.push_back(n - i);
    }

    sa.sort_cyclic_shifts(ptr);

    for (i = 1; i <= n; ++i) {
        int low = 0, high = sa.rank[fir[i]];
        L[i] = R[i] = high;
        high--;
        while (low <= high) {
            int mid = (low + high) >> 1;
            if (sa.lcp(sa.p[mid], fir[i]) == Len[i]) {
                L[i] = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        low = sa.rank[fir[i]] + 1, high = sa.n - 1;
        while (low <= high) {
            int mid = (low + high) >> 1;
            if (sa.lcp(sa.p[mid], fir[i]) == Len[i]) {
                R[i] = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }

    for (i = 0 ; i < sa.n; ++i) {
        if (id[sa.p[i]]) {
            addevent(i, id[sa.p[i]], 0, 0);
            // cout << "add point " << i << " " << id[sa.p[i]] << endl;
        }
    }
/*
    for (i = 1; i <= n; ++i) {
        printf("%d %d\n", L[i], R[i]);
    }
*/
    for (i = 1; i <= q; ++i) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        // cout << "query rectangle " << L[k] << " " << l << " " << R[k] << " " << r << endl;
        addevent(R[k], r, i, 1);
        addevent(L[k] - 1, l - 1, i, 1);
        addevent(R[k], l - 1, i, -1);
        addevent(L[k] - 1, r, i, -1);
    }

    sort(Q, Q + cnt);

    for (i = 0; i < cnt; ++i) {
        if (Q[i].id == 0) {
            update(Q[i].y);
        } else {
            ans[Q[i].id] += Q[i].si * query(Q[i].y);
        }
    }

    for (i = 1; i <= q; ++i) printf("%d\n", ans[i]);
    return 0;
}