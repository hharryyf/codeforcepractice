#include <bits/stdc++.h>

using namespace std;

int main() {
    int W, N, tol = 0;
    scanf("%d%d", &W, &N);
    while (N-- > 0) {
        int u, v;
        scanf("%d%d", &u, &v);
        tol = tol + u * v;
    }

    printf("%d\n", tol / W);
    return 0;
}