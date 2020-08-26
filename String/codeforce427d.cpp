#include <bits/stdc++.h>
#define MAX_SIZE 16394
#define MAXLOG 16
using namespace std;

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

SA sa;
char s1[MAX_SIZE], s2[MAX_SIZE];
char st[MAX_SIZE];
string s;
vector<int> p1, p2;
int lc1[MAX_SIZE][2], lc2[MAX_SIZE][2];

int main() {
    int i, n, m;
    scanf("%s", s1);
    scanf("%s", s2);
    n = strlen(s1), m = strlen(s2);
    for (i = 0 ; i < MAX_SIZE; ++i) {
        lc1[i][0] = -MAX_SIZE - i;
        lc2[i][0] = - 2 * MAX_SIZE - i;
        lc1[i][1] = -MAX_SIZE * 3 - i;
        lc2[i][1] = -MAX_SIZE * 4 - i;
    }

    for (i = 0 ; i < n; ++i) {
        st[i] = s1[i];
    }
    st[n] = '$';
    for (i = 0 ; i < m; ++i) {
        st[i+n+1] = s2[i]; 
    }
    st[n+m+1] = '#';

    s = string(st);

    sa.sort_cyclic_shifts(s);

    for  (i = 0 ; i < sa.n; ++i) {
        if (sa.p[i] < n) {
            p1.push_back(sa.p[i]);
        } else if (sa.p[i] != n + m + 1) {
            p2.push_back(sa.p[i]);
        }
    }

    for (i = 0 ; i < (int) p1.size() - 1; ++i) {
        int val = sa.lcp(p1[i], p1[i+1]);
        lc1[p1[i]][0] = lc1[p1[i+1]][1] = val;
    }

    for (i = 0 ; i < (int) p2.size() - 1; ++i) {
        int val = sa.lcp(p2[i], p2[i+1]);
        lc2[p2[i]][0] = lc2[p2[i+1]][1] = val;
    }

    int ans = MAX_SIZE;
    for (i = 0 ; i < sa.n - 1; ++i) {
        if (s[sa.p[i]] == '#' || s[sa.p[i]] == '$' || s[sa.p[i+1]] == '#' || s[sa.p[i+1]] == '$') continue;
        if (sa.p[i] < n && sa.p[i+1] < n) continue;
        if (sa.p[i] > n && sa.p[i+1] > n) continue;
        int val = sa.lcp(sa.p[i], sa.p[i+1]);
        if (val == 0) continue;
        if (sa.p[i] < n) {
            if (val <= lc1[sa.p[i]][0] || val <= lc1[sa.p[i]][1]) continue;
            if (val <= lc2[sa.p[i+1]][0] || val <= lc2[sa.p[i+1]][1]) continue;
            int t1 = 1 + max(0, max(lc1[sa.p[i]][0], lc1[sa.p[i]][1]));
            int t2 = 1 + max(0, max(lc2[sa.p[i+1]][0], lc2[sa.p[i+1]][1]));
            val = min(val, max(t1, t2));
        } else {
            if (val <= lc2[sa.p[i]][0] || val <= lc2[sa.p[i]][1]) continue;
            if (val <= lc1[sa.p[i+1]][0] || val <= lc1[sa.p[i+1]][1]) continue;
            int t1 = 1 + max(0, max(lc2[sa.p[i]][0], lc2[sa.p[i]][1]));
            int t2 = 1 + max(0, max(lc1[sa.p[i+1]][0], lc1[sa.p[i+1]][1]));
            val = min(val, max(t1, t2));
        }
        
        // cout << sa.p[i] << " " << sa.p[i+1] << endl;
        ans = min(ans, val);
    }

    if (ans == MAX_SIZE) ans = -1;
    printf("%d\n", ans);
    return 0;
}