#include <bits/stdc++.h>
#define MAX_SIZE 511
using namespace std;

int a[MAX_SIZE], b[MAX_SIZE];
int T, n;

int main() {
    int i;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &n);
        vector<pair<int, int>> ap, bp;
        for (i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }

        for (i = 1; i <= n; ++i) {
            scanf("%d", &b[i]);
        }

        if (n % 2 == 1 && a[n/2 + 1] != b[n/2 + 1]) {
            printf("No\n");
            continue;
        }

        for (i = 1; i <= n / 2; ++i) {
            if (a[i] > a[n - i + 1]) {
                swap(a[i], a[n - i + 1]);
            }

            if (b[i] > b[n - i + 1]) {
                swap(b[i], b[n - i + 1]);
            }

            ap.emplace_back(a[i], a[n - i + 1]);
            bp.emplace_back(b[i], b[n - i + 1]);
        }

        sort(ap.begin(), ap.end());
        sort(bp.begin(), bp.end());
        bool flag = true;
        for (i = 0 ; i < (int) ap.size(); ++i) {
            flag = flag && (ap[i] == bp[i]);
        }

        printf("%s\n", flag ? "yes" : "No");
    }   
    return 0;
}