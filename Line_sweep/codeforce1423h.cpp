#include <bits/stdc++.h>
#define MAX_SIZE 131092
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;

vector<int> f[MAX_SIZE];
vector<int> sz[MAX_SIZE];
// first -> second
vector<pair<int, int>> op;
// if first = second then it is a query of type 2
vector<pair<int, int>> tree[MAX_SIZE * 8];
// each edge's last occurrence time
map<pair<int, int>, int> mp;
// number of day and the corresponding add queries
vector<pair<pair<int, int>, int>> q[MAX_SIZE];
int ans[MAX_SIZE * 4];
int z[MAX_SIZE * 4];
int ed[MAX_SIZE * 4];

void update(int start, int end, int l, int r, int index, int v1, int v2) {
    if (start > end || l > r || start > r || l > end) return;
    if (start <= l && r <= end) {
        tree[index].emplace_back(v1, v2);
        return;
    }

    if (end <= MID) {
        update(start, end, l, MID, LEFT, v1, v2);
    } else if (start >= MID + 1) {
        update(start, end, MID + 1, r, RIGHT, v1, v2);
    } else {
        update(start, end, l, MID, LEFT, v1, v2);
        update(start, end, MID + 1, r, RIGHT, v1, v2);
    }
}

int find(int x) {
    if (x == f[x].back()) return x;
    return find(f[x].back());
}

void unionset(int v1, int v2) {
    int a = find(v1), b = find(v2);
    if (a == b) {
        op.emplace_back(-1, -1);
        return;
    }

    if (sz[a].back() > sz[b].back()) swap(a, b);
    f[a].push_back(b);
    sz[b].push_back(sz[a].back() + sz[b].back());
    op.emplace_back(a, b);
}

void del() {
    if (op.empty()) return;
    if (op.back().first == -1) {
        op.pop_back();
    } else {
        int v1 = op.back().first, v2 = op.back().second;
        op.pop_back();
        f[v1].pop_back();
        sz[v2].pop_back();
    }
}

void dfs(int l, int r, int index) {
    if (l > r) return;
    int cnt = 0;
    for (auto p : tree[index]) {
        unionset(p.first, p.second);
        ++cnt;
    }

    if (l == r) {
        if (z[l]) {
            ans[l] = sz[find(z[l])].back();
        }
        while (cnt-- > 0) del();
        return;
    }

    dfs(l, MID, LEFT);
    dfs(MID + 1, r, RIGHT);
    while (cnt-- > 0) del();
}

int main() {
    int i, N, Q, K;
    scanf("%d%d%d", &N, &Q, &K);
    for (i = 0 ; i < MAX_SIZE; ++i) {
        f[i].push_back(i);
        sz[i].push_back(1);
    }
    
    int curr = 1;
    for (i = 1; i <= Q; ++i) {
        int tp;
        scanf("%d", &tp);
        if (tp == 3) {
            ++curr;
            ed[curr - 1] = i;
        } else if (tp == 2) {
            scanf("%d", &z[i]);
        } else {
            int v1, v2;
            scanf("%d%d", &v1, &v2);
            if (v1 > v2) swap(v1, v2);
            q[curr].push_back(make_pair(make_pair(v1, v2), i));
        }
    }

    ed[curr] = Q;

    for (i = 1; i <= curr; ++i) {
        int lstquery = i + K - 1 > curr ? Q : ed[i + K - 1];
        for (auto e : q[i]) {
            update(e.second, lstquery, 1, Q, 1, e.first.first, e.first.second);
        }
    }

    dfs(1, Q, 1);

    for (i = 1; i <= Q; ++i) {
        if (ans[i]) {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}