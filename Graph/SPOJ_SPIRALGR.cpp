#include <bits/stdc++.h>
#define MAX_SIZE 211
using namespace std;

// stores the information of the grid
unordered_set<int> prime;
int grid[MAX_SIZE][MAX_SIZE];
pair<int, int> coord[MAX_SIZE * MAX_SIZE];

int vis[MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];
struct state {
    int x, y;
    int dist;
};

const int U = 200;
int dx[4] = {1, 0, 0, -1};
int dy[4] = {0, 1, -1, 0};

void init() {
    int i, j;
    for (i = 2; i <= U * U; i++) {
        if (!vis[i]) {
            prime.insert(i);
            for (j = 1; i * j <= U * U; j++) {
                vis[i * j] = 1;
            }
        }
    }
    
    int x = 1, y = 1;
    int k = 0;
    int sx[4] = {0, 1, 0, -1}, sy[4] = {1, 0, -1, 0};
    for (i = U * U; i >= 1; i--) {
        grid[x][y] = i;
        coord[i] = make_pair(x, y);
        if (x + sx[k] > U || y + sy[k] > U || x + sx[k] < 1 || y + sy[k] < 1 || grid[x + sx[k]][y + sy[k]] != 0) {
            k = (k + 1) % 4;
        }
        x = x + sx[k];
        y = y + sy[k];
    }
}



int BFS(int start, int end) {
    int i, j;
    for (i = 0 ; i < MAX_SIZE; i++) {
        for (j = 0 ; j < MAX_SIZE; j++) {
            visited[i][j] = 0;
        }
    }
    
    queue<state> q;
    q.push(state{coord[start].first, coord[start].second, 0});
    while (!q.empty()) {
        auto nxt = q.front();
        q.pop();
        if (grid[nxt.x][nxt.y] == end) {
            return nxt.dist;
        }
        
        if (visited[nxt.x][nxt.y]) continue;
        visited[nxt.x][nxt.y] = 1;
        
        for (i = 0 ; i < 4; i++) {
            int tx = nxt.x + dx[i], ty = nxt.y + dy[i];
            if (tx < 1 || tx > U || ty < 1 || ty > U) continue;
            if (!visited[tx][ty] && prime.find(grid[tx][ty]) == prime.end()) {
                q.push(state{tx, ty, nxt.dist + 1});
            }
        }
    }
    
    return -1;
}

int main() {
    init();
    int n, m;
    int cnt = 1;
    while (scanf("%d%d", &n, &m) != EOF) {
        int ans = BFS(n, m);
        if (ans != -1) {
            printf("Case %d: %d\n", cnt, ans);
        } else {
            printf("Case %d: impossible\n", cnt);
        }
        cnt++;
    }
    return 0;
}
