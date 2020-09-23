#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    int i, a, b;
    scanf("%d%d", &a, &b);
    for (i = 1; i <= a - 1; ++i) {
        int se = sqrt(a * a - i * i);
        int l1 = se * b / a, l2 = i * b / a;
        if (se > 0 && l1 * l1 + l2 * l2 == b * b && se * se + i * i == a * a && (se * b / a) != i) {
            printf("YES\n");
            printf("%d %d\n", i, se + i * b / a);
            printf("%d %d\n", 0, i * b / a);
            printf("%d %d\n", se * b / a, 0);
            return 0;
        }
    }

    printf("NO\n");
    return 0;
}