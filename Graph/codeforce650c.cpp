#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 1000011
using namespace std;

int n, m;
vector<vector<int>> grid;
int f[MAX_SIZE];
int visited[MAX_SIZE];
vector<int> g[MAX_SIZE];

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    f[a] = b;
}

int index(int x, int y) {
    return x * m + y;
}

int line[MAX_SIZE];
int id;
int ans[MAX_SIZE];

static bool cmp(int &a, int &b) {
    return grid[id][a] < grid[id][b];
}

static bool cmp2(int &a, int &b) {
    return grid[a][id] < grid[b][id];
}

void dfs(int v) {
    if (g[v].empty()) visited[v] = 1;
    for (auto nv : g[v]) {
        if (!visited[nv]) {
            dfs(nv);  
        } 

        visited[v] = max(visited[nv] + 1, visited[v]);
    }
}

int main() {
    int i, j;
    for (i = 0 ; i < MAX_SIZE; ++i) f[i] = i;
    scanf("%d%d", &n, &m);
    grid = vector<vector<int>>(n, vector<int>(m, 0));
    for (i = 0 ; i < n; ++i) {
        for (j = 0 ; j < m; ++j) {
            scanf("%d", &grid[i][j]);
        }
    }

    for (i = 0 ; i < m; ++i) line[i] = i;
    for (i = 0 ; i < n; ++i) {
        id = i;
        sort(line, line + m, cmp);
        for (j = 1 ; j < m; ++j) {
            if (grid[i][line[j]] == grid[i][line[j-1]]) {
                unionset(index(i, line[j]), index(i, line[j-1]));
            }
        }
    }

    for (i = 0 ; i < n; ++i) line[i] = i;
    for (i = 0 ; i < m; ++i) {
        id = i;
        sort(line, line + n, cmp2);
        for (j = 1; j < n; ++j) {
            if (grid[line[j]][i] == grid[line[j-1]][i]) {
                unionset(index(line[j], i), index(line[j-1], i));
            }
        }
    }

    for (i = 0 ; i < m; ++i) line[i] = i;
    for (i = 0 ; i < n; ++i) {
        id = i;
        sort(line, line + m, cmp);
        for (j = 1 ; j < m; ++j) {
            if (grid[i][line[j]] > grid[i][line[j-1]]) {
                g[find(index(i, line[j]))].push_back(find(index(i, line[j-1])));
            }
        }
    }

    for (i = 0 ; i < n; ++i) line[i] = i;
    for (i = 0 ; i < m; ++i) {
        id = i;
        sort(line, line + n, cmp2);
        for (j = 1; j < n; ++j) {
            if (grid[line[j]][i] > grid[line[j-1]][i]) {
                g[find(index(line[j], i))].push_back(find(index(line[j-1], i)));
            }
        }
    }      

    for (i = 0 ; i < n * m; ++i) {
        if (find(i) == i && !visited[i]) {
            dfs(i);
        }
    }

    for (i = 0; i < n * m; ++i) {
        ans[i] = visited[find(i)];
    }

    for (i = 0 ; i < n; ++i) {
        for (j = 0 ; j < m; ++j) {
            printf("%d ", ans[index(i, j)]);
        }
        printf("\n");
    }
    return 0;
}