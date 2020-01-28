#pragma GCC optimize(3)
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll INF = 1000000000;
const double inf = 10000000.0;
const int maxn = 821;

struct Edge {
    int from, to;
	ll cap, flow;
	double cost;
    Edge(int u, int v, ll c, ll f, double w):from(u),to(v),cap(c),flow(f),cost(w)
    {}
};

struct MCMF {
    int n, m;
    int src, target;
    vector<Edge> edges; 
    vector<int> G[maxn]; 
    int inq[maxn]; 
    double d[maxn]; 
    int p[maxn]; 
    ll a[maxn]; 

    MCMF() {}

    void init(int n=maxn) {
        this->n = n;
        for(int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }

    void addedge(int from, int to, ll cap, double cost) {
        edges.push_back(Edge(from, to, cap, 0, cost)); 
        edges.push_back(Edge(to, from, 0, 0, -cost)); 
        m = edges.size();
        G[from].push_back(m-2); 
        G[to].push_back(m-1);
    }

    bool SPFA(int s, int t, ll &flow, double &cost) {
        for(int i = 0; i < n; i++) d[i] = inf;
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
        if(d[t] == inf) return false; 
        flow += a[t]; 
        cost += d[t] * a[t]; 
        for(int u = t; u != s; u = edges[p[u]].from) {
        		edges[p[u]].flow += a[t]; 
        		edges[p[u]^1].flow -= a[t];
		}
        return true;
    }

    ll mincostMaxflow(double &cost) {
        ll flow = 0; 
		cost = 0;
        while(SPFA(src, target, flow, cost));
        return flow;
    }
};

MCMF mf;

int n;
pair<int, int> coord[maxn];


double dist(int v1, int v2) {
	   return sqrt((coord[v1].first - coord[v2].first) * (coord[v1].first - coord[v2].first)
	   + (coord[v1].second - coord[v2].second) * (coord[v1].second - coord[v2].second));
}
int main() {
	int i, j;
	scanf("%d", &n);
	mf.init();
	mf.src = 0, mf.target = 2 * n + 2;
	for (i = 1; i <= n; i++) {
		scanf("%d%d", &coord[i].first, &coord[i].second);
	}
	
	for (i = 1; i <= n; i++) {
		mf.addedge(mf.src, i, 2, 0.0);
		mf.addedge(i + n, mf.target, 1, 0.0);
		for (j = 1; j <= n; j++) {
			if (coord[i].second > coord[j].second) {
			   mf.addedge(i, j + n, 1, dist(i, j));
			}
		}
	}
	
	double cost = 0.0;
	ll flow = mf.mincostMaxflow(cost);
	if (flow != n-1) {
	   printf("-1\n");
	} else {
	   printf("%.15lf\n", cost);
	}
	return 0;
}
