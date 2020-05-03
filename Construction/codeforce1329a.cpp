#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;
typedef long long ll;
int a[MAX_SIZE];
int ans[MAX_SIZE];

int main() {
    int m, n, i;
    ll sm = 0;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; ++i) {
        scanf("%d", &a[i]);
        sm += a[i];
    }

    if (sm < 1ll * n) {
        printf("-1\n");
        return 0;
    }

    for (i = 1; i <= m; ++i) {
        ans[i] = max(1ll * i, 1ll * n - sm + 1);
        if (ans[i] + a[i] - 1 > n) {
            printf("-1\n");
            return 0;
        }
        sm -= a[i];        
    }

    for (i = 1; i <= m; ++i) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}