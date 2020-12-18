#include <bits/stdc++.h>
#define MAX_SIZE 2011
using namespace std;
char st[MAX_SIZE][MAX_SIZE];
int U[MAX_SIZE][MAX_SIZE], D[MAX_SIZE][MAX_SIZE], L[MAX_SIZE][MAX_SIZE], R[MAX_SIZE][MAX_SIZE];
int LU[MAX_SIZE][MAX_SIZE], RU[MAX_SIZE][MAX_SIZE], LD[MAX_SIZE][MAX_SIZE], RD[MAX_SIZE][MAX_SIZE];
int N, M;


int main() {
    int i, j;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= N; ++i) scanf("%s", st[i] + 1);
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            L[i][j] = L[i][j-1] * (st[i][j] == st[i][j-1]) + 1;
        }

        for (j = M; j >= 1; --j) {
            R[i][j] = R[i][j+1] * (st[i][j] == st[i][j+1]) + 1;
        }
    }

    for (i = 1; i <= M; ++i) {
        for (j = 1; j <= N; ++j) {
            U[j][i] = U[j-1][i] * (st[j-1][i] == st[j][i]) + 1;
        }
        
        for (j = N; j >= 1; --j) {
            D[j][i] = D[j+1][i] * (st[j+1][i] == st[j][i]) + 1;
        }
    }

    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            if (st[i][j] == st[i-1][j-1]) {
                LU[i][j] = min(min(U[i][j], L[i][j]), LU[i-1][j-1] + 2);
            } else {
                LU[i][j] = min(min(L[i][j], U[i][j]), 2);
            }
        }

        for (j = M; j >= 1; --j) {
            if (st[i][j] == st[i-1][j+1]) {
                RU[i][j] = min(min(U[i][j], R[i][j]), RU[i-1][j+1] + 2);
            } else {
                RU[i][j] = min(min(R[i][j], U[i][j]), 2);
            }
        }
    }

    for (i = N; i >= 1; --i) {
        for (j = 1; j <= M; ++j) {
            if (st[i][j] == st[i+1][j-1]) {
                LD[i][j] = min(min(L[i][j], D[i][j]), LD[i+1][j-1] + 2);
            } else {
                LD[i][j] = min(min(L[i][j], D[i][j]), 2);
            }
        }

        for (j = M; j >= 1; --j) {
            if (st[i][j] == st[i+1][j+1]) {
                RD[i][j] = min(min(R[i][j], D[i][j]), RD[i+1][j+1] + 2);
            } else {
                RD[i][j] = min(min(R[i][j], D[i][j]), 2);
            }
        }
    }


    long long ans = 0;
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            ans = ans + min(min(LU[i][j], LD[i][j]), min(RU[i][j], RD[i][j]));
            //printf("(%d %d %d %d %d %d %d %d)    ", LU[i][j], LD[i][j], RU[i][j], RD[i][j], L[i][j], R[i][j], D[i][j], U[i][j]);
        }
        // printf("\n");
    }

    printf("%I64d\n", ans);
    return 0;
}