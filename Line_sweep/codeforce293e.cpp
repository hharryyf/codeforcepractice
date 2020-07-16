#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("-funroll-loops")
#include <bits/stdc++.h>
#define MAX_SIZE 100111
using namespace std;
typedef long long ll;

struct BIT {
    int n;
    int tree[MAX_SIZE];
    void init(int n) {
        this->n = n;
    }

    int shift(int x) {
        return x & (-x);
    }

    void update(int x, int val) {
        x++;
        if (x <= 0) return;
        while (x <= n) {
            tree[x] += val;
            x += shift(x);
        }
    }

    int query(int x) {
        x++;
        int ret = 0;
        while (x > 0) {
            ret += tree[x];
            x -= shift(x);
        }

        return ret;
    }
};

BIT t;
// (to, w)
vector<pair<int, int>> g[MAX_SIZE];
int N, L, W;
int sz[MAX_SIZE];
int parent[MAX_SIZE];
int visited[MAX_SIZE];
ll ans = 0;

void dfs1(int v) {
    sz[v] = 1;
    for (auto ne : g[v]) {
        int nv = ne.first;
        if (nv != parent[v]) {
            parent[nv] = v;
            dfs1(nv);
            sz[v] += sz[nv];
        }
    }
}

int getroot(int _u, int psz) {
    int root = _u;
    while (true) {
        int nu = 0;
        for (auto ne : g[root]) {
            int nv = ne.first;
            if (visited[nv] || nv == parent[root]) continue;
            if (sz[nv] >= psz / 2) nu = nv;
        }

        if (psz - 1 - sz[root] > psz / 2 && parent[root] != 0 && !visited[parent[root]]) {
            nu = parent[root];
        }

        if (nu != 0) {
            root = nu;
        } else {
            break;
        }
    }
    return root;
}

void fixsize(int root) {
    int v = parent[root];
    while (v != 0 && !visited[v]) {
        sz[v] -= 1 + sz[root];
        v = parent[v];
    }
}


vector<pair<pair<int, int>, int>> q;
vector<int> history;

void dfs2(int root, int pre, int l, int w) {
    q.push_back(make_pair(make_pair(w, 0), l));
    q.push_back(make_pair(make_pair(W - w, 1), L - l));
    for (auto ne : g[root]) {
        int nv = ne.first;
        if (nv != pre && !visited[nv]) {
            dfs2(nv, root, l + 1, w + ne.second);
        }
    }
}

ll solve(int root, int pre, int l, int w) {
    ll curr = 0;
    // the problem solving part, we get the answer for the root
    dfs2(root, pre, l, w);
    sort(q.begin(), q.end());
    for (auto it : q) {
        
        if (it.first.second == 1) {
            curr += t.query(it.second);
            // cout << "query " << it.second << endl;
        } else {
            t.update(it.second, 1);
            history.push_back(it.second);
            // cout << "update " << it.second << endl;
        }
    }

    while (!history.empty()) {
        t.update(history.back(), -1);
        history.pop_back();
    }

    q.clear();

    // cout << "root " << root << " " << curr << endl;
    return curr;
}

void CD(int _u, int psz, int pre) {
    int root = getroot(_u, psz);
    fixsize(root);
    ll curr = solve(root, pre, 0, 0);
    curr--;
    for (auto ne : g[root]) {
        int nv = ne.first;
        if (visited[nv]) continue;
        //cout << "eliminate " << root << endl;
        curr -= solve(nv, root, 1, ne.second);
    }

    ans += curr / 2;
    visited[root] = 1;
    for (auto ne : g[root]) {
        int nv = ne.first;
        if (visited[nv]) continue;
        int V2 = 1 + sz[nv];
        if (nv == parent[root]) V2 = psz - 1 - sz[root];
        CD(nv, V2, root);
    }
}

int main() {
    int i;
    scanf("%d%d%d", &N, &L, &W);
    t.init(N+1);
    for (i = 1 ; i <= N - 1; ++i) {
        int u, w;
        scanf("%d%d", &u, &w);
        g[i+1].emplace_back(u, w);
        g[u].emplace_back(i+1, w);
    }

    dfs1(1);
    CD(1, sz[1], 0);
    printf("%I64d\n", ans);
    return 0;
}