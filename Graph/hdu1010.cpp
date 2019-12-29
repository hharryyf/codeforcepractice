#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 11
typedef long long ll;
using namespace std;

int visited[MAX_SIZE][MAX_SIZE];
char mp[MAX_SIZE][MAX_SIZE];
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int n, m, T;
int sx, sy, tx, ty;
bool valid = false;

void init() {
	 int i;
	 for (i = 0; i < MAX_SIZE; i++) {
	 	 memset(visited[i], 0, sizeof(visited));
	 }
}

void dfs(int x, int y, int t) {
    int i;
    if (valid) return;
    if (t > T || x < 0 || y < 0 || x >= n || y >= m) return;
    int rem = T - t - (abs(x - tx) + abs(y - ty));
    if (rem < 0 || rem % 2 == 1) return;
    if (T == t && x == tx && y == ty) {
        valid = true;
        return;
    }
    
    for (i = 0 ; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
        if (!visited[nx][ny] && mp[nx][ny] != 'X') {
            visited[nx][ny] = 1;
            dfs(nx, ny, t + 1);
            visited[nx][ny] = 0;
        }
    }
}

int main() {
	int i, j;
	while (scanf("%d%d%d", &n, &m, &T) != EOF) {
		  int wall = 0;
		  if (n == 0 && m == 0 && T == 0) break;
		  init();
		  for (i = 0; i < n; i++) {
		  	  scanf("%s", mp[i]);
		  }
		  
		  for (i = 0 ; i < n; i++) {
		  	  for (j = 0 ; j < m; j++) {
		            if (mp[i][j] == 'S') {
		                sx = i, sy = j;
		            } else if (mp[i][j] == 'D') {
		                tx = i, ty = j;
		            } else if (mp[i][j] == 'X') {
		                wall++; 
		            }
			  }
		  }
		  
		  if (n * m - wall <= T) {
		      printf("NO\n");
		  } else {
		      valid = false;
		      visited[sx][sy] = 1;
		      dfs(sx, sy, 0);
		      printf("%s\n", valid ? "YES" : "NO");
		  }
	}
	
	return 0;
}

