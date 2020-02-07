#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 10111
#define INF 200011
typedef long long ll;
using namespace std;

bool valid[MAX_SIZE << 3];
bool visited[MAX_SIZE << 3][3];
int dist[MAX_SIZE << 3][3];
struct point {
	   int x, y;
	   bool lit;
	   bool operator < (point other) const {
	   		return make_pair(x, y) < make_pair(other.x, other.y);
	   }
};

struct state {
	   int dis;
	   int id;
	   int tp;
	   bool operator < (state oth) const {
	   		return dis > oth.dis;
	   }
};

vector<pair<int, int> > pt;
set<point> s;
vector<int> row[MAX_SIZE];
vector<int> col[MAX_SIZE];
vector<int> g[MAX_SIZE << 3];
int n, m, k;
pair<int, int> tmp[MAX_SIZE];

int getindex(int x, int y) {
	return lower_bound(pt.begin(), pt.end(), make_pair(x, y)) - pt.begin();
}

void addpoint(int x, int y) {
	 if (x >= 1 && x <= n && y >= 1 && y <= m 
        && s.find(point{x, y, false}) == s.end())	{
	 	s.insert(point{x, y, false});
	 } 
}

bool adjacent(int s1, int s2) {
    int xd = abs(pt[s1].first - pt[s2].first);
    int yd = abs(pt[s1].second - pt[s2].second);
    return xd + yd <= 1;
}

bool samerow(int s1, int s2) {
    return pt[s1].first == pt[s2].first;
}

bool samecol(int s1, int s2) {
    return pt[s1].second == pt[s2].second;
}

void dijkstra() {
	 int i;
	 priority_queue<state> q;
	 for (i = 0 ; i < k; i++) {
	 	 dist[i][0] = dist[i][1] = dist[i][2] = INF;
	 }
	 
	 dist[0][0] = 0, dist[0][1] = dist[0][2] = 1;
	 q.push(state{0, 0, 0});
	 q.push(state{1, 0, 1});
	 q.push(state{1, 0, 2});
	 while (!q.empty()) {
	 	   state st = q.top();
	 	   q.pop();
	 	   if (visited[st.id][st.tp]) continue;
	 	   visited[st.id][st.tp] = true;
	 	   dist[st.id][st.tp] = st.dis;
	 	   for (auto v : g[st.id]) {
		   	   if (valid[st.id]) {
    		   	   if (st.tp == 0) {
    				  if (adjacent(st.id, v) && valid[v] && !visited[v][0] && dist[v][0] > st.dis) {
    				      dist[v][0] = st.dis;
    				      q.push(state{dist[v][0], v, 0});
    				  }
    				  
    				  if (adjacent(st.id, v) && !valid[v] && !visited[v][1] && dist[v][1] > st.dis + 1) {
					  	 dist[v][1] = st.dis + 1;
					  	 q.push(state{dist[v][1], v, 1});
					  }
    				  
    				  if (adjacent(st.id, v) && !valid[v] && !visited[v][2] && dist[v][2] > st.dis + 1) {
					  	 dist[v][2] = st.dis + 1;
					  	 q.push(state{dist[v][2], v, 2});
					  }
    				  
    				  if (samerow(st.id, v) && !visited[v][1] && dist[v][1] > 1 + st.dis) {
    				      dist[v][1] = st.dis + 1;
    				      q.push(state{dist[v][1], v, 1});
    				  }
    				  
    				  if (samecol(st.id, v) && !visited[v][2] && dist[v][2] > 1 + st.dis) {
    				      dist[v][2] = st.dis + 1;
    				      q.push(state{dist[v][2], v, 2});
    				  }
      			   } else if (st.tp == 1) {
      			      if (adjacent(st.id, v) && valid[v] && !visited[v][0] && dist[v][0] > st.dis) {
    				      dist[v][0] = st.dis;
    				      q.push(state{dist[v][0], v, 0});
    				  }
    				  
    				  if (samerow(st.id, v) && !visited[v][1] && dist[v][1] > st.dis) {
    				      dist[v][1] = st.dis;
    				      q.push(state{dist[v][1], v, 1});
    				  }
    				  
    				  if (samecol(st.id, v) && !visited[v][2] && dist[v][2] > 1 + st.dis) {
    				      dist[v][2] = st.dis + 1;
    				      q.push(state{dist[v][2], v, 2});
    				  }
      			   } else {
      			       if (adjacent(st.id, v) && valid[v] && !visited[v][0] && dist[v][0] > st.dis) {
    				      dist[v][0] = st.dis;
    				      q.push(state{dist[v][0], v, 0});
    				  }
    				  
    				  
    				  if (samerow(st.id, v) && !visited[v][1] && dist[v][1] > st.dis + 1) {
    				      dist[v][1] = st.dis + 1;
    				      q.push(state{dist[v][1], v, 1});
    				  }
    				  
    				  if (samecol(st.id, v) && !visited[v][2] && dist[v][2] > st.dis) {
    				      dist[v][2] = st.dis;
    				      q.push(state{dist[v][2], v, 2});
    				  }
      			   }	
		   	   } else {
		   	       if (st.tp == 1) {
		   	           if (samerow(st.id, v) && !visited[v][1] && dist[v][1] > st.dis) {
    				      dist[v][1] = st.dis;
    				      q.push(state{dist[v][1], v, 1});
    				  }
    				  
    				  if (adjacent(st.id, v) && samecol(st.id, v) && valid[v] 
					      && !visited[v][0] && dist[v][0] > st.dis) {
    				      dist[v][0] = st.dis;
    				      q.push(state{dist[v][0], v, 0});
    				  }
		   	       } else if (st.tp == 2) {
		   	          if (samecol(st.id, v) && !visited[v][2] && dist[v][2] > st.dis) {
    				      dist[v][2] = st.dis;
    				      q.push(state{dist[v][2], v, 2});
    				  }
    				  
    				  if (adjacent(st.id, v) && samerow(st.id, v) && valid[v] 
					      && !visited[v][0] && dist[v][0] > st.dis) {
    				      dist[v][0] = st.dis;
    				      q.push(state{dist[v][0], v, 0});
    				  }
		   	       }
		   	   }
           }
	 }
}

