#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;
int a[3];
int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d%d%d", &a[0], &a[1], &a[2]);
        sort(a, a + 3);
        printf("%d\n", min((a[0] + a[1] + a[2]) / 2, a[0] + a[1]));
    }
    return 0;
}