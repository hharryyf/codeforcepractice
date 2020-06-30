#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 70011
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
#define INF 10000000000ll
typedef long long ll;
using namespace std;

// at most 32768 + 32768 + 2 = 65538 nodes 
// hence 70011 is enough for size of the node
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

// the graph looks as follows
// LHS of the graph is a range tree of size at most 32768
// RHS is also a range tree of size at most 32768
// S connects to all the leaves of the range tree on the left with capacity 1
// the left range tree's edges connect in a leaf -> root direction with INF capacity
// the right range tree's edges connect in a root -> leaf direction with INF capacity
// if there is a rectangle area (x1, y1, x2, y2) satisfies the condition
// suppose there are log many nodes that covers (x1, y1) on the left range tree
// and log many nodes that covers (x2, y2) on the right range tree
// in total lognlogn many edges might be added to each of the valid rectangle area
// so in totol O(nlognlogn) many edges might be added to the flow graph

Maxflow mf;
int n;
int cnt = 1;

struct flowtree {
    int id[MAX_SIZE >> 1];
    void build(int l, int r, int index) {
        if (l > r) return;
        id[index] = cnt++;
        if (l == r) return;
        build(l, MID, LEFT);
        build(MID + 1, r, RIGHT);
    }   

    void construct(int l, int r, int index, int tp=0) {
        if (l > r) return;
        if (l == r) {
            if (tp == 1) {
                mf.addedge(id[index], mf.t, 1);
            } else {
                mf.addedge(mf.s, id[index], 1);
            }
            return;
        } 

        if (l <= MID) {
            construct(l, MID, LEFT, tp);
            if (tp == 0) {
                mf.addedge(id[LEFT], id[index], INF);
            } else {
                mf.addedge(id[index], id[LEFT], INF);
            }
        }

        if (MID + 1 <= r) {
            construct(MID + 1, r, RIGHT, tp);
            if (tp == 0) {
                mf.addedge(id[RIGHT], id[index], INF);
            } else {
                mf.addedge(id[index], id[RIGHT], INF);
            }
        }
    }

    void cover(int start, int end, int l, int r, int index, vector<int> &ret) {
        if (start > end || l > r || start > r || l > end) return;
        if (start <= l && r <= end) {
            ret.push_back(id[index]);
            return;
        }

        if (end <= MID) {
            cover(start, end, l, MID, LEFT, ret);
        } else if (start >= MID + 1) {
            cover(start, end, MID + 1, r, RIGHT, ret);
        } else {
            cover(start, end, l, MID, LEFT, ret);
            cover(start, end, MID + 1, r, RIGHT, ret);
        }
    }
};

flowtree t1, t2;

void connect(int x1, int x2, int y1, int y2) {
    vector<int> ret1, ret2;
    t1.cover(x1, x2, 1, n, 1, ret1);
    t2.cover(y1, y2, 1, n, 1, ret2);
    for (auto v : ret1) {
        for (auto u : ret2) {
            mf.addedge(v, u, INF);
        }
    }
} 

vector<pair<int, int>> del[MAX_SIZE >> 2];
vector<pair<int, int>> add[MAX_SIZE >> 2];
// st maintains a disjointed set of segments (x1, x2, y)
set<pair<pair<int, int>, int>> st;
struct rectangle {
    int x1, y1, x2, y2;
};
vector<rectangle> rec;
int pos[MAX_SIZE >> 1];

void eliminate(pair<int, int> p, int y) {
    int i;
    vector<int> st;
    for (i = p.first; i <= p.second; ++i) {
        if (!st.empty() && pos[st.back()] != pos[i]) {
            if (pos[st.back()] < y) {
                rec.push_back(rectangle{st.front(), pos[st.back()], st.back(), y - 1});
            }
            st.clear();
        }
        st.push_back(i);
    }

    if (!st.empty()) {
        if (pos[st.back()] < y) {
            rec.push_back(rectangle{st.front(), pos[st.back()], st.back(), y - 1});
        }
        st.clear();
    }

}

int main() {
    int i, q, j;
    mf.s = MAX_SIZE - 2, mf.t = MAX_SIZE - 1;
    scanf("%d%d", &n, &q);
    t1.build(1, n, 1);
    t2.build(1, n, 1);
    t1.construct(1, n, 1);
    t2.construct(1, n, 1, 1);
    // line sweep to extract all the rectangles, note that the total number
    // of extracted rectangle should be O(n), otherwise, we are booking a TLE feedback
    for (i = 1; i <= q; ++i) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        del[y1].emplace_back(x1, x2);
        add[y2].emplace_back(x1, x2);
    }
    

    for (i = 1; i <= n; ++i) pos[i] = 1;
    for (i = 1; i <= n; ++i) {
        for (auto v : del[i]) {
            eliminate(v, i);
        }

        for (auto v : add[i]) {
            for (j = v.first; j <= v.second; ++j) {
                pos[j] = i + 1;
            }
        }
    }   
    
    eliminate(make_pair(1, n), n + 1);

    for (auto r : rec) {
        connect(r.x1, r.x2, r.y1, r.y2);
       // cout << "connect" << r.x1 << " " << r.x2 << " to " << r.y1 << " " << r.y2 << endl;
    }
    printf("%I64d\n", mf.Dinic());
    return 0;
}