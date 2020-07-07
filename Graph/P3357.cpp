#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1000000000000000;
const int maxn = 1022;

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
vector<int> disc;
int tmp[maxn];
ll cst[maxn];
int x1[maxn], x2[maxn];
int n;

ll sqr(ll x) {
    return x * x;
}

int main() {
    int i, k;
    mf.init();
    mf.src = maxn - 2, mf.target = maxn - 1;
    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; ++i) {
        int y1, y2;
        scanf("%d%d%d%d", &x1[i], &y1, &x2[i], &y2);
        if (x1[i] > x2[i]) swap(x1[i], x2[i]);
        cst[i] = sqrt(sqr(x2[i] - x1[i]) + sqr(y2 - y1));
        x1[i] <<= 1;
        x2[i] <<= 1;
        if (x1[i] == x2[i]) {
            x2[i]++;
        } else {
            x1[i]++;
        }
        tmp[(i << 1) - 1] = x1[i];
        tmp[i << 1] = x2[i];
    }

    sort(tmp + 1, tmp + 1 + 2 * n);
    for (i = 1; i <= 2 * n; ++i) {
        if (i == 1 || tmp[i] != tmp[i-1]) {
            disc.push_back(tmp[i]);
        }
    }

    int sz = disc.size();
    mf.addedge(mf.src, 0, k, 0);
    for (i = 0; i < sz - 1; ++i) {
        mf.addedge(i, i + 1, k, 0);
    }

    mf.addedge(sz - 1, mf.target, k, 0);

    for (i = 1; i <= n; ++i) {
        int it1 = lower_bound(disc.begin(), disc.end(), x1[i]) - disc.begin();
        int it2 = lower_bound(disc.begin(), disc.end(), x2[i]) - disc.begin();
        // if (it1 > it2) swap(it1, it2);
        mf.addedge(it1, it2, 1, -cst[i]);
    }

    ll cost = 0;
    mf.mincostMaxflow(cost);
    cout << -cost << endl;
    return 0;
}