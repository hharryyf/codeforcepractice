#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 200111

struct edge {
    int to, id, rev;
};

vector<edge> g[MAX_SIZE];
vector<edge> tree[MAX_SIZE];
int s[MAX_SIZE];
int visited[MAX_SIZE];
int f[MAX_SIZE];
int n;
#define WRONGANSWER

void dfs1(int v) {
    visited[v] = 1;
    for (auto e : g[v]) {
        int nv = e.to;
        if (!visited[nv]) {
            tree[v].push_back(e);
            #ifndef WRONGANSWER
            cout << "addedge " << v << " to " << nv << " dir= " << e.rev << endl;
            #endif
            dfs1(nv);
        }
    }
}

void dfs2(int v, int pre, int eid, int dir) {
    
    for (auto e : tree[v]) {
        dfs2(e.to, v, e.id, e.rev); 
    }

    // dir == -1 means the origional edge is from v->eid
    // dir == 1 means the origional edge is from eid->v
    f[eid] = dir * s[v];
    s[pre] += dir * f[eid];
}


int main() {
    int i, m, tol = 0;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &s[i]);
        tol += s[i];
    }
    scanf("%d", &m);
    for (i = 1; i <= m; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].push_back(edge{v2, i, 1});
        g[v2].push_back(edge{v1, i, -1});
    }
    
    if (tol != 0) {
        printf("Impossible\n");
        return 0;
    }

    printf("Possible\n");
    dfs1(1);
    dfs2(1, 0, 0, 0);
    for (i = 1; i <= m; ++i) {
        printf("%d\n", f[i]);
    } 

    return 0;
}