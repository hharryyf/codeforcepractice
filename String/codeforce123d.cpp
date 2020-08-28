#include <bits/stdc++.h>
#define MAX_SIZE 100111
#define MAXLOG 18
typedef long long ll;
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
string s;
char st[MAX_SIZE];
vector<int> height;
vector<pair<pair<int, int>, ll>> vc;

int main() {
    int T = 1, i;
    ll ans = 0, curr = 0;
    while (T-- > 0) {
        ans = 0;
        sa.init();
        s.clear();
        height.clear();
        vc.clear();
        scanf("%s", st);
        s = string(st);
        s += '$';
        sa.sort_cyclic_shifts(s);
        for (i = 1 ; i < sa.n - 1; ++i) {
            height.push_back(sa.lcp(sa.p[i], sa.p[i+1]));
        }

        for (i = 0 ; i < (int) height.size(); ++i) {
            // ans += height[i];
            while (!vc.empty() && height[i] <= vc.back().first.first) {
                // cout << "pop " << vc.back().first.first << endl;
                vc.pop_back();
            }

            if (vc.empty()) {
                curr = 1ll * (i + 1) * height[i];
            } else {
                curr = 1ll * (i - vc.back().first.second) * height[i] + vc.back().second;
            }

            ans += curr;
            // cout << "h["<< i << "]= " << height[i] << " += " << curr << endl;
            vc.push_back(make_pair(make_pair(height[i], i), curr));
        }

        int N = strlen(st);
        ans = ans + 1ll * N * (N + 1) / 2;
        printf("%I64d\n", ans);
    }
    return 0;
}