int main(){
	scanf("%d%d%d", &n, &m, &k);
	int i, j;
	for (i = 0 ; i < k; i++) {
		scanf("%d%d", &tmp[i].first, &tmp[i].second);
		s.insert(point{tmp[i].first, tmp[i].second, true});		
	}
	
	int dx[4] = {0, 1, -1, 0}, dy[4] = {-1, 0, 0, 1};
	
	for (i = 0 ; i < k; i++) {
		for (j = 0 ; j < 4; j++) {
			int x = tmp[i].first + dx[j], y = tmp[i].second + dy[j];
			addpoint(x, y);
		}
	}
	
	addpoint(n, m);
	
	i = 0;
	for (auto p : s) {
		pt.emplace_back(p.x, p.y);
		valid[i++] = p.lit;
		row[p.x].push_back(p.y);
		col[p.y].push_back(p.x);
	}
	
	for (i = 1; i <= n; i++) {
		for (j = 0 ; j < (int) row[i].size() - 1; j++) {
			int v1 = getindex(i, row[i][j]), v2 = getindex(i, row[i][j+1]);
			g[v1].push_back(v2);
			g[v2].push_back(v1);
		}
	}
	
	for (i = 1; i <= m; i++) {
		for (j = 0 ; j < (int) col[i].size() - 1; j++) {
			int v1 = getindex(col[i][j], i), v2 = getindex(col[i][j+1], i);
			g[v1].push_back(v2);
			g[v2].push_back(v1);
		}
	}
	
	k = (int) pt.size();
	dijkstra();
	int ans = min(dist[k-1][0], min(dist[k-1][1], dist[k-1][2]));
	if (ans >= INF) ans = -1;
	//for (i = 0 ; i < )
	printf("%d\n", ans);
	return 0;
}

