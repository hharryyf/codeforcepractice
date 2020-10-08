#include <bits/stdc++.h>
#define MAX_SIZE 300011
typedef long long ll;
using namespace std;
const ll inf = 1e13;
vector<pair<int, ll>> g[MAX_SIZE];
ll dist[MAX_SIZE];
int visited[MAX_SIZE];

void dijkstra(int src, int target) {
    int i;
    for (i = 0 ; i < MAX_SIZE; ++i) dist[i] = inf;
    dist[src] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
    q.push(make_pair(src, 0));
    while (!q.empty()) {
        auto p = q.top();
        q.pop();
        if (visited[p.second]) continue;
        visited[p.second] = 1;
        dist[p.second] = p.first;
        for (auto np : g[p.second]) {
            int nv = np.first;
            ll wt = np.second;
            if (!visited[nv] && dist[nv] > dist[p.second] + wt) {
                dist[nv] = dist[p.second] + wt;
                q.push(make_pair(dist[nv], nv));
            }
        }
    }
    cout << dist[target] << endl;
}

// src is 0, rows 1 - row.size(), cols row.size() + 1, row.size() + col.size()
// target 1 + row.size() + col.size()
vector<int> row;
vector<int> col;
vector<pair<int, int>> coord;
pair<int, int> S, F;

static bool cmp(pair<int, int> &p1, pair<int, int> &p2) {
    return p1.second < p2.second;
}

void addedge(int from, int to, ll wt) {
    g[from].emplace_back(to, wt);
}

int main() {
    int i, n, m;
    scanf("%d%d", &n, &m);
    scanf("%d%d%d%d", &S.first, &S.second, &F.first, &F.second);
    for (i = 0; i < m; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        coord.emplace_back(x, y);
    }

    sort(coord.begin(), coord.end());
    for (i = 0 ; i < m; ++i) {
        if (i == 0 || coord[i].first != coord[i-1].first) row.push_back(coord[i].first);
    }

    sort(coord.begin(), coord.end(), cmp);
    for (i = 0 ; i < m; ++i) {
        if (i == 0 || coord[i].second != coord[i-1].second) col.push_back(coord[i].second);
    }

    int sz1 = row.size(), sz2 = col.size(), src = 0, target = 1 + sz1 + sz2;
    for (i = 0 ; i < sz1; ++i) {
        addedge(src, i + 1, abs(row[i] - S.first));
        // addedge(target, i + 1, abs(row[i] - F.first));
        if (i > 0) {
            addedge(i + 1, i, row[i] - row[i-1]);
            addedge(i, i + 1, row[i] - row[i-1]);
        }
    }

    for (i = 0 ; i < sz2; ++i) {
        addedge(src, i + sz1 + 1, abs(col[i] - S.second));
        //addedge(target, i + sz1 + 1, abs(col[i] - F.second));
        if (i > 0) {
            addedge(i + sz1 + 1, i + sz1, col[i] - col[i-1]);
            addedge(i + sz1, i + sz1 + 1, col[i] - col[i-1]);
        }
    }

    for (i = 0 ; i < m; ++i) {
        int idx1 = lower_bound(row.begin(), row.end(), coord[i].first) - row.begin() + 1;
        int idx2 = lower_bound(col.begin(), col.end(), coord[i].second) - col.begin() + 1 + sz1;
        addedge(idx1, idx2, 0);
        addedge(idx2, idx1, 0);
        addedge(idx1, target, abs(F.first - coord[i].first) + abs(F.second - coord[i].second));
        addedge(idx2, target, abs(F.first - coord[i].first) + abs(F.second - coord[i].second));
    //    addedge(idx1, src, abs(S.first - coord[i].first) + abs(S.second - coord[i].second));
    //    addedge(idx2, src, abs(S.first - coord[i].first) + abs(S.second - coord[i].second));
    }

    addedge(src, target, abs(S.first - F.first) + abs(S.second - F.second));
    dijkstra(src, target);
    return 0;
}