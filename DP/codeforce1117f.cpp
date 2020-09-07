#include <bits/stdc++.h>
#define MAX_SIZE 131093
using namespace std;

bool ok[MAX_SIZE][17][17];
int cost[MAX_SIZE];
bool valid[MAX_SIZE];
int cnt[MAX_SIZE];
char st[MAX_SIZE];
int can[17][17];
bool tran[MAX_SIZE];
char curr[MAX_SIZE];
int n, k;

void eliminate(int msk, int fi, int se) {
    int i;
    if (!ok[msk][fi][se]) return;
    ok[msk][fi][se] = false;
    valid[msk] = false;
    // cout << "set " << msk << "  to " << 0 << endl;
    for (i = 0 ; i < k; ++i) {
        if (i != fi && i != se && (((1 << i) & msk) == 0)) eliminate(msk | (1 << i), fi, se);
    }
}

int main() {
    int i, j, p;
    scanf("%d%d", &n, &k);
    memset(valid, true, sizeof(valid));
    memset(ok, true, sizeof(ok));    
    scanf("%s", st);
    for (i = 0; i < k; ++i) {
        for (j = 0 ; j < k; ++j) {
            scanf("%d", &can[i][j]);
        }
    }

    for (i = 0 ; i < k; ++i) {
        for (j = 0 ; j < k; ++j) {
            if (can[i][j]) continue;
            int sz = 0, bit = 0;
            for (p = 0; p < n; ++p) {
                if (st[p] == 'a' + i || st[p] == 'a' + j) {
                    curr[sz++] = st[p];
                    if ((sz >= 2 && curr[sz - 2] == 'a' + i && curr[sz-1] == 'a' + j) || (sz >= 2 && curr[sz - 2] == 'a' + j && curr[sz-1] == 'a' + i)) {
                        eliminate(bit, i, j);
                        // cout << "eliminate " << bit << " " << i << " " << j << endl;
                    }
                    bit = 0;
                } else {
                    bit |= 1 << (st[p] - 'a');
                }
            }
        }
    }

    for (i = 0 ; i < n; ++i) {
        ++cnt[st[i] - 'a'];
    }

    for (i = 0 ; i < (1 << k); ++i) {
        cost[i] = n;
        for (j = 0 ; j < k; ++j) {
            if (((i >> j) & 1)) cost[i] -= cnt[j];
        }
    }

    tran[0] = true;
    for (i = 0 ; i < (1 << k); ++i) {
        if (!valid[i]) continue;
        for (j = 0 ; j < k; ++j) {
            if (!(i & (1 << j))) {
                int nxt = i | (1 << j);
                if (!valid[nxt]) continue;
                tran[nxt] |= tran[i];
            }
        }
    }

    int ans = n;
    for (i = 0 ; i < (1 << k); ++i) {
        if (tran[i]) {
            ans = min(ans, cost[i]);
            // cout << "valid " << i << endl;
        }

        // cout << cost[i] << endl;
    }

    printf("%d\n", ans);
    return 0;
}