#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

pair<int, int> valid[MAX_SIZE];
pair<int, int> s[MAX_SIZE];
int ans[MAX_SIZE];

int main() {
    int n, i, j;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d%d", &s[i].first, &s[i].second);
        s[i].second += s[i].first;
    }

    valid[1] = s[1];

    for (i = 1; i < n; ++i) {
        valid[i+1].first = max(valid[i].first - 1, s[i+1].first);
        valid[i+1].second = min(valid[i].second + 1, s[i+1].second);
    }

    for (i = 1; i <= n; ++i) {
        if (valid[i].first > valid[i].second) {
            printf("%d\n", -1);
            return 0;
        }
    }

    ans[n] = valid[n].second;
    for (i = n - 1; i >= 1; --i) {
        for (j = 1; j >= -1; --j) {
            if (ans[i+1] + j <= valid[i].second && ans[i+1] + j >= valid[i].first) {
                ans[i] = ans[i+1] + j;
                break;
            }
        }
    }

    long long tol = 0;
    for (i = 1; i <= n; ++i) {
        tol += ans[i] - s[i].first;
    }

    printf("%I64d\n", tol);
    for (i = 1; i <= n; ++i) printf("%d ", ans[i]);
    return 0;
}