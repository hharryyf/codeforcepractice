#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 10000000000;
const int maxn = 159;

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
int a[maxn], b[maxn];
int ans[maxn];

int main() {
    int i, T, j;
    scanf("%d", &T);
    while (T > 0) {
        int n, k;
        mf.init();
        mf.src = 0, mf.target = maxn - 1;
        // node 0 is the source
        // 1-n are the n candidates
        // n+1 to n + k are the remaining nodes
        // n+k+1 is the node for +1s
        // T is the target
        scanf("%d%d", &n, &k);
        for (i = n + 1; i <= n + k; ++i) {
            mf.addedge(i, mf.target, 1, 0);
        }

        mf.addedge(n + k + 1, mf.target, n - k, 0);

        for (i = 1; i <= n; ++i) {
            scanf("%d%d", &a[i], &b[i]);
            mf.addedge(mf.src, i, 1, 0);
            for (j = 1; j <= k; ++j) {
                mf.addedge(i, n + j, 1, -a[i] - (j-1) * b[i]);
            }    
            mf.addedge(i, n + k + 1, 1, -(k-1) * b[i]);
        }

        ll cost = 0;
        mf.mincostMaxflow(cost);
        printf("%d\n", k + 2 * (n-k));
        vector<int> discard;
        for (auto &e : mf.edges) {
            if (e.from >= 1 && e.from <= n && e.flow == e.cap && e.to >= n + 1 && e.to <= n + k) {
                ans[e.to - n] = e.from;
            } else if (e.from >= 1 && e.from <= n && e.flow == e.cap && e.to == n + k + 1) {
                discard.push_back(e.from);
            }
        }

        for (i = 1; i <= k-1; ++i) {
            printf("%d ", ans[i]);
        }

        for (auto v : discard) {
            printf("%d %d ", v, -v);
        }
        printf("%d\n", ans[k]);
        --T;
    }
    return 0;
}