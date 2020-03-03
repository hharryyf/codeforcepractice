#include <bits/stdc++.h>
#define INF 900011
typedef long long ll;
using namespace std;

bool visited[11][11][3];
int a[11][11];
pair<int, int> rev[111];
pair<int, int> dist[11][11][3][11][11][3];
pair<int, int> dist2[11][11][3];

struct state {
	   int x, y, z;
	   pair<int, int> dis;
	   bool operator < (state other) const {
	   		return dis > other.dis;
	   }
};

struct edge {
	   int x, y, z;
	   pair<int, int> cost;
};

vector<edge> g[11][11][3]; 
int n;

bool rook(int x1, int y1, int x2, int y2) {
	return (x1 == x2) || (y1 == y2);
}

bool bishop(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) == abs(y1 - y2);
}

bool knight(int x1, int y1, int x2, int y2) {
    return (abs(x1-x2) + abs(y1-y2) == 3) && (abs(x1-x2) * abs(y1-y2) == 2);
}

pair<int, int> add(pair<int, int> &p1, pair<int, int> &p2) {
	return make_pair(p1.first + p2.first, p1.second + p2.second);
}



int main() {
	scanf("%d", &n);
	int i1, j1, k1, i2, j2, k2;
	for (i1 = 1; i1 <= n; i1++) {
		for (j1 = 1; j1 <= n; j1++) {
			scanf("%d", &a[i1][j1]);
			rev[a[i1][j1]] = {i1, j1};
		}
	}
	
	for (i1 = 1; i1 <= n; i1++) {
		for (j1 = 1; j1 <= n; j1++) {
			for (k1 = 0; k1 < 3; k1++) {
				for (i2 = 1; i2 <= n; i2++) {
					for (j2 = 1; j2 <= n; j2++) {
						for (k2 = 0; k2 < 3; k2++) {
							dist2[i1][j1][k1] = {INF, INF};
							dist[i1][j1][k1][i2][j2][k2] = {INF, INF};
							if (i1 == i2 && j1 == j2) {
							   if (k1 == k2) {
							   	  dist[i1][j1][k1][i2][j2][k2] = {0,0};
						       } else {
							   	  dist[i1][j1][k1][i2][j2][k2] = {1, 1};
							   }
							} else if (k1 == k2) {
							   if (k1 == 0 && rook(i1, j1, i2, j2)) {
							   	  dist[i1][j1][k1][i2][j2][k2] = {1, 0};
							   }
							   
							   if (k1 == 1 && bishop(i1, j1, i2, j2)) {
							   	  dist[i1][j1][k1][i2][j2][k2] = {1, 0};
							   }
							   
							   if (k1 == 2 && knight(i1, j1, i2, j2)) {
							   	  dist[i1][j1][k1][i2][j2][k2] = {1, 0};
				   	  		   }
							}
						}
					}
				}
			}
		}
	}
	
	int i3, j3, k3;
	for (i3 = 1; i3 <= n; i3++) {
		for (j3 = 1; j3 <= n; j3++) {
			for (k3 = 0; k3 < 3; k3++) {
				for (i1 = 1; i1 <= n; i1++) {
					for (j1 = 1; j1 <= n; j1++) {
						for (k1 = 0; k1 < 3; k1++) {
							for (i2 = 1; i2 <= n; i2++) {
								for (j2 = 1; j2 <= n; j2++) {
									for (k2 = 0; k2 < 3; k2++) {
										dist[i1][j1][k1][i2][j2][k2] 
										= min(dist[i1][j1][k1][i2][j2][k2], add(dist[i1][j1][k1][i3][j3][k3], dist[i3][j3][k3][i2][j2][k2]));
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
	for (i1 = 1; i1 <= n * n; i1++) {
		for (j1 = 0; j1 < 3; j1++) {
			for (k1 = 0; k1 < 3; k1++) {
				int x = rev[i1].first, y = rev[i1].second;
				g[x][y][j1].push_back(edge{x, y, k1, make_pair(dist[x][y][j1][x][y][k1].first, dist[x][y][j1][x][y][k1].second)});
				if (i1 != 1) {
				   int px = rev[i1-1].first, py = rev[i1-1].second;
				   g[px][py][k1].push_back(edge{x, y, j1, dist[px][py][k1][x][y][j1]});
				}
			}
		}
	}
	
	
	priority_queue<state> q;
	dist2[rev[1].first][rev[1].second][0] = {0,0};
	dist2[rev[1].first][rev[1].second][1] = {0,0};
	dist2[rev[1].first][rev[1].second][2] = {0,0};
	q.push(state{rev[1].first, rev[1].second, 0, make_pair(0,0)});
	q.push(state{rev[1].first, rev[1].second, 1, make_pair(0,0)});
	q.push(state{rev[1].first, rev[1].second, 2, make_pair(0,0)});
	while (!q.empty()) {
		  state curr = q.top();
		  q.pop();
		  if (visited[curr.x][curr.y][curr.z]) {
		  	 continue;
		  }
		  if (a[curr.x][curr.y] == n * n) {
		  	 printf("%d %d\n", curr.dis.first, curr.dis.second);
		  	 break;
		  }
		  visited[curr.x][curr.y][curr.z] = true;
		  for (auto nxt : g[curr.x][curr.y][curr.z]) {
		  	  if (!visited[nxt.x][nxt.y][nxt.z]) {
			  	 if (dist2[nxt.x][nxt.y][nxt.z] > add(curr.dis, nxt.cost)) {
	             	 dist2[nxt.x][nxt.y][nxt.z] = add(curr.dis, nxt.cost);
					 q.push(state{nxt.x, nxt.y, nxt.z, dist2[nxt.x][nxt.y][nxt.z]});
				 }	
	          }
		  }
	}
	return 0;
}

