#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 10000000000000ll;
const int maxn = 5111;

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

vector<int> g[53];
int a[53];
int index(int L, int v) {
	return L * 50 + v;
}

int main() {
	mf.init();
	mf.src = 0, mf.target = maxn - 1;
	int n, m, k, c, d, l, i, j;
	scanf("%d%d%d%d%d", &n, &m, &k, &c, &d);
	for (i = 1; i <= k; ++i) scanf("%d", &a[i]);
	for (i = 1; i <= k; ++i) {
		mf.addedge(mf.src, index(0, a[i]), 1, 0);
	}
	
	for (i = 1; i <= m; ++i) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].push_back(v2);
		g[v2].push_back(v1);
	}
	
	for (i = 0; i <= 100; ++i) {
		for (j = 1; j <= n; ++j) {
			// int cnt = 1;
			for (auto v : g[j]) {
				for (l = 1; l <= k; ++l) {
					mf.addedge(index(i, j), index(i+1, v), 1, d * (2 * l - 1));
					// cnt++;
				}
			}
			// cout << "cnt= " << cnt << endl;
			mf.addedge(index(i, j), index(i+1, j), 50, 0);
		}
	}
	// finish off in i seconds
	for (i = 0; i <= 101; ++i) {
		mf.addedge(index(i, 1), mf.target, 50, c * i);
	}
	
	ll cost = 0;
	mf.mincostMaxflow(cost);
	cout << cost << endl;
	return 0;
}