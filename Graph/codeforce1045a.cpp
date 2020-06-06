#include <bits/stdc++.h>
#define MAX_SIZE 22011
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index << 1 | 1)
#define INF 10000000000ll
typedef long long ll;
using namespace std;

// at most 5000 weapons and 5000 spaceship as a range tree
// the total node is at most 131072 + 5000 + 2
// hence 22000 is enough for size of the node
// invariant:
// weapon from n+1 to n+m, spaceship from 1-m, external nodes start from m+n+1

struct weapon {
    int tp, l, r, a, b, c, k;
};

weapon wp[MAX_SIZE];

struct Maxflow {
    struct edge {
    	int from, to;
    	ll flow, capacity;
    };
    
    // start and end point
    int s, t;
    
    // list array
    vector<edge> edg;
    
    // g reference to the ith vertex's edges
    vector<int> g[MAX_SIZE];
    
    // distance array and visited array
    int dist[MAX_SIZE], visited[MAX_SIZE];
    int cur[MAX_SIZE];
    
    void init() {
    	edg.clear();
    	int i;
    	for (i = 0 ; i < MAX_SIZE; i++) {
    		g[i].clear();
    	}
    }
    
    void addedge(int from, int to, ll capacity) {
    	edge e1 = edge{from, to, 0ll, capacity};
		// cout << "addedge " << from << " " << to << " " << capacity << endl;
    	edge e2 = edge{to, from, 0ll, 0ll};
    	edg.push_back(e1), edg.push_back(e2);
    	g[from].push_back((int) edg.size() - 2);
    	g[to].push_back((int) edg.size() - 1);
    }
    
    // construct the level graph
    bool bfs() {
    	memset(visited,0,sizeof(visited));
    	memset(dist,0,sizeof(dist));
    	queue<int> q;
    	q.push(s);
    	visited[s] = 1;
    	dist[s] = 0;
    	while (!q.empty()) {
    		int v = q.front();
    		q.pop();
    		for (int i = 0 ; i < (int) g[v].size(); i++) {
    			edge &e = edg[g[v][i]];
    			int nxt = e.to;
    			if (!visited[nxt] && e.capacity > e.flow) {
    				dist[nxt] = dist[v] + 1;
    				q.push(nxt);
    				visited[nxt] = 1;
    			}  
    		}
    	}
    	
    	return visited[t];
    }
    
    ll dfs(int x, ll cp) {
    	if (x == t || cp == 0) {
    		return cp;
    	}
    	
    	ll flow = 0, newflow;
    	for (int &y = cur[x]; y < (int) g[x].size(); y++) {
    		edge &e = edg[g[x][y]];
    		if (dist[x] + 1 == dist[e.to]) {
    			ll minn = min(cp, e.capacity - e.flow);
    			newflow = dfs(e.to, minn);
    			if (newflow > 0) {
    				e.flow += newflow;
    				edg[g[x][y] ^1].flow -= newflow;
    				flow += newflow;
    				cp -= newflow;
    				
    				if (cp == 0) {
    					break;
    				}
    			}
    		}
    	}
    	
    	return flow;
    }
    
    ll Dinic(){
        ll flow=0;
        while(bfs()){
            memset(cur,0,sizeof(cur));
            flow += dfs(s,INF);
        }
        return flow;
    }
};

Maxflow mf;
int wid[MAX_SIZE * 10];
int cnt = 0;
int n, m;
int mt[MAX_SIZE];


void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        wid[index] = l;
        return;
    }

    wid[index] = ++cnt;
    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    mf.addedge(wid[index], wid[LEFT], INF);
    mf.addedge(wid[index], wid[RIGHT], INF);
}
// add an edge from v to [start, end]
void update(int start, int end, int l, int r, int index, int v) {
    if (start > end || l > r || start > r || l > end) return;
    if (start <= l && r <= end) {
        mf.addedge(v, wid[index], 1);
        return;
    }

    if (end <= MID) {
        update(start, end, l, MID, LEFT, v);
    } else if (start >= MID + 1) {
        update(start, end, MID + 1, r, RIGHT, v);
    } else {
        update(start, end, l, MID, LEFT, v);
        update(start, end, MID + 1, r, RIGHT, v);
    }
}

// an important trick here, note that the complexity of the
// algorithm is O(nmlogn), so that we can definitly afford another
// O(mn)
void find(int v, int id, int pre) {
    if (mt[id] != 0) return;
    if (v > m && v <= n + m) {
        mt[id] = v - m;
        return;
    }

    int i;
    for (i = 0 ; i < (int) mf.g[v].size(); ++i) {
        auto e = mf.edg[mf.g[v][i]];
        if (e.flow < 0 && e.to != pre) {
            
            find(e.to, id, v);
            mf.edg[mf.g[v][i]].flow++;
            return;
        }
    }
}

int tol[MAX_SIZE];

int main() {
    int i, j;
    scanf("%d%d", &n, &m);
    cnt = n + m;
    mf.s = 0, mf.t = MAX_SIZE - 1;
    build(1, m, 1);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &wp[i].tp);
        if (wp[i].tp == 0) {
            mf.addedge(mf.s, i + m, 1);
            scanf("%d", &wp[i].k);
            for (j = 0 ; j < wp[i].k; ++j) {
                int v;
                scanf("%d", &v);
                mf.addedge(i + m, v, 1);
            }
        } else if (wp[i].tp == 1) {
            mf.addedge(mf.s, i + m, 1);
            scanf("%d%d", &wp[i].l, &wp[i].r);
            update(wp[i].l, wp[i].r, 1, m, 1, i + m);
        } else {
            mf.addedge(mf.s, i + m, 2);
            scanf("%d%d%d", &wp[i].a, &wp[i].b, &wp[i].c);
            mf.addedge(i + m, wp[i].a, 1);
            mf.addedge(i + m, wp[i].b, 1);
            mf.addedge(i + m, wp[i].c, 1);
        }
    }

    for (i = 1; i <= m; ++i) {
        mf.addedge(i, mf.t, 1);
    }

    printf("%I64d\n", mf.Dinic());

    for (i = 0; i < (int) mf.g[mf.t].size(); ++i) {
        // means this residual edge is used
        auto &e = mf.edg[mf.g[mf.t][i]];
        if (e.flow < e.capacity) {
            find(e.to, e.to, mf.t);
        }
    }

    for (i = 1; i <= m; ++i) {
        if (mt[i]) {
            tol[mt[i]]++;
        }
    }

    for (i = 1; i <= n; ++i) {
        if (wp[i].tp == 2 && tol[i] == 1) {
            if (mt[wp[i].a] != i) {
                mt[wp[i].a] = i;
            } else {
                mt[wp[i].b] = i;
            }
        }
    }

    for (i = 1; i <= m; ++i) {
        if (mt[i]) {
            printf("%d %d\n", mt[i], i);
        }
    }
    return 0;
}