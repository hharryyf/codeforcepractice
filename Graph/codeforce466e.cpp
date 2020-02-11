#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 100111
using namespace std;

bool leaf[MAX_SIZE];
int f[MAX_SIZE];
int dfsord[MAX_SIZE];
int subsz[MAX_SIZE];
vector<int> g[MAX_SIZE];
int k = 1;

struct event {
    int tp, x, y;
};

vector<event> evt;
// join i stores the index of the ith type-2 event
int join[MAX_SIZE];

// whether v has a child join[t] and they are in the same
// connected component with id
struct qrs {
    int t;
    int id;
    int v;
    bool operator < (qrs other) const {
        return t < other.t;
    } 
};

vector<qrs> q;

int find(int x) {
    if (x == f[x]) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    f[a] = b;
}

void dfs(int v) {
    subsz[v] = 1;
    dfsord[v] = k++;
    for (auto nv : g[v]) {
        dfs(nv);
        subsz[v] += subsz[nv];
    }
}
// return true iff v is a child of u
bool ischild(int v, int u) {
    return (dfsord[v] >= dfsord[u]) && (dfsord[v] <= (dfsord[u] + subsz[u] - 1));
}

int ans[MAX_SIZE];

int main() {
    int i, n, m, j;
    int cnt = 1;
    for (i = 0; i < MAX_SIZE; i++) f[i] = i;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        int tp;
        scanf("%d", &tp);
        if (tp == 1) {
            int x, y;
            scanf("%d%d", &x, &y);
            g[y].push_back(x);
            evt.push_back(event{tp, x, y});
            leaf[x] = true;
        } else if (tp == 2) {
            int x;
            scanf("%d", &x);
            int p = evt.size();
            join[cnt++] = p;
            evt.push_back(event{tp, x, 0});
        } else {
            int x, y;
            scanf("%d%d", &x, &y);
            int p = q.size();
            q.push_back(qrs{join[y], p, x});
        }
    }
    sort(q.begin(), q.end());
    for (i = 1; i <= n; i++) {
        if (!leaf[i]) dfs(i);
    }
    
    for (i = 0, j = 0 ; i < q.size(); i++) {
        while (j < evt.size() && j <= q[i].t) {
            if (evt[j].tp == 1) {
                unionset(evt[j].x, evt[j].y);
            }
            j++;
        }
        
        if (find(q[i].v) == find(evt[q[i].t].x) && ischild(evt[q[i].t].x, q[i].v)) {
            ans[q[i].id] = 1;
        }
    }
    
    for (i = 0 ; i < q.size(); i++) {
        printf("%s\n", ans[i] ? "YES" : "NO");
    }
    return 0;
}
