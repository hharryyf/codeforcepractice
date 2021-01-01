#include <bits/stdc++.h>
#define MAX_SIZE 611111
#define MAXLOG 20
typedef long long ll;
using namespace std;

struct SA {
    int p[MAX_SIZE];
    int cnt[MAX_SIZE];
    int c[MAXLOG][MAX_SIZE];
    int logs[MAX_SIZE];
    int rank[MAX_SIZE];
    const int alphabet = 300011;
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

int N;
SA sa;
vector<int> s;
char st[MAX_SIZE];
int pos[MAX_SIZE];
int Len[MAX_SIZE];

int main() {
    int i, j;
    scanf("%d", &N);
    for (i = 1 ; i <= N; ++i) {
        scanf("%s", st);
        pos[i] = (int) s.size();
        int len = strlen(st);
        Len[i] = len;
        for (j = 0 ; j < len; ++j) {
            s.push_back(st[j] - 'a' + N);
        }

        s.push_back(N - i);
    }
    sa.sort_cyclic_shifts(s);
    int Q;
    scanf("%d", &Q);
    while (Q-- > 0) {
        int x, y;
        scanf("%d%d", &x, &y);
        int lcp = sa.lcp(pos[x], pos[y]);
        if (x == y) lcp = Len[x];
        if (lcp == 0) {
            printf("0\n");
            continue;
        }
        if (sa.rank[pos[x]] > sa.rank[pos[y]]) swap(x, y);
        int p = sa.rank[pos[x]];
        int low = 0, high = p, L = p;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (sa.lcp(sa.p[p], sa.p[mid]) >= lcp) {
                high = mid - 1;
                L = mid;
            } else {
                low = mid + 1;
            }
        }

        p = low = sa.rank[pos[y]], high = sa.n - 1;
        int R = p;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (sa.lcp(sa.p[p], sa.p[mid]) >= lcp) {
                low = mid + 1;
                R = mid;
            } else {
                high = mid - 1;
            }
        }

        printf("%d\n", R - L + 1);
    }
    return 0;
}