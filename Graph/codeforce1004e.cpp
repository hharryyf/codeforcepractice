#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

int dp1[MAX_SIZE], dp2[MAX_SIZE];
vector<pair<int, int>> g[MAX_SIZE];
// (v, weight)
vector<pair<int, int>> diameter;
int n, k;

void dfs(int v, int pre) {
    for (auto np : g[v]) {
        int nv = np.first, w = np.second;
        if (nv != pre) {
            dfs(nv, v);
            dp1[v] = max(dp1[v], w + dp1[nv]);
        }   
    }
}

void dfs2(int v, int pre) {
    multiset<int> st;
    for (auto np : g[v]) {
        if (np.first != pre) {
            st.insert(dp1[np.first] + np.second);
        }
    }

    for (auto np : g[v]) {
        int nv = np.first, w = np.second;
        if (nv != pre) {
            dp2[nv] = dp2[v] + w;
            st.erase(st.find(dp1[nv] + w));
            if (!st.empty()) {
                dp2[nv] = max(dp2[nv], w + *st.rbegin());
            }
            st.insert(dp1[nv] + w);
        }
    }

    for (auto np : g[v]) {
        if (np.first != pre) {
            dfs2(np.first, v);
        }
    }
}

int pre[MAX_SIZE];
int weight[MAX_SIZE];
int visited[MAX_SIZE];
int dist[MAX_SIZE];

int dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    memset(visited, 0, sizeof(visited));
    memset(dist, 1e9 + 7, sizeof(dist));
    for (auto np : diameter) {
        dist[np.first] = 0;
        q.push(make_pair(0, np.first));
    }

    while (!q.empty()) {
        auto p = q.top();
        q.pop();
        if (visited[p.second]) continue;
        visited[p.second] = 1;
        dist[p.second] = p.first;
        for (auto np : g[p.second]) {
            int nv = np.first;
            if (!visited[nv]) {
                if (dist[nv] > dist[p.second] + np.second) {
                    dist[nv] = dist[p.second] + np.second;
                    q.push(make_pair(dist[nv], nv));
                }
            }
        }
    }

    int ret = 0;
    for (int i = 1; i <= n; ++i) {
        ret = max(ret, dist[i]);
    }
    return ret;
}

int main() {
    int i;
    scanf("%d%d", &n, &k);
    for (i = 0 ; i < n - 1; ++i) {
        int v1, v2, w;
        scanf("%d%d%d", &v1, &v2, &w);
        g[v1].emplace_back(v2, w);
        g[v2].emplace_back(v1, w);
    }

    if (n == 1) {
        printf("0\n");
        return 0;
    }

    dfs(1, 0);    
    dfs2(1, 0);
    
    for (i = 1; i <= n; ++i) {
        dp1[i] = max(dp1[i], dp2[i]);
    }

    int id1 = 1, id2 = 1;
    for (i = 1; i <= n; ++i) {
        if (dp1[id1] < dp1[i]) {
            id1 = i;
        }
    }

    for (i = 1; i <= n; ++i) {
        if (dp1[id1] == dp1[i] && i != id1) {
            id2 = i;
        }
    }

    queue<int> q;
    q.push(id1);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (visited[v]) continue;
        if (v == id2) break;
        visited[v] = 1;
        for (auto np : g[v]) {
            if (!visited[np.first]) {
                pre[np.first] = v;
                weight[np.first] = np.second;
                q.push(np.first);
            }
        }
    }

    int v = id2;
    while (v != id1) {
        diameter.emplace_back(v, weight[v]);
        v = pre[v];
    }

    diameter.emplace_back(id1, 0);

    int ans = dijkstra(), tmp = 2e9;
    int L = 0, R = 0;
    for (auto p : diameter) {
        R += p.second;
    }

    tmp = min(tmp, max(L, R));
    for (i = 0 ; i < (int) diameter.size(); ++i) {
        R -= diameter[i].second;
        if (i + 1 >= k) {
            L += diameter[i+1-k].second;
        }
        tmp = min(tmp, max(L, R));
    }

    printf("%d\n", max(ans, tmp));
    return 0;
}