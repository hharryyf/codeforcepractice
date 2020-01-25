#include <bits/stdc++.h>
#define INF 100000000
#define MAX_SIZE 3011
using namespace std;

vector<int> g[MAX_SIZE];
int dist[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE];
int n, m;
set<pair<int, int>> to[MAX_SIZE];
set<pair<int, int>> from[MAX_SIZE];

void insert(int i, int v) {
    if (dist[i][v] < INF && i != v) {
        to[v].insert(make_pair(dist[i][v], i));
        if (to[v].size() > 3) {
            auto p = *to[v].begin();
            to[v].erase(p);
        }
        
        from[i].insert(make_pair(dist[i][v], v));
        if (from[i].size() > 3) {
            auto p = *from[i].begin();
            from[i].erase(p);
        } 
    }
}

bool valid(int v1, int v2, int v3, int v4) {
    return (v1 != v2) && (v2 != v3) && (v3 != v4) && (v1 != v3) && (v1 != v4) && (v2 != v4);
}

void init() {
    int i, j;
    for (i = 0 ; i < MAX_SIZE; i++) {
        for (j = 0 ; j < MAX_SIZE; j++) {
            dist[i][j] = INF;
        }
    }
}

void BFS(int src) {
    memset(visited, false, sizeof(visited));
    queue<pair<int, int>> q;
    q.push(make_pair(src, 0));
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        if (visited[p.first]) continue;
        visited[p.first] = true;
        dist[src][p.first] = p.second;
        for (auto nv : g[p.first]) {
            if (!visited[nv]) {
                q.push(make_pair(nv, p.second + 1));
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    int i, j;
    init();
    for (i = 0 ; i < m; i++) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        if (v1 != v2) {
            g[v1].push_back(v2);
        }
    }
    
    for (i = 1; i <= n; i++) {
        BFS(i);
    }
    
    int s = 0, v1 = 0, v2 = 0, t = 0, mx = 0;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            insert(i, j);       
        }
    }
    
    
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            for (auto p1 : to[i]) {
                for (auto p2 : from[j]) {
                    if (valid(i, j, p1.second, p2.second) && dist[i][j] < INF && mx <= dist[i][j] + p1.first + p2.first) {
                        s = p1.second, t = p2.second, v1 = i, v2 = j;
                        mx = dist[i][j] + p1.first + p2.first;
                    }
                }
            }
        }
    }
    //printf("%d\n", mx);
    printf("%d %d %d %d\n", s, v1, v2, t);
    return 0;
}
