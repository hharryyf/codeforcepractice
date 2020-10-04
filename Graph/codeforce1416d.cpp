#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 524292
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;
typedef long long ll;

int tree[MAX_SIZE << 1];
vector<int> g[MAX_SIZE];
int endtime[MAX_SIZE];
pair<pair<int, int>, int> edg[MAX_SIZE];
pair<int, int> q[MAX_SIZE];
int f[MAX_SIZE];
int p[MAX_SIZE];
int parent[MAX_SIZE][19];
int sz[MAX_SIZE], id[MAX_SIZE], rid[MAX_SIZE];
set<int> root;
int n, m, Q;
int cnt = 0;

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index] = p[rid[l]];
        // cout << "index " << l << " value " << p[rid[l]] << endl;
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index] = max(tree[LEFT], tree[RIGHT]);
}

void update(int pt, int l, int r, int index) {
    if (pt < l || pt > r || l > r) return;
    if (l == r) {
        tree[index] = 0;
        return;
    }

    if (pt <= MID) {
        update(pt, l, MID, LEFT);
    } else {
        update(pt, MID + 1, r, RIGHT);
    }
    tree[index] = max(tree[LEFT], tree[RIGHT]);
}

pair<int, int> query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return make_pair(0, 0);
    if (l == r) return make_pair(tree[index], l);
    if (start <= l && r <= end) {
        if (tree[LEFT] > tree[RIGHT]) return query(start, end, l, MID, LEFT);
        return query(start, end, MID + 1, r, RIGHT);
    }
    if (end <= MID) return query(start, end, l, MID, LEFT);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
    return max(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void dfs(int v) {
    id[v] = ++cnt;
    rid[id[v]] = v;
    sz[v] = 1;
    for (auto nv : g[v]) {
        dfs(nv);
        sz[v] += sz[nv];
    }
}

void preprocess() {
    int i, j;
   
    for (j = 1; j <= 18; ++j) {
        for (i = 1; i <= cnt; ++i) {
            parent[rid[i]][j] = parent[parent[rid[i]][j-1]][j-1];
        }
    }
}

int getroot(int v, int ti) {
    int i;
    for (i = 18; i >= 0; --i) {
        if (parent[v][i] && endtime[parent[v][i]] >= ti) v = parent[v][i];
    }
    return v;
}

void addedge(int u, int v) {
    g[u].push_back(v);
    // cout << "addedge " << u << " -> " << v << endl;
}

int main() {
    int i;
    scanf("%d%d%d", &n, &m, &Q);
    for (i = 0 ; i < MAX_SIZE; ++i) {
        endtime[i] = MAX_SIZE;
        f[i] = i;         
    }

    for (i = 1; i <= n; ++i) {
        root.insert(i);
        scanf("%d", &p[i]);
    }
    for (i = 1; i <= m; ++i) scanf("%d%d", &edg[i].first.first, &edg[i].first.second);
    for (i = 1; i <= Q; ++i) {
        scanf("%d%d", &q[i].first, &q[i].second);
        if (q[i].first == 2) {
            edg[q[i].second].second = i;
        }
    }

    for (i = 1; i <= m; ++i) {
        if (edg[i].second == 0) {
            int u = find(edg[i].first.first), v = find(edg[i].first.second);
            if (u != v) {
                root.erase(u), root.erase(v);
                root.insert(i + n);
                addedge(i + n, v), addedge(i + n, u);
                parent[u][0] = parent[v][0] = i + n;
                f[u] = f[v] = i + n;
            }
        }
    }

    for (i = Q; i >= 1; --i) {
        if (q[i].first == 2) {
            int u = find(edg[q[i].second].first.first), v = find(edg[q[i].second].first.second);
            if (u != v) {
                root.erase(u), root.erase(v), root.insert(q[i].second + n);
                // g[q[i].second + n].push_back(u), g[q[i].second + n].push_back(v);
                addedge(q[i].second + n, u), addedge(q[i].second + n, v);
                parent[u][0] = parent[v][0] = q[i].second + n;
                f[u] = f[v] = q[i].second + n;
                endtime[q[i].second + n] = i;
            }
        }
    }

    for (auto v : root) {
        dfs(v);
    }

    preprocess();/*
    for (i = 1; i <= cnt; ++i) {
        printf("id= %d, v= %d , endtime= %d\n", i, rid[i], endtime[rid[i]]);
    }*/
    build(1, cnt, 1);
    for (i = 1; i <= Q; ++i) {
        if (q[i].first == 1) {
            int v = getroot(q[i].second, i);
        //    cout << "root= " << v << endl;
            auto ret = query(id[v], id[v] + sz[v] - 1, 1, cnt, 1);
            printf("%d\n", ret.first);
            update(ret.second, 1, cnt, 1);
        }
    }
    return 0;
}