#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int n, i, v;
        scanf("%d", &n);
        vector<int> ret;
        for (i = 0 ; i < n; ++i) {
            scanf("%d", &v);
            ret.push_back(v);
        }

        reverse(ret.begin(), ret.end());
        for (auto v : ret) {
            printf("%d " , v);
        }
        printf("\n");
    }
    return 0;
}