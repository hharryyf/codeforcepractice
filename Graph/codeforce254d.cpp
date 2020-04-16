#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;

char g[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];
bool visited2[MAX_SIZE][MAX_SIZE];
vector<pair<int, int>> rat;
int n, m, d;

bool valid(int x, int y) {
	return x <= n && x >= 1 && y <= m && y >= 1 && (g[x][y] != 'X');
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int i, j, cnt = 0, sx = 0, sy = 0;
	int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
	scanf("%d%d%d", &n, &m, &d);
	for (i = 1; i <= n; ++i) {
		scanf("%s", g[i] + 1);
		for (j = 1; j <= m; ++j) {
			if (g[i][j] == 'R') {
				cnt++;
				sx = i, sy = j;
				rat.emplace_back(i, j);
			}
		}
	}
	
	if (cnt > 2 * (2 * d * d + 2 * d + 1)) {
		printf("-1\n");
		return 0;
	}
	
	queue<pair<pair<int, int>, int>> q;
	vector<pair<int, int>> startnode;
	q.push(make_pair(make_pair(sx, sy), 0));
	while (!q.empty()) {
		auto p = q.front();
		q.pop();
		if (visited[p.first.first][p.first.second]) continue;
		visited[p.first.first][p.first.second] = true;
		startnode.emplace_back(p.first.first, p.first.second);
		for (i = 0 ; i < 4; ++i) {
			int tx = dx[i] + p.first.first, ty = dy[i] + p.first.second;
			if (valid(tx, ty) && p.second < d && !visited[tx][ty]) {
				q.push(make_pair(make_pair(tx, ty), p.second + 1));
			}
		}
	}
	
	for (auto p : startnode) {
		visited[p.first][p.second] = false;
	}
	
	pair<int, int> b1;
	for (auto st : startnode) {
		// cout << "start node " << st.first << ", " << st.second << endl;
		vector<pair<int, int>> bomb;
		b1.first = st.first, b1.second = st.second;
		q.push(make_pair(make_pair(st.first, st.second), 0));
		while (!q.empty()) {
			auto p = q.front();
			q.pop();
			if (visited[p.first.first][p.first.second]) continue;
			visited[p.first.first][p.first.second] = true;
			bomb.emplace_back(p.first.first, p.first.second);
			for (i = 0 ; i < 4; ++i) {
				int tx = dx[i] + p.first.first, ty = dy[i] + p.first.second;
				if (valid(tx, ty) && p.second < d && !visited[tx][ty]) {
					q.push(make_pair(make_pair(tx, ty), p.second + 1));
				}
			}
		}
		
		bool kill = true;
		for (auto &r : rat) {
			if (!visited[r.first][r.second]) {
				kill = false;
				sx = r.first, sy = r.second;
			}
		}
		
		if (kill) {
			for (i = 1; i <= n; ++i) {
				for (j = 1; j <= m; ++j) {
					if (valid(i, j) && (i != b1.first || j != b1.second)) {
						printf("%d %d %d %d\n", i, j, b1.first, b1.second);
						return 0;
					}
				}
			}
		} else {
			vector<pair<int, int>> secondnode;
			q.push(make_pair(make_pair(sx, sy), 0));
			while (!q.empty()) {
				auto p = q.front();
				q.pop();
				if (visited2[p.first.first][p.first.second]) continue;
				visited2[p.first.first][p.first.second] = true;
				secondnode.emplace_back(p.first.first, p.first.second);
				for (i = 0 ; i < 4; ++i) {
					int tx = dx[i] + p.first.first, ty = dy[i] + p.first.second;
					if (valid(tx, ty) && p.second < d && !visited2[tx][ty]) {
						q.push(make_pair(make_pair(tx, ty), p.second + 1));
					}
				}
			}
			
			for (auto &p : secondnode) {
				visited2[p.first][p.second] = false;
			}
			
			for (auto &sc : secondnode) {
				// cout << "second node " << sc.first << ", " << sc.second << endl;
				vector<pair<int, int>> ps;
				q.push(make_pair(make_pair(sc.first, sc.second), 0));
				while (!q.empty()) {
					auto p = q.front();
					q.pop();
					if (visited2[p.first.first][p.first.second]) continue;
					visited2[p.first.first][p.first.second] = true;
					ps.emplace_back(p.first.first, p.first.second);
					for (i = 0 ; i < 4; ++i) {
						int tx = dx[i] + p.first.first, ty = dy[i] + p.first.second;
						if (valid(tx, ty) && p.second < d && !visited2[tx][ty]) {
							q.push(make_pair(make_pair(tx, ty), p.second + 1));
						}
					}
				}
				
				kill = true;
				
				for (auto r : rat) {
					if (!visited[r.first][r.second] && !visited2[r.first][r.second]) {
						kill = false;
						break;
					}
				}
				
				if (kill) {
					printf("%d %d %d %d\n", b1.first, b1.second, sc.first, sc.second);
					return 0;
				}
				
				for (auto p : ps) {
					visited2[p.first][p.second] = false;
				}
			}
		}
		
		for (auto b : bomb) {
			visited[b.first][b.second] = visited2[b.first][b.second] = false;
		}
	}
	
	printf("-1\n");
	return 0;
}