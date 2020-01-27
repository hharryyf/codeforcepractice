#pragma GCC optimize(3)
#include <bits/stdc++.h>

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

    int mincostMaxflow(ll &cost) {
        ll flow = 0; 
		cost = 0;
        while(SPFA(src, target, flow, cost));
        return flow;
    }
};

MCMF mf;
char st[111];
int n;
int index(char ch) {
    return n + 1 + ch - 'a';
}

int main() {
    mf.init();
    int i, j;
    scanf("%s", st);
    scanf("%d", &n);
    mf.src = 0, mf.target = n + 30;
    int len = strlen(st);
    unordered_map<char, int> h;
    for (i = 0; i < strlen(st); i++) {
        h[st[i]]++;
    }
    
    auto iter = h.begin();
    while (iter != h.end()) {
        mf.addedge(index(iter->first), mf.target, iter->second, 0);
        iter++;
    }
    
    for (i = 1; i <= n; i++) {
        int v;
        scanf("%s%d", st, &v);
        h.clear();
        mf.addedge(mf.src, i, v, 0);
        for (j = 0; j < strlen(st); j++) {
            h[st[j]]++;
        }
        
        iter = h.begin();
        while (iter != h.end()) {
            mf.addedge(i, index(iter->first), iter->second, i);
            iter++;
        }
    }
    
    ll cost = 0;
    ll flow = mf.mincostMaxflow(cost);
    if (flow != len) {
        printf("-1\n");
    } else {
        printf("%lld\n", cost);
    }
    return 0;
}
