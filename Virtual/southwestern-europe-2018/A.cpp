#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;

int a[MAX_SIZE];

int main() {
    int i, N, k, ans = 0, curr = 0;
    scanf("%d%d", &N, &k);
    while (k-- > 0) {
        int v;
        scanf("%d", &v);
        for (i = v; i <= N; i = i + v) {
            curr += (a[i]^1) - a[i];
            a[i] ^= 1;
        }

        ans = max(ans, curr);
        // cout << curr << endl;
    }

    printf("%d\n", ans);
    return 0;
}