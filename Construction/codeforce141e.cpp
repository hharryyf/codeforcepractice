#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

struct edge {
    int from, to, wt;
};

edge edg[MAX_SIZE];

int f[1011];
int select[MAX_SIZE];

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    f[a] = b;
}

char st[4];
vector<pair<int, int>> g[MAX_SIZE];
vector<int> ret;
int pre[MAX_SIZE];
int pr[MAX_SIZE];
int visited[MAX_SIZE];
int n;

int BFS(int src, int target) {
    if (src == target) return -1;
    // ret records all the edges on the path
    ret.clear();
    memset(visited, 0, sizeof(visited));
    queue<int> q;
    pre[src] = src;
    visited[src] = 1;
    q.push(src);
    while (!q.empty()) {
        int v = q.front();
        if (v == target) break;
        q.pop();
        for (auto np : g[v]) {
            if (!visited[np.first]) {
                pre[np.first] = v;
                pr[np.first] = np.second;
                q.push(np.first);
                visited[np.first] = 1;
            }
        }
    }

    if (!visited[target]) return -1;

    auto v = target;
    while (v != src) {
        ret.push_back(pr[v]);
        v = pre[v];
    }
    
    for (auto e : ret) {
        if (edg[e].wt == 0) {
            return e;
        }
    }

    return -1;
}

void addedge(int idx) {
    g[edg[idx].from].emplace_back(edg[idx].to, idx);
    g[edg[idx].to].emplace_back(edg[idx].from, idx);
    select[idx] = 1;
}

void removeedge(int idx) {
    auto iter = g[edg[idx].from].begin();
    while (iter != g[edg[idx].from].end()) {
        if (iter->second == idx) {
            g[edg[idx].from].erase(iter);
            break;
        }
        ++iter;
    }

    iter = g[edg[idx].to].begin();
    while (iter != g[edg[idx].to].end()) {
        if (iter->second == idx) {
            g[edg[idx].to].erase(iter);
            break;
        }
        ++iter;
    }

    select[idx] = 0;
}

int main() {
    int i, m;
    scanf("%d%d", &n, &m);
    for (i = 1; i < 1011; ++i) {
        f[i] = i;
    }

    for (i = 1; i <= m; ++i) {
        scanf("%d%d%s", &edg[i].from, &edg[i].to, st);
        edg[i].wt = (st[0] == 'S');
    }

    if (n % 2 == 0) {
        printf("-1\n");
        return 0;
    }

    int edg0 = 0, edg1 = 0;
    for (i = 1; i <= m; ++i) {
        if (edg[i].wt == 0) {
            if (find(edg[i].from) != find(edg[i].to)) {
                addedge(i);
                unionset(edg[i].from, edg[i].to);
                edg0++;    
            }
        }
    }

    if (edg0 < n / 2) {
        printf("-1\n");
        return 0;
    }

    for (i = 1; i <= m; ++i) {
        if (edg[i].wt == 1) {
            if (find(edg[i].from) != find(edg[i].to)) {
                addedge(i);
                unionset(edg[i].from, edg[i].to);
                edg1++;
            }
        }
    }

    // cout << edg0 << " " << edg1 << endl;
    if (edg0 + edg1 != n - 1) {
        printf("-1\n");
        return 0;
    }

    for (i = 1; i <= m && edg0 > edg1; ++i) {
        if (!select[i] && edg[i].wt == 1) {
            int ret = BFS(edg[i].from, edg[i].to);
            if (ret != -1) {
                addedge(i);
                removeedge(ret);
                edg0--;
                edg1++;
            }
        }
    }

    // cout << edg0 << " " << edg1 << endl;
    if (edg0 == edg1) {
        printf("%d\n", n - 1);
        for (i = 1; i <= m; ++i) {
            if (select[i]) {
                printf("%d ", i);
            }
        }
        printf("\n");
    } else {
        printf("-1\n");
    }
    return 0;
}