#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 200111
#define MAXLOG 19
typedef long long ll;
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
char S[MAX_SIZE];
string s;
int N, Q;
vector<int> a, b;
vector<pair<int, int>> evt;

static bool cmp(const int &i1, const int &i2) {
    return sa.rank[i1] < sa.rank[i2];
}

void solve() {
    evt.clear();
    sort(a.begin(), a.end(), cmp);
    sort(b.begin(), b.end(), cmp);
    ll ans = 0, curr = 0;
    int i, j, sz1 = a.size(), sz2 = b.size();
    for (i = 0, j = 0; i < sz1; ++i) {
        while (j < sz2 && sa.rank[b[j]] <= sa.rank[a[i]]) {
            evt.emplace_back(b[j++], 0);
        }
        evt.emplace_back(a[i], 1);
    }

    while (j < sz2) evt.emplace_back(b[j++], 0);

    stack<pair<int, int>> stk;
    for (i = 0 ; i < sz1 + sz2; ++i) {
        if (!evt[i].second) ans += curr;
        // update evt[i], evt[i+1] to the lcp
        if (i != sz1 + sz2 - 1) {
            int p = sa.lcp(evt[i].first, evt[i+1].first);
            int tol = evt[i].second;
            while (!stk.empty() && stk.top().first >= p) {
                curr -= 1ll * stk.top().first * stk.top().second;
                tol += stk.top().second;
                stk.pop();
            }
            curr += 1ll * p * tol;
            stk.push(make_pair(p, tol));
        }
        // if  (!evt[i].second) cout << "curr= " << curr << endl;
        
    }

    while (!stk.empty()) stk.pop();
    evt.clear();
    for (i = 0, j = 0; i < sz1; ++i) {
        while (j < sz2 && sa.rank[b[j]] < sa.rank[a[i]]) {
            evt.emplace_back(b[j++], 0);
        }
        evt.emplace_back(a[i], 1);
    }

    while (j < sz2) evt.emplace_back(b[j++], 0);
    curr = 0;
    for (i = sz1 + sz2 - 1 ; i >= 0; --i) {
        // update evt[i], evt[i+1] to the lcp
        if (!evt[i].second) ans += curr;
        if (i != 0) {
            int p = sa.lcp(evt[i].first, evt[i-1].first);
            int tol = evt[i].second;
            while (!stk.empty() && stk.top().first >= p) {
                curr -= 1ll * stk.top().first * stk.top().second;
                tol += stk.top().second;
                stk.pop();
            }
            curr += 1ll * p * tol;
            // cout << "p= " << p << " tol= " << tol << endl;
            stk.push(make_pair(p, tol));
        }
        // if (!evt[i].second) cout << "i= " << i << " curr= " << curr << endl;
    }

    set<int> stt;
    for (auto v : a) stt.insert(v);
    for (auto v : b) {
        if (stt.find(v) != stt.end()) ans += N - v;
    }
    
    cout << ans << endl;
}

int main() {
    scanf("%d%d", &N, &Q);
    scanf("%s", S);
    s = string(S);
    s += '$';
    sa.sort_cyclic_shifts(s);
    while (Q-- > 0) {
        a.clear(), b.clear();
        int k1, k2, v;
        scanf("%d%d", &k1, &k2);
        while (k1-- > 0) {
            scanf("%d", &v);
            a.push_back(v-1);
        }

        while (k2-- > 0) {
            scanf("%d", &v);
            b.push_back(v-1);
        }

        solve();
    }
    return 0;
}