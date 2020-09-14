#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int n, i;
        scanf("%d", &n);
        set<int> ans;
        for (i = 1; i <= sqrt(n); ++i) {
            ans.insert(n / i);
            ans.insert(n / (n / i));
        }
        ans.insert(0);
        printf("%d\n", (int) ans.size());
        for (auto v : ans) {
            printf("%d ", v);
        }
        printf("\n");
    }
    return 0;
}