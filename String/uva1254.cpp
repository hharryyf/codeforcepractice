#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
#define MID ((l+r)>>1)
#define MAX_SIZE 200111
#define MAXLOG 19
// #define WRONGANSWER
using namespace std;

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

int N, Q;
char st[MAX_SIZE];
char ss[MAX_SIZE];
int id[MAX_SIZE], tp[MAX_SIZE];;
vector<pair<string, int>> g[MAX_SIZE];
vector<int> s;
SA sa;

int match(char pt[], int idx) {
    int len = strlen(pt), i;
    for (i = 0 ; i < len; ++i) {
        if (pt[i] < ss[idx + i]) return -1;
        if (pt[i] > ss[idx + i]) return 1;
    }

    return 0;
}

int findL(char pt[], int len) {
    int low = 0, high = sa.n - 1;
    int ret = -1;
    while (low <= high) {
        int mid = (low + high) >> 1;
        // cout << mid << " search " << sa.p[mid] << " ch= " << ss[sa.p[mid]];
        int curr = match(pt, sa.p[mid]);
        // cout << " curr= " << curr << endl;
        if (curr == 0) {
            ret = mid;
            high = mid - 1;
        } else if (curr == -1) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return ret;
}

int findR(char pt[], int len) {
    int low = 0, high = sa.n - 1;
    int ret = -1;
    while (low <= high) {
        int mid = (low + high) >> 1;
        int curr = match(pt, sa.p[mid]);
        if (curr == 0) {
            ret = mid;
            low = mid + 1;
        } else if (curr == -1) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return ret;
}

set<int> tree[524292];
set<int> pullup(set<int> t1, set<int> t2) {
    set<int> ret;
    for (auto v : t1) ret.insert(v);
    for (auto v : t2) ret.insert(v);
    while ((int) ret.size() > 10) {
        ret.erase(*ret.rbegin());
    }
    return ret;
}


void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        if (tp[sa.p[l]] > 0) tree[index].insert(tp[sa.p[l]]);
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

set<int> query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return tree[0];
    if (start <= l && r <= end) return tree[index];
    if (end <= MID) return query(start, end, l, MID, LEFT);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
    return pullup(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}

int main() {
    int i, cnt = 1;
    scanf("%d", &N);
    for (i = 1 ; i <= N; ++i) {
        scanf("%s", st);
        int L = strlen(st);
        g[L].emplace_back(string(st), i);
    }

    for (i = 1; i < MAX_SIZE; ++i) {
        sort(g[i].begin(), g[i].end());
        for (auto &v : g[i]) {
            id[cnt] = v.second;
            for (auto ch : v.first) {
                tp[(int) s.size()] = cnt;
                ss[(int) s.size()] = ch;
                s.push_back((int) ch);
            }
            cnt++;
            ss[(int) s.size()] = '$';
            tp[(int) s.size()] = MAX_SIZE;
            s.push_back((int) '$');
        }
    }
    // cout << ss << endl;
    sa.sort_cyclic_shifts(s);
    build(0, sa.n - 1, 1);
    scanf("%d", &Q);
    while (Q-- > 0) {
        scanf("%s", st);
        int L = findL(st, strlen(st)), R = findR(st, strlen(st));
        // cout << "get L= " << L << " R= " << R << endl;
        if (L > R || L == -1 || R == -1) {
            printf("-1\n");
        } else {
            set<int> ret = query(L, R, 0, sa.n - 1, 1);
            if (ret.empty()) {
                printf("-1\n");
            } else {
                int c = 0;
                for (auto v : ret) {
                    if (c == 0) {
                        printf("%d", id[v]);
                    } else {
                        printf(" %d", id[v]);
                    }
                    ++c;
                }
                printf("\n");
            }
        }
    }
    return 0;
}