#include <bits/stdc++.h>
#define MAX_SIZE 524312
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;
const int inf = 1e8;
int tree[MAX_SIZE], a[MAX_SIZE];
vector<int> g[200011];
int N, K;

void update(int pt, int l, int r, int index) {
    if (pt < l || pt > r || l > r) return;
    if (l == r) {
        tree[index] = inf;
        return;
    }

    if (pt <= MID) {
        update(pt, l, MID, LEFT);
    } else {
        update(pt, MID + 1, r, RIGHT);
    }

    tree[index] = min(tree[LEFT], tree[RIGHT]);
}
// (number, index)
pair<int, int> query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return make_pair(inf, inf);
    if (l == r) return make_pair(tree[index], l);
    if (start <= l && r <= end) {
        if (tree[LEFT] <= tree[RIGHT]) return query(start, end, l, MID, LEFT);
        return query(start, end, MID + 1, r, RIGHT);
    }

    if (end <= MID) return query(start, end, l, MID, LEFT);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
    return min(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index] = a[l];
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index] = min(tree[LEFT], tree[RIGHT]);
}

int main() {
    int i;
    scanf("%d%d", &N, &K);
    set<int> s;
    for (i = 1; i <= N; ++i) {
        scanf("%d", &a[i]);
        g[a[i]].push_back(i);
    }

    for (i = 1; i <= K; ++i) {
        s.insert(g[i].back());
    }

    build(1, N, 1);
    int L = 1;
    for (i = 1; i <= K; ++i) {
        int R = *s.begin();
        auto p = query(L, R, 1, N, 1);
        printf("%d ", p.first);
        L = p.second + 1;
        s.erase(g[p.first].back());
        for (auto v : g[p.first]) {
            update(v, 1, N, 1);
        }
    }
    return 0;
}