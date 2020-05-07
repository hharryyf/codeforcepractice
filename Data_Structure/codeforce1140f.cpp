#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 300011
#define MID ((l+r)>>1)
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)
using namespace std;
typedef long long ll;

struct qrs {
    // y coordinate, join fa and fb
    int y, fa, fb, tp;
};

ll ans[MAX_SIZE];
// the size is recorded at the back
vector<int> sz[MAX_SIZE];
// the parent all nodes at the moment
// is the back element
vector<int> f[MAX_SIZE];
// the height of each component
vector<int> height[MAX_SIZE];
// the x coordinate of all y
vector<int> xcoord[MAX_SIZE];
// the range tree for all queries
vector<pair<int, int>> tree[MAX_SIZE << 2];
// the history stack
vector<qrs> history;
int Q;
map<int, int> mp[MAX_SIZE];
ll curr = 0;

void preprocess() {
    int i;
    for (i = 0 ; i < MAX_SIZE; ++i) {
        f[i].push_back(i);
        sz[i].push_back(1);
        height[i].push_back(0);
    }
}

int find(int x) {
    // cout << "find " << x << endl;
    if (f[x].back() == x) return x;
    return find(f[x].back());
}

void cancelpre() {
    if (history.empty()) return;
    auto q = history.back();
    history.pop_back();
    if (q.tp == 0) {
        curr -= sz[q.fa].back();
        height[q.fa].pop_back();
        xcoord[q.y].pop_back();
    } else if (q.tp == 1) {
        xcoord[q.y].pop_back();
    } else {
        // cancel to query of joining q.fa to q.fb
        curr -= 1ll * sz[q.fb].back() * height[q.fb].back();
        sz[q.fb].pop_back();
        height[q.fb].pop_back();
        xcoord[q.y].pop_back();
        f[q.fa].pop_back();
        curr += 1ll * sz[q.fa].back() * height[q.fa].back();
        curr += 1ll * sz[q.fb].back() * height[q.fb].back();
    }
}

void addpoint(int x, int y) {
    // cout << "add point " << x << " " << y << endl;
    int fx = find(x);
    // cout << fx << endl;
    if (xcoord[y].empty()) {
        // cout << "case 1" << endl;
        // this is a new y coorinate for the current component
        // we add 1 to the height of the current component
        height[fx].push_back(height[fx].back() + 1);
        xcoord[y].push_back(x);
        history.push_back(qrs{y, fx, fx, 0});
        curr += sz[fx].back();
        return;
    }

    int fy = find(xcoord[y].back());
    // the added point is in the same connected component of the current point
    if (fx == fy) {
        // cout << "case 2" << endl;
        xcoord[y].push_back(x);
        history.push_back(qrs{y, fx, fx, 1});
        return;
    }
    // cout << "case 3" << endl;
    // the hardest case, the added point is not in the same connect component
    xcoord[y].push_back(x);
    int sz1 = sz[fx].back(), sz2 = sz[fy].back();
    curr -= 1ll * sz1 * height[fx].back();
    curr -= 1ll * sz2 * height[fy].back();
    if (sz1 > sz2) {
        sz[fx].push_back(sz1 + sz2);
        f[fy].push_back(fx);
        height[fx].push_back(height[fx].back() + height[fy].back());
        curr += 1ll * (sz1 + sz2) * height[fx].back();
        // join fy to fx
        history.push_back(qrs{y, fy, fx, 2});
    } else {
        sz[fy].push_back(sz1 + sz2);
        f[fx].push_back(fy);
        height[fy].push_back(height[fx].back() + height[fy].back());
        curr += 1ll * (sz1 + sz2) * height[fy].back();
        // join fx to fy
        history.push_back(qrs{y, fx, fy, 2});
    }
}

void update(int start, int end, int l, int r, int index, int x, int y) {
    if (start > end || l > end || start > r || l > r) return;
    if (start <= l && r <= end) {
        tree[index].emplace_back(x, y);
        return;
    }

    if (end <= MID) {
        update(start, end, l, MID, LEFT, x, y);
    } else if (start >= MID + 1) {
        update(start, end, MID + 1, r, RIGHT, x, y);
    } else {
        update(start, end, l, MID, LEFT, x, y);
        update(start, end, MID + 1, r, RIGHT, x, y);
    }
}

void dfs(int l, int r, int index) {
    int i;
    // cout << l << " " << r <<  " ok " << endl;
    if (l > r) return;
    for (auto p : tree[index]) {
        addpoint(p.first, p.second);
    }
    // cout << "finish add " << l << " " << r << endl;
    if (l == r) {
        ans[l] = curr;
        for (i = 0 ; i < (int) tree[index].size(); ++i) {
            cancelpre();
        }
        return;    
    }

    dfs(l, MID, LEFT);
    dfs(MID + 1, r, RIGHT);
    for (i = 0 ; i < (int) tree[index].size(); ++i) {
        cancelpre();
    } 
}

int main() {
    int i;
    scanf("%d", &Q);
    preprocess();
    for (i = 1; i <= Q; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        int z = mp[x][y];
        if (z != 0) {
            mp[x].erase(y);
            update(z, i - 1, 1, Q, 1, x, y);
            // cout << "insert " << x << " " << y << " to " << z << " " << i - 1 << endl;
        } else {
            mp[x][y] = i;
        }
    }

    for (i = 1; i < MAX_SIZE; ++i) {
        if (mp[i].empty()) continue;
        auto iter = mp[i].begin();
        while (iter != mp[i].end()) {
            if (iter->second != 0) {
                update(iter->second, Q, 1, Q, 1, i, iter->first);
                // cout << "insert " << i << " " << iter->first << " to " << iter->second << " " << Q << endl;
            }
            iter++;
        }
    }
    
    dfs(1, Q, 1);
    for (i = 1; i <= Q; ++i) {
        printf("%I64d ", ans[i]);
    }
    printf("\n");
    return 0;
}