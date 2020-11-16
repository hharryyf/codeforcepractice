#include <bits/stdc++.h>
using namespace std;


int main() {
    int i, n, k;
    scanf("%d%d", &n, &k);
    int block_size = (n - k) / 2 + 1;
    for (i = 1; i <= n; ++i) {
        printf("%d", (i % block_size) > 0);
    }
    return 0;
}