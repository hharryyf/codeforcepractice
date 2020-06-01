#include <bits/stdc++.h>

using namespace std;

int T, n, m;
int cnt[55];
int ans[55][55];

int main() {
    int i, j, a, b;
    scanf("%d", &T);
    while (T > 0) {
        scanf("%d%d%d%d", &n, &m, &a, &b);
        if (n * a != m * b) {
            printf("NO\n");
        } else {
            vector<pair<int, int>> col;
            for (i = 0; i < n; ++i) {
                for (j = 0 ; j < m; ++j) {
                    ans[i][j] = 0;
                    cnt[j] = 0;
                }
            }

            for (i = 0 ; i < m; ++i) {
                col.emplace_back(0, i);
            }

            for (i = 0 ; i < n; ++i) {
                sort(col.begin(), col.end());
                for (j = 0 ; j < a; ++j) {
                    ans[i][col[j].second] = 1;
                    cnt[col[j].second]++;
                }

                col.clear();
                for (j = 0 ; j < m; ++j) {
                    col.emplace_back(cnt[j], j);
                }
            }
            
            printf("YES\n");
            for (i = 0 ; i < n; ++i) {
                for (j = 0 ; j < m; ++j) {
                    printf("%d", ans[i][j]);
                }
                printf("\n");
            }
        }
        --T;
    }
    return 0;
}