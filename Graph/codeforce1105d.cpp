#include <bits/stdc++.h>
#define MAX_SIZE 1011

using namespace std;
// the original grid
char grid[MAX_SIZE][MAX_SIZE];
// the visited array
int visited[MAX_SIZE][MAX_SIZE];
// n rows, m cols and pn players
int n, m, pn;
// speed of the ith player
int s[10];
// the bfs queue ((x,y), depth) 
queue<pair<pair<int,int>, int> > q[10];

int maxdepth[10];

bool hasmoved = true;

int main(int argc, char *argv[]) {
	cin >> n >> m >> pn;
	int i, j;
	for (i = 1; i <= pn; i++) {
		cin >> s[i];
		maxdepth[i] = s[i];
	}
	
	for (i = 0; i < n; i++) {
		scanf("%s", grid[i]);
		for (j = 0 ; j < m; j++) {
			if (grid[i][j] == '#') {
				visited[i][j] = 10;
			} else if (grid[i][j] >= '1' && grid[i][j] <= '9') {
				visited[i][j] = grid[i][j] - '0';
				q[visited[i][j]].push(make_pair(make_pair(i, j), 0));
			}
		}
	} 
	
	while (hasmoved) {
		hasmoved = false;
		for (i = 1 ; i <= pn; i++) {
			while (!q[i].empty()) {
				auto p = q[i].front();
				if (p.second >= maxdepth[i]) {
					maxdepth[i] = maxdepth[i] + s[i];
					break;
				}
				
				q[i].pop();
				
				int dx[4] = {1,-1,0,0};
				int dy[4] = {0,0,1,-1};
				
				for (j = 0 ; j < 4; j++) {
					int tx = p.first.first + dx[j], ty = p.first.second + dy[j];
					if (tx < n && tx >= 0 && ty < m && ty >= 0 && !visited[tx][ty]) {
						hasmoved = true;
						visited[tx][ty] = i;
						q[i].push(make_pair(make_pair(tx, ty), p.second + 1));
					}
				}
			}
		}
		
	}
	
	int ans[10] = {0,0,0,0,0,0,0,0,0,0};
	
	for (i = 0; i < n; i++) {
		for (j = 0 ; j < m; j++) {
			if (visited[i][j] >= 1 && visited[i][j] <= pn) {
				ans[visited[i][j]]++;
			}
		}
	}
	
	for (i = 1; i <= pn; i++) {
		cout <<  ans[i] << " ";
	}
	cout << endl;
	return 0;
}
