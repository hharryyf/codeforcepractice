#include <bits/stdc++.h>
#define MAX_SIZE 10011
typedef long long ll;
const ll inf = 1e16;
using namespace std;

struct edge {
    int from, to, cost, benifit;
};

edge edg[1000011];
map<string, int> mp;
vector<int> g[MAX_SIZE];
ll dist[MAX_SIZE][2];
int B, visited[MAX_SIZE], N;
char st[3][22];
ll dp[MAX_SIZE];

void init() {
    for (int i = 0 ; i < MAX_SIZE; ++i) dist[i][0] = inf;
}

void dfs(int v) {
    visited[v] = 1;
    for (auto e : g[v]) {
        if (!visited[edg[e].to]) {
            dfs(edg[e].to);
        }

        if (dist[v][0] > edg[e].cost + dist[edg[e].to][0]) {
            dist[v][0] = edg[e].cost + dist[edg[e].to][0];
            dist[v][1] = edg[e].benifit + dist[edg[e].to][1];
        } else if (dist[v][0] == edg[e].cost + dist[edg[e].to][0]) {
            dist[v][1] = max(dist[v][1], edg[e].benifit + dist[edg[e].to][1]);
        }
    }

    if (g[v].empty()) {
        dist[v][0] = 0, dist[v][1] = 0;
    }
}

int main() {
    int i, j, sz = 0;
    scanf("%d%d", &B, &N);
    init();
    for (i = 1; i <= N; ++i) {
        scanf("%s%s%s%d%d", st[0], st[1], st[2], &edg[i].cost, &edg[i].benifit);
        if (mp[string(st[0])] == 0) {
            mp[string(st[0])] = ++sz;
        }

        if (mp[string(st[1])] == 0) {
            mp[string(st[1])] = ++sz;
        }

        int d1 = mp[string(st[0])], d2 = mp[string(st[1])];
        edg[i].from = d1, edg[i].to = d2;
        g[d1].push_back(i);
    }        

    for (i = 1; i <= sz; ++i) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    ll ans = 0;
    for (i = 1; i <= sz; ++i) {
        for (j = B; j >= 0; --j) {
            if (j >= dist[i][0]) {
                dp[j] = max(dp[j - dist[i][0]] + dist[i][1], dp[j]);
            }
            ans = max(ans, dp[j]);
        }
    }

    for (i = 0; i <= B; ++i) {
        if (ans == dp[i]) {
            cout << ans << endl;
            cout << i << endl;
            return 0;
        }
    }
    return 0;
}