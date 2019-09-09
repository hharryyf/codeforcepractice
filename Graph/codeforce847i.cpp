#include <bits/stdc++.h>
#define MAX_SIZE 256

using namespace std;

bool visited[MAX_SIZE][MAX_SIZE];
char arr[MAX_SIZE][MAX_SIZE];
long long ans[MAX_SIZE][MAX_SIZE];

// rows and cols
int n, m;
// noise unit of 'A' and maximum allowed noise
long long q, p;

void BFS(int x, int y);

int main(int argc, char *argv[]) {
	int i, j;
	scanf("%d%d%lld%lld", &n, &m, &q, &p);
	for (i = 0 ; i < n; i++) {
		scanf("%s", arr[i]);
	}
	
	for (i = 0 ; i < n; i++) {
		for (j = 0 ; j < m; j++) {
			if (arr[i][j] == '*') {
				ans[i][j] = 0ll;
			} else if (arr[i][j] >= 'A' && arr[i][j] <= 'Z') {
				BFS(i, j);
			}	
		}
	}
	
	int cnt = 0;
	for (i = 0 ; i < n; i++) {
		for (j = 0 ; j < m; j++) {
			// cout << ans[i][j] << " ";
			if(ans[i][j] > p) cnt++;
		}
		// cout << endl;
	}
	
	cout << cnt << endl;
	return 0;
}

void BFS(int x, int y) {
	memset(visited, false, sizeof(visited));
	
	// a queue of ((x, y), noise)
	queue<pair<pair<int, int>, long long>> qu;
	qu.push(make_pair(make_pair(x, y), (arr[x][y] - 'A' + 1) * q));
	visited[x][y] = true;
	ans[x][y] += (arr[x][y] - 'A' + 1) * q;
	int dx[4] = {0,0,1,-1};
	int dy[4] = {1,-1,0,0};
	while (!qu.empty()) {
		pair<pair<int, int>, long long> next = qu.front();
		qu.pop();
		int cx = next.first.first, cy = next.first.second;
		if (next.second <= 1) continue;
		for (int i = 0 ; i < 4; i++) {
			int tx = dx[i] + cx;
			int ty = dy[i] + cy;
			if (tx < 0 || ty < 0 || tx >= n || ty >= m) continue;
			if (visited[tx][ty] || arr[tx][ty] == '*') continue;
			visited[tx][ty] = true;
			ans[tx][ty] += next.second / 2;
			qu.push(make_pair(make_pair(tx, ty), next.second / 2));
		}
		
	}
}
