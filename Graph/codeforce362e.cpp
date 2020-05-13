#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 10000000000;
const int maxn = 111;

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
    ll K;
    MCMF() {}

    void init(int n=maxn, ll K=INF) {
        this->n = n;
        for(int i = 0; i < n; i++) G[i].clear();
        edges.clear();
        this->K = K;
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
        // note that everytime MCMF would find the cheapest path
        // for a unit flow
        if (cost + d[t] * a[t] > K) {
            flow += (K - cost) / d[t];
            cost += (K - cost) / d[t] * d[t];
            return false;
        }
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

int main() {
    int i, n, j;
    ll K;
    scanf("%d%I64d", &n, &K);
    mf.init(maxn, K);
    mf.src = 1, mf.target = n;
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) {
            ll tmp;
            scanf("%I64d", &tmp);
            if (tmp > 0) {
                mf.addedge(i, j, tmp, 0);
                mf.addedge(i, j, K, 1);
            }
        }
    }

    ll cost = 0;
    ll flow = mf.mincostMaxflow(cost);
    printf("%I64d\n", flow);
    return 0;
}