#include <bits/stdc++.h>
#define MAX_SIZE 111
using namespace std;
typedef long long ll;

int ans[MAX_SIZE];
int n, m;

int main() {
    int i, j;
    scanf("%d%d", &n, &m);
    for (i = 0 ; i < m; ++i) {
        int v;
        scanf("%d", &v);
        for (j = v; j <= n; ++j) {
            if (ans[j] == 0) ans[j] = v;
        }
    }

    for (i = 1; i <= n; ++i) {
        printf("%d ", ans[i]);
    }
    return 0;
}