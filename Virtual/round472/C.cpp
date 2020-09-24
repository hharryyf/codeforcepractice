#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;

vector<int> disc;

int main() {
    int n, U, i;
    double ans = -1;
    scanf("%d%d", &n, &U);
    for (i = 0; i < n; ++i) {
        int v;
        scanf("%d", &v);
        disc.push_back(v);
    }

    for (i = 0 ; i < n - 2; ++i) {
        // disc[i], disc[i+1] and max j such that disc[j] - disc[i] <= U
        int idx = upper_bound(disc.begin(), disc.end(), U + disc[i]) - disc.begin() - 1;
        if (idx > i + 1) {
            ans = max(ans, 1.0 * (disc[idx] - disc[i+1]) / (disc[idx] - disc[i]));
        }
    }

    if (ans < 0) {
        printf("-1\n");
    } else {
        // cout << ans << endl;
        printf("%.10lf\n", ans);
    }
    return 0;
}