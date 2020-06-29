#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;
typedef long long ll;

// the a array
ll a[MAX_SIZE];
// the ith set indices
vector<int> g[MAX_SIZE];
// the ith element in which heavy, set
vector<int> h[MAX_SIZE];
// whether the ith set is heavy
int heavy[MAX_SIZE];
// the id of the ith heavy set
int id[MAX_SIZE];
int block_size = 1;
// total number of heavy set
int cnt = 0;
// tag of each heavy set
ll inc[MAX_SIZE];
ll ans[MAX_SIZE];
// the number of overlapping elements between the ith set and the jth heavy set
int occ[MAX_SIZE][321];
char st[4];

int main() {
    int n, m, q, i, k;
    scanf("%d%d%d", &n, &m, &q);
    block_size = sqrt(n);
    for (i = 1; i <= n; ++i) {
        scanf("%I64d", &a[i]);
    }

    for (i = 1; i <= m; ++i) {
        scanf("%d", &k);
        if (k > block_size) {
            heavy[i] = 1;
            id[++cnt] = i;
        }

        while (k-- > 0) {
            int v;
            scanf("%d", &v);
            g[i].push_back(v);
            if (heavy[i]) {
                h[v].push_back(cnt);
                ans[i] += a[v];
            }
        }
    }

    for (i = 1; i <= m; ++i) {
        for (auto v : g[i]) {
            for (k = 0 ; k < (int) h[v].size(); ++k) {
                ++occ[i][h[v][k]];
            }
        }
    }

    while (q-- > 0) {
        int x;
        scanf("%s%d", st, &k);
        if (st[0] == '?') {
            ll ret = 0;
            if (heavy[k]) {
                ret += ans[k];
                for (i = 1; i <= cnt; ++i) {
                    ret += inc[id[i]] * occ[k][i];
                }
            } else {
                for (auto v : g[k]) ret += a[v];
                for (i = 1; i <= cnt; ++i) {
                    ret += inc[id[i]] * occ[k][i];
                }
            }

            printf("%I64d\n", ret);
        } else {
            scanf("%d", &x);
            if (heavy[k]) {
                inc[k] += x;
            } else {
                for (auto v : g[k]) {
                    a[v] += x;
                }

                for (i = 1; i <= cnt; ++i) {
                    ans[id[i]] += occ[k][i] * x;
                }
            }
        }
    }
    return 0;
}