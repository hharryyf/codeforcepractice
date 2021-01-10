#include <bits/stdc++.h>
#define MAX_SIZE 262192
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;
const int inf = 700000000;
vector<pair<int, int>> g[MAX_SIZE];
int tree[MAX_SIZE];
int dist[3][MAX_SIZE];
int tmp[MAX_SIZE];
int visited[MAX_SIZE];
vector<int> disc;
int N, M;


struct tup {
    int d1, d2, d3;
    bool operator < (tup other) const {
        if (d1 != other.d1) return d1 < other.d1;
        if (d2 != other.d2) return d2 < other.d2;
        return d3 < other.d3;
    }
};

tup tp[MAX_SIZE];
int useless[MAX_SIZE];

void update(int pt, int l, int r, int index, int val) {
    if (pt < l || l > r || pt > r) return;
    if (l == r) {
        tree[index] = min(tree[index], val);
        return;
    }

    if (pt <= MID) {
        update(pt, l, MID, LEFT, val);
    } else {
        update(pt, MID + 1, r, RIGHT, val);
    }
    tree[index] = min(tree[LEFT], tree[RIGHT]);
}

int query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return inf;
    if (start <= l && r <= end) return tree[index];
    if (end <= MID) return query(start, end, l, MID, LEFT);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
    return min(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}

void dijkstra(int src) {
    int i;
    memset(visited, 0, sizeof(visited));
    for (i = 0 ; i < N; ++i) {
        dist[src][i] = inf;
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    dist[src][src] = 0;
    q.push(make_pair(0, src));
    while (!q.empty()) {
        auto p = q.top();
        q.pop();
        if (visited[p.second]) continue;
        visited[p.second] = 1;
        dist[src][p.second] = p.first;
        for (auto ne : g[p.second]) {
            int nv = ne.first, w = ne.second;
            if (!visited[nv] && dist[src][nv] > dist[src][p.second] + w) {
                dist[src][nv] = dist[src][p.second] + w;
                q.push(make_pair(dist[src][nv], nv));
            }
        }
    }
}

int main() {
    int i;
    scanf("%d%d", &N, &M);
    for (i = 0 ; i < M; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    for (i = 0 ; i < 3; ++i) {
        dijkstra(i);
    }   

    for (i = 0 ; i < N; ++i) {
        tmp[i] = dist[1][i];
        tp[i].d1 = dist[0][i], tp[i].d2 = dist[1][i], tp[i].d3 = dist[2][i];
    }

    sort(tp, tp + N);
    sort(tmp, tmp + N);
    for (i = 0 ; i < N; ++i) {
        if (i == 0 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
    }
    map<int, vector<int>> mp;
    for (i = 0 ; i < N; ++i) {
        mp[tp[i].d1].push_back(i);
    }

    int sz = disc.size(), ans = N;
    for (i = 0 ; i < MAX_SIZE; ++i) tree[i] = inf;
    for (auto iter : mp) {
        for (auto v : iter.second) {
            int idx = lower_bound(disc.begin(), disc.end(), tp[v].d2) - disc.begin();
            // first less, second, third not greater than
            if (query(0, idx, 0, sz - 1, 1) <= tp[v].d3) {
                useless[v] = 1;
            }
        }

        for (auto v : iter.second) {
            int idx = lower_bound(disc.begin(), disc.end(), tp[v].d2) - disc.begin();
            update(idx, 0, sz - 1, 1, tp[v].d3);
        }

        for (auto v : iter.second) {
            int idx = lower_bound(disc.begin(), disc.end(), tp[v].d2) - disc.begin();
            if (query(0, idx, 0, sz - 1, 1) < tp[v].d3) {
                useless[v] = 1;
            } else if (query(0, idx - 1, 0, sz - 1, 1) <= tp[v].d3) {
                useless[v] = 1;
            }
        }
    }

    for (i = 0 ; i < N; ++i) ans -= useless[i];
    printf("%d\n", ans);
    return 0;
}