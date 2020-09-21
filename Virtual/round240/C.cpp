#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, k, i;
    scanf("%d%d", &n, &k);
    if (n == 1) {
        if (k == 0) {
            printf("1\n");
        } else {
            printf("-1\n");
        }

        return 0;
    }

    vector<int> ans;
    if (n % 2 == 1) {
        ans.push_back(8e8);
        n--;
    }

    if (k < n / 2) {
        printf("-1\n");
        return 0;
    }

    int curr = 1e9;
    for (i = 1; i <= n / 2 - 1; ++i) {
        ans.push_back(curr);
        ans.push_back(curr - 1);
        curr -= 2;
    }

    ans.push_back(k - n / 2 + 1);
    ans.push_back((k - n / 2 + 1) * 2);
    reverse(ans.begin(), ans.end());
    for (auto v : ans) {
        printf("%d ", v);
    }
    return 0;
}