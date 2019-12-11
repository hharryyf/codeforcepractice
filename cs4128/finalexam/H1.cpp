#include <bits/stdc++.h>
#define MAX_SIZE 41
using namespace std;

char s[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];

int r, c, k;

int cost[MAX_SIZE];

int dx[4] = {0,1,0,-1}, dy[4] = {-1,0,1,0};

void dfs(int x, int y) {
	visited[x][y] = 1;
	int i;
	for (i = 0 ; i < 4; i++) {
		int tx = dx[i] + x, ty = dy[i] + y;
		if (tx >= 0 && tx < r && ty >= 0 && ty < c) {
			if (!visited[tx][ty] && s[tx][ty] != '#') {
				dfs(tx, ty);
			}
		}
	}
}

int main() {
	cin >> r >> c >> k;
	int i, j;
	for (i = 0 ; i < r; i++) {
		scanf("%s", s[i]);
	}
	
	int x = 0, y = 0;
	for (i = 0; i < r; i++) {
		for (j = 0 ; j < c; j++) {
			if (s[i][j] == 'R') {
				x = i, y = j;
			} else if (s[i][j] >= 'a' && s[i][j] <= 'z') {
				s[i][j] = '#';
			}
		}
	}
	
	for (i = 0 ; i < k; i++) {
		scanf("%d", &cost[i]);
	}
	
	dfs(x, y);
	
	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++) {
			if ((i == 0 || j == 0 || i == r-1 || j == c-1) && visited[i][j]) {
				cout << -1 << endl;
				return 0;
			}
		}
	}
	cout << 0 << endl;
	return 0;
}
