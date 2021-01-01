#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 1000211
#define MAXLOG 20
typedef long long ll;
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
        memset(rank, 0, sizeof(rank));
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

int N;
int cost[MAX_SIZE];
SA sa;
string s;
char pt[105];
char st[MAX_SIZE];
int cnt;
pair<int, int> pos[10011];
int dp[10011][105];

int match(char pt[], int idx) {
    int len = strlen(pt), i;
    for (i = 0 ; i < len; ++i) {
        if (pt[i] < st[idx + i]) return -1;
        if (pt[i] > st[idx + i]) return 1;
    }

    return 0;
}

int findL(char pt[]) {
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

int findR(char pt[]) {
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

int main() {
    int T, i, j;
    freopen("cenzura.in", "r", stdin);
    freopen("cenzura.out", "w", stdout);
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        scanf("%s", st);
        cnt = 0;
        s = string(st);
        s += '$';
        sa.init();
        sa.sort_cyclic_shifts(s);
        for (i = 0 ; i < N; ++i) scanf("%d", &cost[i]);
        int M;
        scanf("%d", &M);
        pos[cnt].first = -1, pos[cnt++].second = -1;
        for (j = 0 ; j < M; ++j) {
            scanf("%s", pt);
            int len = strlen(pt);
            int L = findL(pt), R = findR(pt);
            if (L != -1 && R != -1) {
                for (i = L; i <= R; ++i) {
                    pos[cnt].first = sa.p[i] + len - 1;
                    pos[cnt++].second = sa.p[i];
                }
            }
        }

        sort(pos, pos + cnt);

        dp[0][0] = 0;
        for (i = 1; i < cnt; ++i) {
            int cst = 1010000000;
            // cout << pos[i].second << " " << pos[i].first << endl;
            for (j = pos[i-1].second; j <= pos[i-1].first; ++j) {
                cst = min(cst, dp[i-1][j - pos[i-1].second]);
                if (pos[i].second <= j) {
                    dp[i][j - pos[i].second] = dp[i-1][j - pos[i-1].second];
                }
            }

            for (j = pos[i].second; j <= pos[i].first; ++j) {
                if (j > pos[i-1].first || j < pos[i-1].second) {
                    dp[i][j - pos[i].second] = min(1010000000, cst + cost[j]);
                }
            }
        }       

        int ans = 1010000000;
        for (i = pos[cnt-1].second; i <= pos[cnt-1].first; ++i) {
            ans = min(ans, dp[cnt-1][i - pos[cnt-1].second]);
        }
        printf("%d\n", ans);
    }
    return 0;
}