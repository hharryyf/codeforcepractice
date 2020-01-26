#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 1000111
using namespace std;

struct dsu {
    int subsz[MAX_SIZE], f[MAX_SIZE];
    void preprocess() {
        int i;
        for (i = 0 ; i < MAX_SIZE; i++) {
            f[i] = i, subsz[i] = 1;
        }
    }
    
    int find(int x) {
        if (f[x] == x) return x;
        return f[x] = find(f[x]);
    }
    
    bool sameset(int x, int y) {
        return find(x) == find(y);
    }
    
    void unionset(int x, int y) {
        int a = find(x), b = find(y);
        if (a == b) return;
        if (subsz[b] < subsz[a]) {
            subsz[a] += subsz[b];
            f[b] = a;
        } else {
            subsz[b] += subsz[a];
            f[a] = b;
        }
    }
    
    int query(int x) {
        return subsz[find(x)];
    }
};

vector<pair<ll, pair<int, int>>> candidate;
dsu s;
int n, m;
ll k;
ll g[1011][1011];
bool visited[1011][1011];
int dx[4] = {0, 1, -1, 0}, dy[4] = {1, 0, 0, -1};
int index(int x, int y) {
    return m * x + y;
}

void dfs(int x, int y, ll st) {
    if (visited[x][y]) return;
    visited[x][y] = true;
    int i;
    for (i = 0 ; i < 4; i++) {
        int tx = x + dx[i], ty = y + dy[i];
        if (tx < 0 || ty < 0 || tx >= n || ty >= m || g[tx][ty] < st) continue;
        s.unionset(index(x, y), index(tx, ty));
        if (!visited[tx][ty]) {
            dfs(tx, ty, st);
        }
    }
}

bool visited2[1011][1011];
vector<pair<int, int>> idx;

void dfs_2(int x, int y, ll st) {
    if (idx.size() >= k / st) return;
    visited2[x][y] = true;
    idx.emplace_back(x, y);
    int i;
    for (i = 0 ; i < 4; i++) {
        int tx = dx[i] + x, ty = dy[i] + y;
        if (tx < 0 || tx >= n || ty < 0 || ty >= m) continue;
        if (visited2[tx][ty] || g[tx][ty] < st) continue;
        dfs_2(tx, ty, st);
    }
}

int main() {
    s.preprocess();
    int i, j;
    scanf("%d%d%lld", &n, &m, &k);
    for (i = 0; i < n; i++) {
        for (j = 0 ; j < m; j++) {
            scanf("%lld", &g[i][j]);
            if (k % g[i][j] == 0) {
                candidate.push_back(make_pair(g[i][j],make_pair(i, j)));
            }
        }
    }
    
    sort(candidate.begin(), candidate.end(), greater<pair<ll, pair<int, int>>>());
    
    int x = -1, y = -1;
    for (auto c : candidate) {
        int cx = c.second.first, cy = c.second.second;
        dfs(cx, cy, c.first);
        if (s.query(index(cx, cy)) >= k / c.first) {
            x = cx, y = cy;
            break;
        }
    }
    
    if (x == -1 && y == -1) {
        printf("NO\n");
    } else {
        dfs_2(x, y, g[x][y]);
        ll st = g[x][y];
        // printf("%d %d\n", idx.size(), g[x][y]);
        for (auto p : idx) {
            g[p.first][p.second] = -1;
        }
        
        for (i = 0 ; i < n; i++) {
            for (j = 0 ; j < m; j++) {
                if (g[i][j] != -1) g[i][j] = 0;
            }
        }
        
        for (i = 0 ; i < n; i++) {
            for (j = 0 ; j < m; j++) {
                if (g[i][j] == -1) g[i][j] = st;
            }
        }
        
        printf("YES\n");
        for (i = 0 ; i < n; i++) {
            for (j = 0 ; j < m; j++) {
                printf("%d ", g[i][j]);
            }
            printf("\n");
        }
    }
    
    return 0;
}
