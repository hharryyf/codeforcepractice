#include <bits/stdc++.h>
#define MAX_SIZE 111
using namespace std;

char g[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];
pair<int, int> pre[MAX_SIZE][MAX_SIZE];
// the correct path from (1, 1) to F
vector<pair<int, int>> path;
int dx[4] = {0, 1, -1, 0};
int dy[4] = {-1, 0, 0, 1};
int n, m;


void BFS(int sx, int sy) {
    int i;
    int ex = n, ey = m;
    queue<pair<int, int>> q;
    q.push(make_pair(sx, sy));
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        if (visited[p.first][p.second]) continue;
        visited[p.first][p.second] = 1;
        if (g[p.first][p.second] == 'F') {
            ex = p.first, ey = p.second;
            break;
        }
        for (i = 0 ; i < 4; ++i) {
            int tx = p.first + dx[i], ty = p.second + dy[i];
            if (tx > n || tx < 1 || ty > m || ty < 1 || visited[tx][ty] || g[tx][ty] == '*') continue;
            pre[tx][ty] = make_pair(p.first, p.second);
            q.push(make_pair(tx, ty));
        }
    }

    while (ex != sx || ey != sy) {
        if (pre[ex][ey].first == 0 && pre[ex][ey].second == 0) break;
        path.emplace_back(ex, ey);
        auto p = pre[ex][ey];
        ex = p.first, ey = p.second;
    }

    reverse(path.begin(), path.end());
}

char st[5] = {'L', 'R', 'U', 'D'};

void interact(char ch) {
    printf("%c\n", ch);
    fflush(stdout);
}
// move from (fx, fy) to (tx, ty)
void query(int fx, int fy, int tx, int ty) {
    int x, y;
    if (abs(fx - tx) + abs(fy - ty) != 1) {
        printf("BFS is wrong!\n");
        exit(0);
    }

    // we should move downward
    if (tx - fx == 1) {
        interact(st[3]);
        scanf("%d%d", &x, &y);
        if (x != tx || y != ty) {
            swap(st[2], st[3]);
            interact(st[3]);
            scanf("%d%d", &x, &y);
        }
        return;
    } 
    // we should move upward
    if (tx - fx == -1) {
        interact(st[2]);
        scanf("%d%d", &x, &y);
        if (x != tx || y != ty) {
            swap(st[2], st[3]);
            interact(st[2]);
            scanf("%d%d", &x, &y);
        }
        
        return;
    }
    // we should move right
    if (ty - fy == 1) {
        interact(st[1]);
        scanf("%d%d", &x, &y);
        if (x != tx || y != ty) {
            swap(st[0], st[1]);
            interact(st[1]);
            scanf("%d%d", &x, &y);
        }
        return;
    }
    // we should move left
    interact(st[0]);
    scanf("%d%d", &x, &y);
    if (x != tx || y != ty) {
        swap(st[0], st[1]);
        interact(st[0]);
        scanf("%d%d", &x, &y);
    }
}

int main() {
    int i;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) {
        scanf("%s", g[i]+1);
    }

    BFS(1, 1);
    /*
    for (auto p : path) {
        cout << p.first << " " << p.second << endl;
    }*/
    int x = 1, y = 1;
    for (auto p : path) {
        query(x, y, p.first, p.second);
        x = p.first, y = p.second;
    }
    return 0;
}