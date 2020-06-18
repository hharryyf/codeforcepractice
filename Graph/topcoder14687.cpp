#include <bits/stdc++.h>
#define MAX_SIZE 3111
#define INF 10000000000ll
typedef long long ll;
using namespace std;

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


class DayAndNight{
public:
    // a must occur before b, day cost, night cost, dayToNight cost, nightToDay cost
    int minimalCost(vector<int> a, vector<int> b, vector<int> day, vector<int> night, int dayToNight, int nightToDay){
        ll ret = 2e9 + 7;
        int i, j, k, l;
        int m = a.size(), n = day.size();
        mf.init();
        for (k = 0 ; k < 2; ++k) {
            mf.s = MAX_SIZE - 2, mf.t = MAX_SIZE - 1;
            for (i = 1; i <= n; ++i) {
                mf.init();
                auto id = [&](int x , int y){ // get node id
                    return x * i + y;
                };

                for (j = 0 ; j < n; ++j) {
                    int pre = mf.s;
                    for (l = 0 ; l < i; ++l) {
                        int cost = l & 1 ? day[j] : night[j];
                        mf.addedge(pre, id(j, l), cost);
                        pre = id(j, l);
                    }

                    mf.addedge(pre, mf.t, INF);
                }

                for (j = 0 ; j < m; ++j) {
                    for (l = 0 ; l < i; ++l) {
                        mf.addedge(id(a[j], l), id(b[j], l), INF);
                    }
                }

                ll tmp = mf.Dinic();
                for (j = 0 ; j < i - 1; ++j) {
                    if (j & 1) {
                        tmp += dayToNight;
                    } else {
                        tmp += nightToDay;
                    }
                }

                ret = min(ret, tmp);
            }

            for (i = 0 ; i < n; ++i) swap(day[i], night[i]);
            swap(dayToNight, nightToDay);
        }
        return ret;
    }
};

int main(){
    DayAndNight solver;
    int N , M;
    cin >> N >> M;
    vector<int> a , b , day , night;
    for(int i = 1; i <= M; ++i){
        int x; cin >> x; a.push_back(x);
    }
    for(int i = 1; i <= M; ++i){
        int x; cin >> x; b.push_back(x);
    }
    for(int i = 1; i <= N; ++i){
        int x; cin >> x; day.push_back(x);
    }
    for(int i = 1; i <= N; ++i){
        int x; cin >> x; night.push_back(x);
    }
    int dayToNight , nightToDay; cin >> dayToNight >> nightToDay;
    cout << solver.minimalCost(a , b , day , night , dayToNight , nightToDay) << endl;
    return 0;
}