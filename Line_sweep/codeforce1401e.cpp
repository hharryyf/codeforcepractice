#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;
const int up = 1e6;
typedef long long ll;
struct BIT {
    int tree[MAX_SIZE];
    void init() {
        memset(tree, 0, sizeof(tree));
    }

    int shift(int x) {
        return x & (-x);
    }

    void update(int pos, int val) {
        pos++;
        if (pos <= 0) return;
        while (pos <= up + 1) {
            tree[pos] += val;
            pos += shift(pos);
        }
    }

    int query(int pos) {
        pos++;
        int ret = 0;
        while (pos > 0) {
            ret += tree[pos];
            pos -= shift(pos);
        }
        return ret;
    }
};

BIT t;
vector<pair<int, int>> tx[MAX_SIZE];
vector<pair<int, int>> ty[MAX_SIZE];
// hor[y] means all segments at height y
vector<pair<int, int>> hor[MAX_SIZE];
// ver[y] means all vertical segments at x
vector<pair<int, int>> ver[MAX_SIZE];

vector<int> add[MAX_SIZE];
vector<int> del[MAX_SIZE];
vector<pair<int, int>> qrs[MAX_SIZE];

// similar to APIO2017 problem, we use the Euler planer graph formula
// V - E + R = 2
// we need to calculate the number of vertices and the number of edges
// then R = 2 - V + E
// for V it can be solved by line sweep, basically find all the intersecting points
// for E, we can do it segments by segments if both end points are closed then the number
// of added edge is the intersection points - 1, otherwise, if one of the end point is closed
// the edge addition is the number of intersection points
// we should do this for all segments after merging
ll V, E;

void clear() {
    int i;
    t.init();
    for (i = 0 ; i <= up; ++i) {
        add[i].clear();
        del[i].clear();
        qrs[i].clear();
    }
}

void sweep_horizontal() {
    int i;
    for (i = 0 ; i <= up; ++i) {
        for (auto p : hor[i]) {
            qrs[i].push_back(p);
        }

        for (auto p : ver[i]) {
            add[p.first].push_back(i);
            del[p.second].push_back(i);
        }
    }

    for (i = 0; i <= up; ++i) {
        for (auto v : add[i]) {
            t.update(v, 1);
           //  cout << "insert at " << v << " height= " << i << endl;
        }

        for (auto q : qrs[i]) {
            int t1 = t.query(q.second);
            int t2 = t.query(q.first - 1);
            int t3 = t.query(q.first);
            int t4 = t.query(q.second - 1);
            // cout << "query interval " << q.first << " " << q.second << endl;
            int deltaV = t1 - t2 + 2 - (t3 - t2) - (t1 - t4);
            // cout << "deltaV = " << deltaV << endl;
            int deltaE = deltaV - 1; 
            // cout << "deltaE = " << deltaE << endl;
            V += deltaV;
            E += deltaE;
        }

        for (auto v : del[i]) {
            t.update(v, -1);
            // cout << "erase at " << v << " height= " << i << endl;
        }
    }
}

void sweep_vertical() {    
    int i;
    for (i = 0 ; i <= up; ++i) {
        for (auto p : ver[i]) {
            qrs[i].push_back(p);
        }

        for (auto p : hor[i]) {
            add[p.first].push_back(i);
            del[p.second].push_back(i);
        }
    }

    for (i = 0; i <= up; ++i) {
        for (auto v : add[i]) {
            t.update(v, 1);
        }

        for (auto q : qrs[i]) {
            int t1 = t.query(q.second);
            int t2 = t.query(q.first - 1);
            int t3 = t.query(q.first);
            int t4 = t.query(q.second - 1);
            int deltaV = t1 - t2 + 2 - (t3 - t2) - (t1 - t4);
            int deltaE = deltaV - 1; 
            V += 2 - (t3 - t2) - (t1 - t4);
            E += deltaE;
        }

        for (auto v : del[i]) {
            t.update(v, -1);
        }
    }
}

void merge_segments() {
    int i, j;
    for (i = 0 ; i <= up; ++i) {
        sort(tx[i].begin(), tx[i].end());
        sort(ty[i].begin(), ty[i].end());
    }

    for (i = 0; i <= up; ++i) {
        int sz = tx[i].size();
        if (!sz) continue;
        int l = tx[i][0].first, r = tx[i][0].second;
        for (j = 1 ; j < sz; ++j) {
            if (tx[i][j].first <= r) {
                r = max(r, tx[i][j].second);
            } else {
                hor[i].emplace_back(l, r);
                // cout << "add horiaontal [" << l << ", " << r << "] at " << i << endl;
                l = tx[i][j].first, r = tx[i][j].second;
            }
        }
        hor[i].emplace_back(l, r);
        // cout << "add horiaontal [" << l << ", " << r << "] at " << i << endl;
    }

    for (i = 0; i <= up; ++i) {
        int sz = ty[i].size();
        if (!sz) continue;
        int l = ty[i][0].first, r = ty[i][0].second;
        for (j = 1 ; j < sz; ++j) {
            if (ty[i][j].first <= r) {
                r = max(r, ty[i][j].second);
            } else {
                ver[i].emplace_back(l, r);
                l = ty[i][j].first, r = ty[i][j].second;
                // cout << "add vertical [" << l << ", " << r << "] at " << i << endl;
            }
        }
        ver[i].emplace_back(l, r);
        // cout << "add vertical [" << l << ", " << r << "] at " << i << endl;
    }
}

int main() {
    int n, m, i;
    scanf("%d%d", &n, &m);
    tx[up].emplace_back(0, up);
    tx[0].emplace_back(0, up);
    ty[0].emplace_back(0, up);
    ty[up].emplace_back(0, up);
    for (i = 0 ; i < n; ++i) {
        int y, x1, x2;
        scanf("%d%d%d", &y, &x1, &x2);
        tx[y].emplace_back(x1, x2);
    }

    for (i = 0; i < m; ++i) {
        int x, y1, y2;
        scanf("%d%d%d", &x, &y1, &y2);
        ty[x].emplace_back(y1, y2);
    }

    merge_segments();
    sweep_horizontal();
    clear();
    sweep_vertical();
    // cout << V << " " << E << endl;
    printf("%I64d\n", E - V + 1);
    return 0;
}