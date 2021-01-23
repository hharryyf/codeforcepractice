#include <bits/stdc++.h>
#define MAX_SIZE 1048597
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;
struct rangesumtree {
    int val, lz;
    struct segt {
        int val, lz;
    };
    segt tree[MAX_SIZE];

    void pushdown(int l, int r, int index) {
        if (l > r) return;
        if (tree[index].lz != 0) {
            if (l != r) {
                tree[LEFT].lz += tree[index].lz;
                tree[RIGHT].lz += tree[index].lz;
                tree[LEFT].val += tree[index].lz;
                tree[RIGHT].val += tree[index].lz;
                tree[LEFT].lz %= 256;
                tree[RIGHT].lz %= 256;
                tree[LEFT].val %= 256;
                tree[RIGHT].val %= 256;
            }
            tree[index].lz = 0;
        }
    }

    void update(int start, int end, int l, int r, int index, int val) {
        if (start > end || l > r || start > r || l > end) return;
        pushdown(l, r, index);
        if (start <= l && r <= end) {
            tree[index].lz += val;
            tree[index].val += val;
            tree[index].val %= 256;
            tree[index].lz %= 256;
            return;
        }

        if (end <= MID) {
            update(start, end, l, MID, LEFT, val);
        } else if (start >= MID + 1) {
            update(start, end, MID + 1, r, RIGHT, val);
        } else {
            update(start, end, l, MID, LEFT, val);
            update(start, end, MID + 1, r, RIGHT, val);
        }
        tree[index].val = min(tree[LEFT].val, tree[RIGHT].val);
    }

    int query(int pt, int l, int r, int index) {
        if (pt < l || pt > r || l > r) return -1;
        pushdown(l, r, index);
        if (l == r) return tree[index].val;
        if (pt <= MID) return query(pt, l, MID, LEFT);
        return query(pt, MID + 1, r, RIGHT);
    }
} t1;

struct rangesettree {
    struct segt {
        pair<int, pair<int, int>> val;
        pair<int, pair<int, int>> lz;
    };
    segt tree[MAX_SIZE];

    void pushdown(int l, int r, int index) {
        if (l > r) return;
        if (tree[index].lz != make_pair(0, make_pair(0, 0))) {
            if (l != r) {
                tree[LEFT].lz = tree[RIGHT].lz = tree[LEFT].val = tree[RIGHT].val = tree[index].lz;
            }
            tree[index].lz = {0, {0, 0}};
        }
    }

    void update(int start, int end, int l, int r, int index, pair<int, pair<int, int>> val) {
        if (start > end || l > r || start > r || l > end) return;
        pushdown(l, r, index);
        if (start <= l && r <= end) {
            tree[index].lz = val;
            tree[index].val = val;
            return;
        }

        if (end <= MID) {
            update(start, end, l, MID, LEFT, val);
        } else if (start >= MID + 1) {
            update(start, end, MID + 1, r, RIGHT, val);
        } else {
            update(start, end, l, MID, LEFT, val);
            update(start, end, MID + 1, r, RIGHT, val);
        }
        tree[index].val = min(tree[LEFT].val, tree[RIGHT].val);
    }

    pair<int, pair<int, int>> query(int pt, int l, int r, int index) {
        if (pt < l || pt > r || l > r) return {0, {0,0}};
        pushdown(l, r, index);
        if (l == r) return tree[index].val;
        if (pt <= MID) return query(pt, l, MID, LEFT);
        return query(pt, MID + 1, r, RIGHT);
    }
} t2;

struct qrs {
    // operation type 0: increment [l, r] by v
    // operation type 1: query point l store it in id
    // version means the tree version for our query
    // if version = 0 means we are getting 0  
    int tp, id, l, r, version;
    bool operator < (qrs other) const {
        if (version != other.version) {
            return version < other.version;
        }
        return tp < other.tp;
    } 
};

int ans[MAX_SIZE];
int sz[MAX_SIZE];
int N, M, Q;
vector<int> g[MAX_SIZE >> 1];
int vid[MAX_SIZE], ivid[MAX_SIZE];
int ok[MAX_SIZE];
int getindex(int cid, int idx) {
    return sz[cid - 1] + idx;
}

int getsize(int id) {
    return sz[id] - sz[id-1];
}

vector<qrs> evt;

int main() {
    int i;
    scanf("%d%d%d", &N, &M, &Q);
    for (i = 1; i <= M; ++i) {
        scanf("%d", &sz[i]);
        sz[i] += sz[i-1];
        int v = sz[i] - sz[i-1];
        g[i].push_back(0);
        while (v-- > 0) {
            int u;
            scanf("%d", &u);
            g[i].push_back(u);
        }
    }

    for (i = 1; i <= Q; ++i) {
        int tp;
        scanf("%d", &tp);
        // int tp, id, l, r, version;
        if (tp == 1) {
            int id, pos;
            scanf("%d%d", &id, &pos);
            t2.update(pos, pos + getsize(id) - 1, 1, N, 1, make_pair(vid[id], make_pair(id, pos)));

        } else if (tp == 2) {
            int pos;
            ok[i] = 1;
            scanf("%d", &pos);
            auto v = t2.query(pos, 1, N, 1);
            if (v.first == 0 && v.second.first == 0 && v.second.second == 0) {
                evt.push_back(qrs{1, i, 0, 0, -1});
            } else {
                // (version , starting position)
                // pos - v.second + 1
                evt.push_back(qrs{1, i, v.second.first, pos - v.second.second + 1, v.first});
                // cout << "query " << ivid[v.first] << " pos= " << pos - v.second + 1 << endl;
            }
        } else {
            int id, l, r;
            scanf("%d%d%d", &id, &l, &r);
            evt.push_back(qrs{0, i, getindex(id, l), getindex(id, r), i});
            vid[id] = i;
        }
    }

    std::sort(evt.begin(), evt.end());
    for (auto e : evt) {
        // cout << "start " << e.version << endl;
        // cout << "id= " << e.id << " l=" << e.l << " r=" << e.r << " tp=" << e.tp << " vs=" << e.version << endl;
        if (e.tp == 0) {
            t1.update(e.l, e.r, 1, sz[M], 1, 1);
        } else {
            
            if (e.version == -1) {
                ans[e.id] = 0;
            } else {
                // cout << "queryindex= " << getindex(e.l, e.r) << endl;
                ans[e.id] = t1.query(getindex(e.l, e.r), 1, sz[M], 1) + g[e.l][e.r];
                ans[e.id] %= 256;
            }
        }

        // cout << "end " << e.version << endl;
    }

    for (i = 1; i <= Q; ++i) {
        if (ok[i]) {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}
