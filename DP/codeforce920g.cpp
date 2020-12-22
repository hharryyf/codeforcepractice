#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 1000011
using namespace std;

vector<int> g[MAX_SIZE];
int visited[MAX_SIZE];

void init() {
    int i, j;
    for (i = 2; i < MAX_SIZE; ++i) {
        if (!visited[i]) {
            for (j = 1; i * j < MAX_SIZE; ++j) {
                visited[i * j] = 1;
                g[i * j].push_back(i);
            }
        }
    }
}

int check(int x, int p) {
    int ret = 0, i, j, sz = g[p].size();
    for (i = 1 ; i < (1 << sz); ++i) {
        int curr = 1;
        for (j = 0 ; j < sz; ++j) {
            if ((1 << j) & i) {
                curr = curr * g[p][j];
            }
        }

        if (__builtin_popcount(i) & 1) {
            ret = ret + x / curr;
        } else {
            ret = ret - x / curr;
        }
    }

    return ret;
}

int main() {
    int T;
    init();
    scanf("%d", &T);
    while (T-- > 0) {
        int x, p, k;
        scanf("%d%d%d", &x, &p, &k);
        int low = x + 1, high = 20000000;
        int ans = 0, prefix = check(x, p);
        while (low <= high) {
            int mid = (low + high) / 2;
            if (mid - check(mid, p) + prefix - x >= k) {
                high = mid - 1;
                ans = mid;
            } else {
                low = mid + 1;
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}