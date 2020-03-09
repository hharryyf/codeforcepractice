#pragma GCC optimize(3)
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll INF = 10000000000;
const int maxn = 2021;

struct Edge {
    int from, to;
	ll cap, flow, cost;
	int id;
    Edge(int u, int v, ll c, ll f, ll w, int id):from(u),to(v),cap(c),flow(f),cost(w), id(id)
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

    void addedge(int from, int to, ll cap, ll cost, int id) {
        edges.push_back(Edge(from, to, cap, 0, cost, id)); 
        edges.push_back(Edge(to, from, 0, 0, -cost, 0)); 
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
int s[maxn], t[maxn], c[maxn];
int tmp[maxn];
int n, k;
int ans[maxn];

int main() {
	int i;
	mf.init();
	scanf("%d%d", &n, &k);
	for (i = 1; i <= n; i++) {
		scanf("%d%d%d", &s[i], &t[i], &c[i]);
		tmp[i] = s[i];
		tmp[i + n] = t[i] + s[i];
	}
	
	sort(tmp + 1, tmp + 1 + 2 * n);
	
	for (i = 1; i <= 2 * n; i++) {
		if (i == 1 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
	}
	
	int m = (int) disc.size();
	
	mf.src = 0, mf.target = m + 1;
	
	for (i = 0; i <= m; i++) {
		mf.addedge(i, i + 1, k, 0, 0);
	}
	
	for (i = 1; i <= n; i++) {
		int idx1 = lower_bound(disc.begin(), disc.end(), s[i]) - disc.begin() + 1;
		int idx2 = lower_bound(disc.begin(), disc.end(), t[i] + s[i]) - disc.begin() + 1;
		mf.addedge(idx1, idx2, 1, -c[i], i);
	}
	ll cost = 0;
	mf.mincostMaxflow(cost);
	for (auto e : mf.edges) {
		if (e.id && e.cap == e.flow) {
		   ans[e.id] = 1;
		}
	}
	
	for (i = 1; i <= n; i++) {
		printf("%d ", ans[i]);
	}
	printf("\n");
	return 0;
}
