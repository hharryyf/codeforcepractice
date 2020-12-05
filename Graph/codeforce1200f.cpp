#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;

const int mod = 2520;
vector<int> g[MAX_SIZE];
int outd[MAX_SIZE];
int val[MAX_SIZE];
int dp[MAX_SIZE][mod + 4];
int visited[MAX_SIZE][mod + 4];
int ok = 0;
vector<pair<int, int>> vis;
int N;

void dfs(int v, int num) {
    num %= mod;
    if (visited[v][num] == 1) {
        ok = dp[v][num];
        return;
    }
    vis.emplace_back(v, num);
    visited[v][num] = 1;
    int nxt = (num + val[v]) % outd[v];
    if (nxt < 0) nxt += outd[v];
    dfs(g[v][nxt], (num + val[v]) % mod);
}

int main() {
    int i, j, k;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &val[i]);
        val[i] = val[i] % mod;
        if (val[i] < 0) val[i] += mod;
    }

    for (i = 1; i <= N; ++i) {
        scanf("%d", &outd[i]);
        for (j = 0 ; j < outd[i]; ++j) {
            int v;
            scanf("%d", &v);
            g[i].push_back(v);
        }
    }

    for (i = 1; i <= N; ++i) {
        for (j = 0 ; j < mod; ++j) {
            ok = 0;
            vis.clear();
            dfs(i, j);
            if (ok == 0) {
                int sz = vis.size();
                set<int> st;
                int nxt = (vis[sz - 1].second + val[vis[sz - 1].first]) % outd[vis[sz - 1].first];
                int nxtval = (vis[sz - 1].second + val[vis[sz - 1].first]) % mod;
                if (nxt < 0) nxt += outd[vis[sz - 1].first];    
                for (k = sz - 1; k >= 0; --k) {
                    st.insert(vis[k].first);
                    if (g[vis[sz - 1].first][nxt] == vis[k].first && nxtval == vis[k].second) {
                        break;
                    }
                }

                for (auto v : vis) {
                    dp[v.first][v.second] = (int) st.size();
                }
            } else {
                for (auto v : vis) {
                    dp[v.first][v.second] = ok;
                }
            }
        }
    }

    int q;
    scanf("%d", &q);
    while (q-- > 0) {
        int x, y;
        scanf("%d%d", &x, &y);
        y = (y % mod + mod) % mod;
        printf("%d\n", dp[x][y]);
    }
    return 0;
}