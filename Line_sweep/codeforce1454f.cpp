#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

int logs[MAX_SIZE], a[MAX_SIZE], mxL[MAX_SIZE], mxR[MAX_SIZE], N;
int table[19][MAX_SIZE];

void precompute() {
    int i;
    for (i = 2; i < MAX_SIZE; i++) {
        logs[i] = logs[i/2] + 1;
    }
}

int RMQ(int l, int r) {
    if (l > r) return 4 * MAX_SIZE;
    int len = r - l + 1;
    return min(table[logs[len]][l], table[logs[len]][r - (1 << logs[len]) + 1]);
}

void build() {
    int i, j;
    for (i = 1; i <= N; i++) {
        table[0][i] = a[i];
    }

    mxL[0] = mxR[N+1] = 0;
    for (i = 1; i <= N; ++i) {
        mxL[i] = max(mxL[i-1], a[i]);
    }

    for (i = N; i >= 1; --i) {
        mxR[i] = max(mxR[i+1], a[i]);
    }
    
    for (i = 1; i <= 18; i++) {
        int prel = (1 << (i - 1));
        for (j = 1; j <= N; ++j) {
            table[i][j] = 0;
        }

        for (j = 1; j <= N; j++) {
            if (j + prel <= N) {
                table[i][j] = min(table[i-1][j], table[i-1][j+prel]);
            } else {
                table[i][j] = table[i-1][j];
            }
        }
    }
}

int main() {
    int T;
    precompute();
    scanf("%d", &T);
    while (T-- > 0) {
        int i;
        scanf("%d", &N);
        bool ok = false;
        for (i = 1; i <= N; ++i) scanf("%d", &a[i]);
        build();
        for (i = 2; i <= N - 1; ++i) {
            int val = mxR[i + 1];
            int low = 1, high = i - 1, l1 = -1, r1 = -1;
            while (low <= high) {
                int mid = (low + high) / 2;
                if (mxL[mid] >= val) {
                    high = mid - 1;
                    l1 = mid;
                } else {
                    low = mid + 1;
                }
            }

            low = 1, high = i - 1;
            while (low <= high) {
                int mid = (low + high) / 2;
                if (mxL[mid] <= val) {
                    low = mid + 1;
                    r1 = mid;
                } else {
                    high = mid - 1;
                }
            }

            if (l1 == -1 || r1 == -1) continue;
            if (mxL[l1] != val || mxL[r1] != val) continue;

            int l2 = -1, r2 = -1;
            low = 2, high = i;
            while (low <= high) {
                int mid = (low + high) / 2;
                if (RMQ(mid, i) >= val) {
                    high = mid - 1;
                    l2 = mid;
                } else {
                    low = mid + 1;
                }
            }

            low = 2, high = i;
            while (low <= high) {
                int mid = (low + high) / 2;
                if (RMQ(mid, i) <= val) {
                    low = mid + 1;
                    r2 = mid;
                } else {
                    high = mid - 1;
                }
            }
            // printf("i= %d: %d %d %d %d\n", i, l1, r1, l2, r2);
            if (r2 == -1 || l2 == -1) continue;
            if (RMQ(r2, i) != val || RMQ(l2, i) != val) continue;
            if (l2 - r1 > 1) continue;
            vector<int> candidate;
            candidate.push_back(l1 - 1);
            candidate.push_back(l1);
            candidate.push_back(l2 - 1);
            candidate.push_back(l2);
            candidate.push_back(r1);
            candidate.push_back(r1 - 1);
            candidate.push_back(r2 - 1);
            for (auto v : candidate) {
                if (v >= l1 && v <= r1 && v + 1 >= l2 && v + 1 <= r2) {
                    printf("YES\n%d %d %d\n", v, i - v, N - i);
                    ok = true;
                    break;
                }
            }

            if (ok) break;
        }

        if (!ok) {
            printf("NO\n");
        }
    }

    return 0;
}