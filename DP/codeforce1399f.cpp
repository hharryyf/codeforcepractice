#include <bits/stdc++.h>
#define MAX_SIZE 6011
using namespace std;

vector<int> disc;
int dp[MAX_SIZE][MAX_SIZE];

pair<int, int> it[MAX_SIZE];
int tmp[MAX_SIZE];
vector<pair<int, int>> g[MAX_SIZE];

int f(int l, int r) {
    if (l > r) return 0;
    if (dp[l][r] != -1) return dp[l][r];
    int ans = 0, has = 0;
    ans = f(l + 1, r);
    for (auto v : g[l]) {
        if (v.first > r) continue;
        if (v.first == r) {
            has = v.second;
        } else {
            ans = max(ans, f(l, v.first) + f(v.first + 1, r));
        }
    }
    
    ans += has;
    return dp[l][r] = ans;
}

int main() {
    int T;
    scanf("%d", &T);
    map<pair<int, int>, int> st;
    while (T-- > 0) {
        int n, i, j;
        scanf("%d", &n);
        st.clear();
        disc.clear();
        for (i = 1; i <= n; ++i) {
            scanf("%d%d", &it[i].first, &it[i].second);
            tmp[i * 2 - 1] = it[i].first, tmp[i * 2] = it[i].second;
            st[make_pair(it[i].first, it[i].second)]++;
        }

        sort(tmp + 1, tmp + 1 + n * 2);
        for (i = 1; i <= 2 * n; ++i) {
            if (i == 1 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
        }

        for (i = 0; i <= 2 * n; ++i) {
            for (j = i; j <= 2 * n; ++j) {
                dp[i][j] = -1;
            }

            g[i].clear();
        }

        for (auto p : st) {
            int id1 = lower_bound(disc.begin(), disc.end(), p.first.first) - disc.begin() + 1;
            int id2 = lower_bound(disc.begin(), disc.end(), p.first.second) - disc.begin() + 1;
            g[id1].emplace_back(id2, p.second);
        }

        dp[0][0] = 0;
        int sz = disc.size();
        printf("%d\n", f(1, sz));
    }
    return 0;
}