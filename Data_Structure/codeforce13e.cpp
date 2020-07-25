#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define REP(i,a,b) for(i=a;i<=b;++i)
#define RREP(i,a,b) for(i=a;i>=b;--i)
#define MAX_SIZE 100011
using namespace std;

int N, Q;
int block_size;
int q[MAX_SIZE][3];
int nxt[MAX_SIZE], f[MAX_SIZE], wt[MAX_SIZE], ok[MAX_SIZE];

int main() {
    int i, j, L, R, ret = 0, v;
    scanf("%d%d", &N, &Q);
    block_size = sqrt(N);
    REP(i, 1, N) {
        scanf("%d", &f[i]);
        nxt[i] = f[i] = min(f[i] + i, N + 1);
        ok[i] = wt[i] = 1;
    }

    REP(i, 0, Q-1) {
        scanf("%d", &q[i][0]);
        ++q[i][0];
        if (q[i][0] == 1) {
            scanf("%d%d", &q[i][1], &q[i][2]);
        } else {
            scanf("%d", &q[i][1]);
        }
    }

    REP(i, 0, Q-1) {
        L = i * block_size, R = min(L + block_size - 1, Q - 1);
        if (L >= Q || L > R) break;
        REP(j, L, R) {
            if (q[j][0] == 1) {
                ok[q[j][1]] = 0;
            }
        }

        RREP(j, N, 1) {
            f[j] = nxt[j];
            wt[j] = 1;
            if (ok[j]) {
                if (ok[f[j]] && f[f[j]] != N + 1) {
                    f[j] = f[f[j]];
                    wt[j] =  wt[nxt[j]] + 1;
                } 
            } else {
                wt[j] = 1;
            }
        }
/*
        REP (j, 1, N) {
            cout << "f[" << j << "]= " << f[j] << " wt[" << j << "]= " << wt[j] << endl;
        }
*/
        REP(j, L, R) {
            if (q[j][0] == 1) {
                nxt[q[j][1]] = f[q[j][1]] = min(q[j][1] + q[j][2], N + 1);
            } else {
                v = q[j][1];
                ret = 0;
                while (v != N + 1) {
                    ret += wt[v];
                    if (f[v] == N + 1) {
                        printf("%d %d\n",  v, ret);
                    }
                    v = f[v];
                }
            }
        }

        REP(j, L, R) {
            ok[q[j][1]] |= (q[j][0] == 1);
        }
    }
    return 0;
}
