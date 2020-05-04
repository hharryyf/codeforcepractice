#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;
vector<int> g[MAX_SIZE];

int main() {
    int n, k, pos = 0, i, id = 1, j;
    scanf("%d%d", &n, &k);
    for (i = 0; i < n && id <= n; ++i) {
        for (j = 1; j <= k && id <= n; ++j) {
            g[i].push_back(id);
            ++id;
        }

        if (id >= n) {
            pos = i;
        }
    }

    printf("%d\n", (n-1)/k * 2 + ((n-1)%k > 0) + ((n-1)% k > 1));
    for (i = pos - 1; i >= 1; --i) {
        for (j = 0 ; j < k; ++j) {
            printf("%d %d\n", g[i][j], g[i-1][j]);   
        }
    }    

    int sz = g[pos].size();
    for (i = 0 ; i < sz; ++i) {
        printf("%d %d\n", g[pos][i], g[pos-1][i]);
    }

    for (i = sz; i < k; ++i) {
        printf("%d %d\n", g[pos][sz-1], g[pos-1][i]);
    }

    if (sz > 1) {
        for (i = 1 ; i < sz; ++i) {
            printf("%d %d\n", g[pos][0], g[pos][i]);
        }
    }
    return 0;
}   