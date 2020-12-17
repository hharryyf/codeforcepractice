#include <bits/stdc++.h>
using namespace std;
const int INF = 1e7;
int dist[55][55][55], dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int visited[55][55][55];
char st[55][55];
char c[55];
struct node {
	int u, v, d;
};

int N, M, L, sx, sy, ex, ey;

bool valid(int x, int y) {
	return x >= 1 && x <= N && y >= 1 && y <= M && st[x][y] != '#';
}

int main() {
	int i, j, k;
	scanf("%d%d", &N, &M);
	for (i = 1; i <= N; ++i) scanf("%s", st[i] + 1);
	scanf("%s", c + 1);
	L = strlen(c + 1);
	for (i = 0; i <= N; ++i) {
		for (j = 0; j <= M; ++j) {
			for (k = 0; k <= L; ++k) {
				dist[i][j][k] = INF;
			}
		}
	}

	for (i = 1; i <= N; ++i) {
		for (j = 1; j <= M; ++j) {
			if (st[i][j] == 'R') {
				sx = i, sy = j;
			}

			if (st[i][j] == 'E') {
				ex = i, ey = j;
			}
		}
	}

	int ans = 1e7;
	deque<node> q;
	dist[sx][sy][0] = 0;
	q.push_back(node{sx, sy, 0});
	while (!q.empty()) {
		
		auto curr = q.front();
		q.pop_front();
		int x = curr.u, y = curr.v, z = curr.d;
		// printf("%d %d %d --> %d\n", x, y, z, dist[x][y][z]);
		if (x == ex && y == ey) {
			ans = min(ans, dist[x][y][z]);
			continue;
		}
		if (visited[curr.u][curr.v][curr.d]) continue;
		visited[x][y][z] = 1;
		for (i = 0 ; i < 4; ++i) {
			int tx = x + dx[i], ty = y + dy[i];
			if (valid(tx, ty) && !visited[tx][ty][z]) {
				if (dist[tx][ty][z] > dist[x][y][z] + 1) {
					dist[tx][ty][z] = dist[x][y][z] + 1;
					q.push_back(node{tx, ty, z});
				}
			}
		}

		if (z + 1 <= L) {
			if (c[z+1] == 'U') {
				if (valid(x - 1, y)) {
					if (!visited[x-1][y][z+1] && dist[x-1][y][z+1] >  dist[x][y][z]) {
						q.push_front(node{x - 1, y, z+1});
						dist[x-1][y][z+1] = dist[x][y][z];
					}
				} else {
					if (!visited[x][y][z+1] && dist[x][y][z+1] > dist[x][y][z]) {
						q.push_front(node{x, y, z + 1});
						dist[x][y][z+1] =  dist[x][y][z];
					}
				}
			}

			if (c[z+1] == 'D') {
				if (valid(x + 1, y)) {
					if (!visited[x+1][y][z+1] && dist[x+1][y][z+1] >  dist[x][y][z]) {
						q.push_front(node{x + 1, y, z+1});
						dist[x+1][y][z+1] = dist[x][y][z];
					}
				} else {
					if (!visited[x][y][z+1] && dist[x][y][z+1] > dist[x][y][z]) {
						q.push_front(node{x, y, z + 1});
						dist[x][y][z+1] =  dist[x][y][z];
					}
				}
			}

			if (c[z+1] == 'L') {
				if (valid(x, y - 1)) {
					if (!visited[x][y - 1][z+1] && dist[x][y - 1][z+1] >  dist[x][y][z]) {
						q.push_front(node{x, y - 1, z+1});
						dist[x][y - 1][z+1] = dist[x][y][z];
					}
				} else {
					if (!visited[x][y][z+1] && dist[x][y][z+1] > dist[x][y][z]) {
						q.push_front(node{x, y, z + 1});
						dist[x][y][z+1] =  dist[x][y][z];
					}
				}
			}

			if (c[z+1] == 'R') {
				if (valid(x, y + 1)) {
					if (!visited[x][y + 1][z+1] && dist[x][y + 1][z+1] >  dist[x][y][z]) {
						q.push_front(node{x, y + 1, z+1});
						dist[x][y + 1][z+1] = dist[x][y][z];
					}
				} else {
					if (!visited[x][y][z+1] && dist[x][y][z+1] > dist[x][y][z]) {
						q.push_front(node{x, y, z + 1});
						dist[x][y][z+1] =  dist[x][y][z];
					}
				}
			}

			if (!visited[x][y][z+1] && dist[x][y][z+1] > dist[x][y][z] + 1) {
				dist[x][y][z+1] = dist[x][y][z] + 1;
				q.push_back(node{x, y, z + 1});
			}
		}
	}

	printf("%d\n", ans);
	return 0;
}