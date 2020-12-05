#include <bits/stdc++.h>
#define MAX_SIZE 200111
typedef long long ll;
using namespace std;
const ll mod = 998244353;
int N, M;

pair<int, int> edg[MAX_SIZE];
vector<pair<int, ll>> g[MAX_SIZE * 19];
vector<pair<int, pair<int, int>>> g2[MAX_SIZE * 2];
int visited[MAX_SIZE * 19], visited2[MAX_SIZE * 2];
ll dist[MAX_SIZE * 19];
pair<int, int> dist2[MAX_SIZE * 2];

int idx(int v, int vi) {
    return vi * N + v;
}

int main() {
    int i, j;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= M; ++i) scanf("%d%d", &edg[i].first, &edg[i].second);

    for (i = 0; i <= 18; ++i) {
        for (j = 1; j <= M; ++j) {
            if (i % 2 == 0) {
                g[idx(edg[j].first, i)].emplace_back(idx(edg[j].second, i), 1);
            } else {
                g[idx(edg[j].second, i)].emplace_back(idx(edg[j].first, i), 1);
            }
        }
    }

    for (i = 0 ; i <= 17; ++i) {
        for (j = 1; j <= N; ++j) {
            g[idx(j, i)].emplace_back(idx(j, i + 1), 1 << i);
        }
    }

    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
    for (i = 0 ; i < MAX_SIZE * 19; ++i) {
        dist[i] = 1e12;
    }

    dist[1] = 0;
    ll ans = 1e12;
    q.push(make_pair(0, 1));
    while (!q.empty()) {
        auto p = q.top();
        q.pop();
        if (visited[p.second]) continue;
        visited[p.second] = 1;
        dist[p.second] = p.first;
        for (auto np : g[p.second]) {
            if (!visited[np.first] && dist[np.first] > dist[p.second] + np.second) {
                dist[np.first] = dist[p.second] + np.second;
                q.push(make_pair(dist[np.first], np.first));
            }
        }
    }

    for (i = 0 ; i <= 18; ++i) {
        ans = min(ans, dist[idx(N, i)]);
    }

    if (ans < 1e12) {
        cout << (ans % mod) << endl;
        return 0;
    }

    for (i = 0 ; i <= 1; ++i) {
        for (j = 1; j <= M; ++j) {
            if (i % 2 == 0) {
                g2[idx(edg[j].first, i)].push_back(make_pair(idx(edg[j].second, i), make_pair(0, 1)));
            } else {
                g2[idx(edg[j].second, i)].push_back(make_pair(idx(edg[j].first, i), make_pair(0, 1)));
            }
        }
    }

    for (j = 1; j <= N; ++j) {
        g2[idx(j, 0)].push_back(make_pair(idx(j, 1), make_pair(1, 0)));
        g2[idx(j, 1)].push_back(make_pair(idx(j, 0), make_pair(1, 0)));

    }

    priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, greater<pair<pair<int, int>, int>>> q2;
    for (j = 1; j <= 2 * N; ++j) {
        dist2[j].first = dist2[j].second = 1e8;
    }

    q2.push(make_pair(make_pair(0, 0), 1));
    while (!q2.empty()) {
        auto p = q2.top();
        q2.pop();
        if (visited2[p.second]) continue;
        visited2[p.second] = 1;
        dist2[p.second] = p.first;
        for (auto np : g2[p.second]) {
            if (!visited2[np.first]) {
                auto p1 = dist2[np.first], p2 = make_pair(dist2[p.second].first + np.second.first, dist2[p.second].second + np.second.second);
                if (p1 > p2) {
                    dist2[np.first].first = dist2[p.second].first + np.second.first;
                    dist2[np.first].second = dist2[p.second].second + np.second.second;
                }
                q2.push(make_pair(dist2[np.first], np.first));
            }
        }
    }

    dist2[N] = min(dist2[N], dist2[2 * N]);
    // (2 ^ dist2.first) - 1 + dist2.second
    int ret = 1;
    for (i = 1; i <= dist2[N].first; ++i) {
        ret = ret * 2;
        ret %= mod;
    }

    ret--;
    ret += dist2[N].second;
    ret %= mod;
    if (ret < 0) ret += mod;
    printf("%d\n", ret);
    return 0;
}