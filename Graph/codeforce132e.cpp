#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
typedef long long ll;
const ll INF = 100000000000;
const int maxn = 511;
using namespace std;

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

int calc(int num) {
    int ret = 0;
    while (num > 0) {
        if (num & 1) {
            ++ret;
            --num;
        } else {
            num >>= 1;
        }
    }
    return ret;
}

int a[maxn];
int cost[maxn];
map<int, int> pre;
int nxt[maxn];
int ans[maxn];

int main() {
    set<int> st;
    int n, k, i, cnt = 0;
    mf.init();
    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        cost[i] = calc(a[i]);
        ans[i] = -1;
    }

    cnt = 2 * n;
    mf.src = maxn - 2, mf.target = maxn - 1;

    for (i = 1; i <= n; ++i) {
        mf.addedge(mf.src, i, 1, cost[i]);
        mf.addedge(i + n, mf.target, 1, 0);
        mf.addedge(i, i + n, 1, 0);
        if (i < n) mf.addedge(i, i + 1, k - 1, 0);
        auto iter = pre.find(a[i]);
        if (iter != pre.end()) {
            mf.addedge(i - 1, iter->second + n, 1, -cost[i]);
        }
        pre[a[i]] = i;
    }

    ll ret = 0;
    mf.mincostMaxflow(ret);
    for (auto &e : mf.edges) {
        // this implies a merging cost
        if (e.from <= n && e.to > n && e.flow == e.cap && e.cost < 0) {
            --cnt;
            nxt[e.to - n] = e.from + 1;
        }
    }   

    printf("%d %I64d\n", cnt, ret);
    for (i = 0; i < k; ++i) {
        st.insert(i);
    }

    for (i = 1; i <= n; ++i) {
        if (ans[i] == -1) {
            ans[i] = *st.begin();
            st.erase(ans[i]);
            printf("%c=%d\n", 'a' + ans[i], a[i]);
            printf("print(%c)\n", 'a' + ans[i]);
        } else {
            printf("print(%c)\n", 'a' + ans[i]);
        }

        if (!nxt[i]) {
            st.insert(ans[i]);
        } else {
            ans[nxt[i]] = ans[i];
        }
    }
    return 0;
}