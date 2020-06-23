#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

unordered_map<int, int> f, sz, val;

pair<int, int> find(int x) {
    if (f.find(x) == f.end()) return make_pair(x, val[x]);
    auto p = find(f[x]);
    return make_pair(p.first, p.second ^ val[x]);
}

// join x, y with (x ^ y = v)
void unionset(int x, int y, int v) {
    auto p1 = find(x), p2 = find(y);
    if (p1.first == p2.first) return;
    if (sz[p1.first] == 0) sz[p1.first] = 1;
    if (sz[p2.first] == 0) sz[p2.first] = 1;
    if (sz[p1.first] < sz[p2.first]) {
        sz[p2.first] += sz[p1.first];
        f[p1.first] = p2.first;
        val[p1.first] ^= (v ^ p1.second ^ p2.second);
    } else {
        sz[p1.first] += sz[p2.first];
        f[p2.first] = p1.first;
        val[p2.first] ^= (v ^ p1.second ^ p2.second);
    }
}

int main() {
    int q, last = 0;

    scanf("%d", &q);
    while (q-- > 0) {
        int tp, l, r, x;
        scanf("%d", &tp);
        if (tp == 1) {
            scanf("%d%d%d", &l, &r, &x);
            l ^= last, r ^= last, x ^= last;
            l++, r++;
            if (l > r) swap(l, r);
            unionset(l - 1, r, x);
        } else {
            scanf("%d%d", &l, &r);
            l ^= last, r ^= last;
            l++, r++;
            if (l > r) swap(l, r);
            auto p1 = find(l - 1), p2 = find(r);
            if (p1.first != p2.first) {
                printf("%d\n", -1);
                last = 1;
            } else {
                last = p1.second ^ p2.second;
                printf("%d\n", last);
            }
        }
    }
    return 0;
}