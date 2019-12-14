#include <bits/stdc++.h>
#define MAX_SIZE 1011
#define INF 1000000000
using namespace std;

typedef long long ll;

ll dist[3][MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];
char g[MAX_SIZE][MAX_SIZE];
int r, c;
struct state {
	int x, y;
	ll dist;
};

struct cmp {
	bool operator()(const state &a, const state &b) {
		return a.dist > b.dist;
	}
};

void init(int f) {
	if (f == 0) {
		for (int i = 0 ; i < MAX_SIZE; i++) {
			for (int j = 0 ; j < MAX_SIZE; j++) {
				dist[0][i][j] = dist[1][i][j] = dist[2][i][j] = INF;
			}
		}
	}
	
	for (int i = 0 ; i < MAX_SIZE; i++) {
		for (int j = 0 ; j < MAX_SIZE; j++) {
			visited[i][j] = false;
		}
	}
}

int dx[4] = {1, 0, 0, -1}, dy[4] = {0, 1, -1, 0};

void bfs(int dim) {
	init(1);
	priority_queue<state, vector<state>, cmp> q;
	int i, j;
	for (i = 0 ; i < r; i++) {
		for (j = 0 ; j < c; j++) {
			if (g[i][j] == dim + '0' + 1) {
				q.push(state{i, j, 0});
				dist[dim][i][j] = 0;
			} 
		}
	}
	
	while (!q.empty()) {
		state st = q.top();
		q.pop();
		if (visited[st.x][st.y]) continue;
		visited[st.x][st.y] = true;
		dist[dim][st.x][st.y] = st.dist;
		for (i = 0 ; i < 4; i++) {
			int tx = dx[i] + st.x, ty = dy[i] + st.y;
			if (tx >= 0 && tx < r && ty >= 0 && ty < c && !visited[tx][ty] && g[tx][ty] != '#') {
				if ((dist[dim][st.x][st.y] + (g[tx][ty] == '.' ? 1 : 0)) < dist[dim][tx][ty]) {
					int cost = 0;
					if (g[tx][ty] == '.') cost = 1; 
					dist[dim][tx][ty] = dist[dim][st.x][st.y] + cost;
					q.push(state{tx, ty, dist[dim][tx][ty]});
				}
			}
		}
	}
}

int main() {
	int i, j;
	init(0);
	scanf("%d%d", &r, &c);
	for (i = 0 ; i < r; i++) {
		scanf("%s", g[i]);
	}
	
	for (i = 0 ; i < 3; i++) {
		bfs(i);
	}
	
	ll ans = INF;
	for (i = 0 ; i < r; i++) {
		for (j = 0 ; j < c; j++) {
			if (g[i][j] == '.') {
				ans = min(ans, dist[0][i][j] + dist[1][i][j] + dist[2][i][j] - 2);
			} else {
				ans = min(ans, dist[0][i][j] + dist[1][i][j] + dist[2][i][j]);
			}
			
			//cout << "("<< i << ", " << j << ") --> "<< "(" << dist[0][i][j] << ", " << dist[1][i][j] << ", " << dist[2][i][j] << ")" << endl;
		}
	}
	
	if (ans < INF) {
		cout << ans << endl;
	} else {
		cout << -1 << endl;
	}
	
	return 0;
}
