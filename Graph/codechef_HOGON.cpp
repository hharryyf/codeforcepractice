#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 3011
using namespace std;
typedef long long ll;
const ll INF = 10000000000;
const int maxn = 211;

struct Edge {
    int from, to;
	ll cap, flow, cost;
    Edge(int u, int v, ll c, ll f, ll w):from(u),to(v),cap(c),flow(f),cost(w)
    {}
};

struct MCMF {
    int n, m;
    int src, target;
    vector<Edge> edges; 
    vector<int> G[maxn]; 
    int inq[maxn]; 
    ll d[maxn]; 
    int p[maxn]; 
    ll a[maxn]; 

    MCMF() {}

    void init(int n=maxn) {
        this->n = n;
        for(int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }

    void addedge(int from, int to, ll cap, ll cost) {
        edges.push_back(Edge(from, to, cap, 0, cost)); 
        edges.push_back(Edge(to, from, 0, 0, -cost)); 
        m = edges.size();
        G[from].push_back(m-2); 
        G[to].push_back(m-1);
    }

    bool SPFA(int s, int t, ll &flow, ll &cost) {
        for(int i = 0; i < n; i++) d[i] = INF;
        memset(inq, 0, sizeof(inq));
        d[s] = 0; inq[s] = 1; p[s] = 0; a[s] = INF;

        queue<int> Q;
        Q.push(s);
        while(!Q.empty()) {
            int u = Q.front(); Q.pop();
            inq[u] = 0;
            for(int i = 0; i < (int) G[u].size(); i++) {
                Edge& e = edges[G[u][i]];
                if(e.cap > e.flow && d[e.to] > d[u] + e.cost) {
                    d[e.to] = d[u] + e.cost;
                    p[e.to] = G[u][i];
                    a[e.to] = min(a[u], e.cap - e.flow);
                    if(!inq[e.to]) { Q.push(e.to); inq[e.to] = 1; }
                }
            }
        }
        if(d[t] == INF) return false; 
        flow += a[t]; 
        cost += d[t] * a[t]; 
        for(int u = t; u != s; u = edges[p[u]].from) {
        		edges[p[u]].flow += a[t]; 
        		edges[p[u]^1].flow -= a[t];
		}
        return true;
    }

    ll mincostMaxflow(ll &cost) {
        ll flow = 0; 
		cost = 0;
        while(SPFA(src, target, flow, cost));
        return flow;
    }
};

MCMF mf;
int a[MAX_SIZE][MAX_SIZE];
int N, K;

int idx(int x, int y) {
    return (x - 1) * N + y - 1;
}

int main() {
    int i, j;
    ll sm = 0;
    scanf("%d%d", &N, &K);
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            scanf("%d", &a[i][j]);
            sm += a[i][j];
        }
    }
    mf.init();
    mf.src = maxn - 1, mf.target = maxn - 2;
    int S = maxn - 3, T = maxn - 4;
    mf.addedge(mf.src, S, K, 0);
    mf.addedge(T, mf.target, K, 0);
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> q;
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            if (j + 1 <= N) {
                q.push(make_pair(a[i][j] + a[i][j+1], make_pair(idx(i, j), idx(i, j + 1))));
            }

            if (i + 1 <= N) {
                q.push(make_pair(a[i][j] + a[i+1][j], make_pair(idx(i, j), idx(i + 1, j))));
            }

            while ((int) q.size() > 100) {
                q.pop();
            }
        }
    }

    vector<pair<int, pair<int, int>>> ret;
    vector<int> tmp, disc;
    while (!q.empty()) {
        ret.push_back(q.top());
        tmp.push_back(q.top().second.first);
        tmp.push_back(q.top().second.second);
        q.pop();
    }

    sort(tmp.begin(), tmp.end());
    for (i = 0 ; i < (int) tmp.size(); ++i) {
        if (i == 0 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
    }

    for (i = 0 ; i < (int) disc.size(); ++i) {
        int row = disc[i] / N, col = disc[i] % N;
        if ((row + col) % 2 == 0) {
            mf.addedge(S, i, 1, 0);
        } else {
            mf.addedge(i, T, 1, 0);
        }
    }

    for (auto p : ret) {
        int u = p.second.first, v = p.second.second;
        int row = u / N, col = u % N;
        int idx1 = lower_bound(disc.begin(), disc.end(), u) - disc.begin();
        int idx2 = lower_bound(disc.begin(), disc.end(), v) - disc.begin();
        if ((row + col) % 2 == 0) {
            mf.addedge(idx1, idx2, 1, -p.first);
        } else {
            mf.addedge(idx2, idx1, 1, -p.first);
        }
    }

    ll cost = 0;
    mf.mincostMaxflow(cost);
    cout << sm + cost << endl;
    return 0;
}