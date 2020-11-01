#include <bits/stdc++.h>
#define MAX_SIZE 8011
using namespace std;

vector<char> g[MAX_SIZE];
vector<int> p[MAX_SIZE];
int curr[MAX_SIZE];
char st[MAX_SIZE];
int dp[MAX_SIZE];
int numd[MAX_SIZE];

void upd(int idx, char ch) {
    g[idx].push_back(ch);
    // special case for index 1
    if ((int) g[idx].size() == 2) {
        p[idx].push_back(0);
        return;
    }
    while (curr[idx] > 0 && ch != g[idx][curr[idx]+1]) curr[idx] = p[idx][curr[idx]];
    if (g[idx].back() == g[idx][curr[idx]+1]) ++curr[idx];
    p[idx].push_back(curr[idx]);
}

int main() {
    int i, n, j;
    scanf("%s", st + 1);
    n = strlen(st + 1);
    for (i = 1; i <= n; ++i) {
        numd[i] = (int) to_string(i).length();
        g[i].push_back('#');
        p[i].push_back(0);
    }

    for (i = 1; i <= n; ++i) {
        dp[i] = 2 * n + 2;
        for (j = 1; j <= i; ++j) {
            upd(j, st[i]);
            int period = (i - j + 1) - p[j].back();
            // cout << i << ": " << j << " " << period << endl;
            if ((i - j + 1) % period == 0) {
                dp[i] = min(dp[i], dp[j-1] + numd[(i - j + 1) / period] + period);
            }

            dp[i] = min(dp[i], dp[j-1] + (i - j + 1) + 1);
        }
    }

    printf("%d\n", dp[n]);
    return 0;
}