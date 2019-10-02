#include <bits/stdc++.h>
#define MAX_SIZE 1001
#define INF 10000011
using namespace std;

int visited[MAX_SIZE][MAX_SIZE];

int dist[MAX_SIZE][MAX_SIZE];

int grid[MAX_SIZE][MAX_SIZE];

int m, n;

int sssp() {
	priority_queue<pair< int, pair< int, int> >, vector<pair< int, pair< int, int> > >, greater<pair< int, pair< int, int> > > > q;
	q.push(make_pair(grid[1][1], make_pair(1, 1)));
	dist[1][1] = grid[1][1];
	int dx[4] = {1,0,0,-1}, dy[4] = {0,1,-1,0};
	while (!q.empty()) {
		pair< int, pair< int, int> > tp = q.top();
		int x = tp.second.first, y = tp.second.second, ds = tp.first;
		q.pop();
		
		// cout << x << " " << y << " " << ds << endl;
		if (visited[x][y]) continue;
		if (x == m && y == n) return ds;
		visited[x][y] = 1;
		for (int i = 0 ; i < 4; i++) {
			int tx = x + dx[i], ty = y + dy[i];
			if (tx >= 1 && tx <= m && ty >= 1 && ty <= n && !visited[tx][ty] && ds + grid[tx][ty] < dist[tx][ty]) {
				dist[tx][ty] = ds + grid[tx][ty];
				q.push(make_pair(dist[tx][ty], make_pair(tx, ty)));
			}
		}
	}
	
	return -1; 
}

int main(int argc, char *argv[]) {
	int T;
	scanf("%d", &T);
	while (T > 0) {
		scanf("%d%d", &m, &n);
		for (int i = 1 ; i <= m; i++) {
			for (int j = 1 ; j <= n; j++) {
				scanf("%d", &grid[i][j]);
				visited[i][j] = 0;
				dist[i][j] = INF;
			}
		}
		
		printf("%d\n", sssp());
		T--;
	}
	return 0;
}
