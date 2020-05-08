#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m, i, j;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n / 2; ++i) {
        for (j = 1; j <= m; ++j) {
            printf("%d %d\n", i, j);
            printf("%d %d\n", n - i + 1, m - j + 1);
        }
    }

    if (n % 2 == 1) {
        int down = 1,up = m;
        for(i = 1;i <= m;++i) {
            if(i%2==1) {
                printf("%d %d\n",n/2+1,down++);
            } else {
                printf("%d %d\n",n/2+1,up--);
            }
        }
    }
    return 0;
}