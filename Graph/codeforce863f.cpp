#include <bits/stdc++.h>
#define maxn 152
using namespace std;

typedef long long ll;
const ll INF = 10000000000;

list<int> g[maxn];

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


int main() {
    int n, q;
    mf.init();
    scanf("%d%d", &n, &q);
    mf.src = 0, mf.target = 2 * n + 1;
    int i, j, k;
    for (i = 1; i <= n; i++) {
        mf.addedge(mf.src, i, 1, 0);
        for (j = 0; j < n; j++) {
            g[i].push_back(j + 1);
            mf.addedge(i + n, mf.target, 1, 2 * j + 1);
        }
    }
    for (i = 0 ; i < q; i++) {
        int tp, l, r, v;
        scanf("%d%d%d%d", &tp, &l, &r, &v);
        if (tp == 1) {
            for (j = l; j <= r; j++) {
                while (!g[j].empty() && g[j].front() < v) {
                   g[j].pop_front();
                }
            }
        } else {
            for (j = l; j <= r; j++) {
               while (!g[j].empty() && g[j].back() > v) {
                  g[j].pop_back();
               }
            }
        }
    }
    
    for (i = 1; i <= n; i++) {
        for (auto v : g[i]) {
            mf.addedge(i, v + n, 1, 0);
        }
    }
    
    ll cost = 0;
    if(mf.mincostMaxflow(cost) != n) {
        printf("-1\n");
        return 0;
    }
    printf("%lld\n", cost);
    return 0;
}
