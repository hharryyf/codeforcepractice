#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
typedef int ll;
const int INF = 100000000;
const int maxn = 6511;

struct Edge {
    int from, to;
	ll cap, flow, cost;
    Edge(int u, int v, ll c, ll f, ll w):from(u),to(v),cap(c),flow(f),cost(w)
    {}
};

struct MCMF {
    int n;
    int src, target;
    vector<Edge> edges; 
    vector<int> G[maxn]; 
    ll dis[maxn], H[maxn];
    int p[maxn]; 
    ll a[maxn];
    ll K=INF;
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
        int m = edges.size();
        G[from].push_back(m-2); 
        G[to].push_back(m-1);
    }

    bool Dijkstra(int s, int t, ll &flow, ll &cost) {
        priority_queue <pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>> > q;
        for(int i = 0; i < n; i++) dis[i] = INF;
		dis[s] = 0; 
        a[s] = INF;
        p[s] = 0;
        q.push(pair<int, int>(0, s));
		while (!q.empty()) {
			auto now = q.top(); 
            q.pop();
			int v = now.second;
			if (dis[v] < now.first) continue;
			for (int i = 0; i < (int) G[v].size(); ++i) {
				Edge& e = edges[G[v][i]];
				if (e.cap > e.flow && dis[e.to] > dis[v] + e.cost + H[v] - H[e.to]) {
					dis[e.to] = dis[v] + e.cost + H[v] - H[e.to];
					p[e.to] = G[v][i];
                    a[e.to] = min(a[v], e.cap - e.flow);
					q.push(make_pair(dis[e.to], e.to));
				}
			}
		}
		
        if (dis[t] == INF) return false;
		for (int i = 0; i < n; ++i) H[i] += dis[i];
       
        flow += a[t]; 
        cost += H[t] * a[t]; 
        for(int u = t; u != s; u = edges[p[u]].from) {
        		edges[p[u]].flow += a[t]; 
        		edges[p[u]^1].flow -= a[t];
		}
        return true;
    }

    ll mincostMaxflow(ll& cost) {
		ll flow = 0;
        cost = 0; 
		for(int i = 0; i < n; i++) H[i] = 0;
        while (Dijkstra(src, target, flow, cost)) {}
		return flow;
	}
};

MCMF mf;

int n, m;
int mt[82][82];
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int index(int x, int y) {
    return (x - 1) * m + y;
}

int main() {
    int i, j, k;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= m; ++j) {
            scanf("%d", &mt[i][j]);
        }
    }

    mf.init();
    mf.src = 0, mf.target = maxn - 1;

    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= m; ++j) {
            if ((i + j) & 1) {
                mf.addedge(mf.src, index(i, j), 1, 0);
                for (k = 0 ; k < 4; ++k) {
                    int tx = i + dx[k], ty = j + dy[k];
                    if (tx >= 1 && tx <= n && ty >= 1 && ty <= m) {
                        mf.addedge(index(i, j), index(tx, ty), 1, mt[i][j] != mt[tx][ty]);
                    }
                }
            } else {
                mf.addedge(index(i, j), mf.target, 1, 0);
            }
        }
    }

    ll cost = 0;
    mf.mincostMaxflow(cost);
    printf("%d\n", cost);
    return 0;
}