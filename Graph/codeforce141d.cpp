#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 500111
#define INF 10000000000000000ll
typedef long long ll;
using namespace std;

struct edge {
    // ramp id, 0 means directly walk
    int id;  
    int to;
    ll ti;
};

ll dist[MAX_SIZE];
// the previous vertex i
int pre[MAX_SIZE];
// the rid that takes the person to the current vertex i
int rid[MAX_SIZE];
vector<edge> g[MAX_SIZE];

vector<int> disc;
struct rmp {
    int x;
    int id;
    int d;
    int t;
    int p;
};

rmp a[MAX_SIZE];
int tmp[MAX_SIZE];
bool visited[MAX_SIZE];

void Dijkstra() {
    int n = disc.size();
    int i;
    for (i = 0 ; i < n; i++) {
        dist[i] = INF;
        pre[i] = -1;
    }
    
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
    q.push(make_pair(0, 0));
    while (!q.empty()) {
        auto p = q.top();
        q.pop();
        if (visited[p.second]) continue;
        visited[p.second] = true;
        dist[p.second] = p.first;
        for (auto e : g[p.second]) {
            if (!visited[e.to] && dist[e.to] > dist[p.second] + e.ti) {
                dist[e.to] = dist[p.second] + e.ti;
                pre[e.to] = p.second;
                rid[e.to] = e.id;
                q.push(make_pair(dist[e.to], e.to));
            }
        }
    }
    
    printf("%lld\n", dist[n-1]);
    int curr = n - 1;
    stack<int> ret;
    while (curr != -1) {
        if (rid[curr]) {
            ret.push(rid[curr]);
        }
        curr = pre[curr];
    }
    printf("%d\n", ret.size());
    if (!ret.empty()) {
        while (!ret.empty()) {
            printf("%d ", ret.top());
            ret.pop();
        }
        printf("\n");
    }
}

void build(int n) {
    int i, m = disc.size();
    for (i = 0 ; i < m - 1; i++) {
        g[i].push_back(edge{0, i+1, disc[i+1] - disc[i]});
        g[i+1].push_back(edge{0, i, disc[i+1] - disc[i]});
    }
    
    for (i = 0 ; i < n; i++) {
        if (a[i].x >= a[i].p) {
            int index1 = lower_bound(disc.begin(), disc.end(), a[i].x - a[i].p) - disc.begin();
            int index2 = lower_bound(disc.begin(), disc.end(), a[i].x + a[i].d) - disc.begin();
            g[index1].push_back(edge{a[i].id, index2, 1ll * (a[i].t + a[i].p)});
        }
    }
}

int main() {
    int n, L, i, k = 0;
    scanf("%d%lld", &n, &L);
    for (i = 0 ; i < n; i++) {
        scanf("%d%d%d%d", &a[i].x, &a[i].d, &a[i].t, &a[i].p);
        a[i].id = i + 1;
        tmp[k++] = a[i].x;
        tmp[k++] = a[i].x + a[i].d;
        if (a[i].x >= a[i].p) {
            tmp[k++] = a[i].x - a[i].p;
        }
    }
    
    tmp[k++] = 0, tmp[k++] = L;
    sort(tmp, tmp + k);
    for (i = 0 ; i < k; i++) {
        if (i == 0 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
    }
    
    build(n);
    Dijkstra();
    return 0;
}
