#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;

int parent[MAX_SIZE][18];
int depth[MAX_SIZE];
int in[MAX_SIZE], out[MAX_SIZE];
int num[MAX_SIZE];
int gen[MAX_SIZE];
int visited[MAX_SIZE];
int id[MAX_SIZE << 1];
int cnt[MAX_SIZE][2];
ll curr = 0;
int block_size = 1;
vector<int> disc;
int tmp[MAX_SIZE];
vector<int> g[MAX_SIZE];

struct qrs {
    int l, r, lca, id;
    bool operator < (qrs other) const {
        int b1 = l / block_size, b2 = other.l / block_size;
        return (b1 ^ b2) ? b1 < b2 : ((b1 & 1) ? r < other.r : r > other.r);
    }
};


qrs q[MAX_SIZE];
int ct = 1;
ll ans[MAX_SIZE];

void dfs(int v, int pre) {
    in[v] = ct;
    id[ct++] = v;
    int i;
    parent[v][0] = pre;
    for (i = 1; i <= 17; ++i) parent[v][i] = parent[parent[v][i-1]][i-1];
    depth[v] = depth[pre] + 1;
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs(nv, v);
        }
    }
    out[v] = ct;
    id[ct++] = v;
}

int LCA(int u, int v) {
    int i;
    if (depth[u] < depth[v]) swap(u, v);
    for (i = 17; i >= 0; --i) {
        if (depth[u] >= (1 << i) + depth[v]) {
            u = parent[u][i];
        }
    }

    if (u == v) return u;
    for (i = 17; i >= 0; --i) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i], v = parent[v][i];
        }
    }
    return parent[u][0];
}

// update the vertex v
void update(int v) {
    // cout << "we update " << v << endl;
    if (visited[v]) {
        curr -= cnt[num[v]][1 ^ gen[v]];
        cnt[num[v]][gen[v]]--;
    } else {
        curr += cnt[num[v]][1 ^ gen[v]];
        cnt[num[v]][gen[v]]++;
    }

    visited[v] ^= 1;
}

int main () {
    int n, i;
    scanf("%d", &n);
    block_size = sqrt(2 * n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &gen[i]);
    }

    for (i = 1; i <= n; ++i) {
        scanf("%d", &num[i]);
        tmp[i] = num[i];
    }

    sort(tmp + 1, tmp + 1 + n);

    for (i = 1; i <= n; ++i) {
        if (i == 1 || tmp[i] != tmp[i-1]) {
            disc.push_back(tmp[i]);
        }
    }

    for (i = 1; i <= n; ++i) {
        num[i] = lower_bound(disc.begin(), disc.end(), num[i]) - disc.begin();
    }

    for (i = 1; i < n; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }

    dfs(1, 0);
    int m;
    scanf("%d", &m);
    for (i = 1; i <= m; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        if (in[v1] > in[v2]) {
            swap(v1, v2);
        }

        q[i].id = i;
        int lca = LCA(v1, v2);
        if (lca == v1) {
            q[i].l = in[v1], q[i].r = in[v2];
        } else {
            q[i].l = out[v1], q[i].r = in[v2];
            q[i].lca = lca;
        }
    }

    sort(q + 1, q + 1 + m);

    int L = 1, R = 0;
    for (i = 1; i <= m; ++i) {
        while (R < q[i].r) update(id[++R]);
        while (R > q[i].r) update(id[R--]);
        while (L < q[i].l) update(id[L++]);
        while (L > q[i].l) update(id[--L]);
        // cout << q[i].l << " " << q[i].r << " " << id[q[i].l] << " " << id[q[i].r] << " " << q[i].lca << endl; 
        if (q[i].lca > 0) update(q[i].lca);
        ans[q[i].id] = curr;
        if (q[i].lca > 0) update(q[i].lca);
        // cout << "finish query " << q[i].id << endl;
    }

    for (i = 1; i <= m; ++i) {
        printf("%I64d\n", ans[i]);
    }
    return 0;
}