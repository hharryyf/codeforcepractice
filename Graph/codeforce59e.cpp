#include <bits/stdc++.h>
typedef long long ll;
#define INF 100000000 
#define MAX_SIZE 3011
using namespace std;

bool visited[MAX_SIZE][MAX_SIZE];
int dist[MAX_SIZE][MAX_SIZE];
pair<int, int> pre[MAX_SIZE][MAX_SIZE];
vector<int> g[MAX_SIZE];
unordered_map<int, unordered_map<int, unordered_set<int>>> banned;
int n;

struct state {
    int pr, cur;
    int dist;
    bool operator < (const state other) const {
        return dist > other.dist;
    }
};

bool isvalid(int a, int b, int c) {
    if (banned.find(a) == banned.end()) return true;
    if (banned[a].find(b) == banned[a].end()) return true;
    if (banned[a][b].find(c) == banned[a][b].end()) return true;
    return false;
}

void add(int a, int b, int c) {
    banned[a][b].insert(c);
}

void dijkstra() {
    priority_queue<state> q;
    state target = {0,0,0};
    bool hassol = false;
    int i, j;
    for (i = 0 ; i < MAX_SIZE; i++) {
        for (j = 0 ; j < MAX_SIZE; j++) {
            if (i != j) {
                dist[i][j] = INF;
            }
        }
    }
    dist[0][1] = 0;
    q.push(state{0, 1, 0});
    while (!q.empty()) {
        state p = q.top();
        q.pop();
        if (visited[p.pr][p.cur]) continue;
        dist[p.pr][p.cur] = p.dist;
        visited[p.pr][p.cur] = true;
        if (p.cur == n) {
            target = p;
            hassol = true;
            break;
        }
        
        for (auto nv : g[p.cur]) {
            if (!visited[p.cur][nv] && isvalid(p.pr, p.cur, nv)) {
                if (dist[p.cur][nv] > dist[p.pr][p.cur] + 1) {
                    dist[p.cur][nv] = dist[p.pr][p.cur] + 1;
                    q.push(state{p.cur, nv, dist[p.cur][nv]});
                    pre[p.cur][nv] = make_pair(p.pr, p.cur);
                }
            }
        }
    }
    
    if (!hassol) {
        printf("-1\n");
        return;
    }
    
    printf("%d\n", target.dist);
    pair<int, int> pp = make_pair(target.pr, target.cur);
    stack<int> st;
    while (pp.second != 0) {
        st.push(pp.second);
        pp = pre[pp.first][pp.second];
    }
    
    while (!st.empty()) {
        printf("%d ", st.top());
        st.pop();
    }
    printf("\n");
}

int main() {
    int m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0 ; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        g[a].push_back(b);
        g[b].push_back(a);
    }
    
    for (int i = 0 ; i < k; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }
    dijkstra();
    return 0;
}
