#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;
// all nodes that are connected to node[i] with color j
map<int, vector<int>> color[MAX_SIZE];
set<int> st[MAX_SIZE];
int f[MAX_SIZE];

void init() {
    int i;
    for (i = 0 ; i < MAX_SIZE; ++i) f[i] = i;
}

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    if (st[x].size() > st[y].size()) swap(x, y);
    for (auto v : st[x]) {
        st[y].insert(v);
    }
    f[x] = y;
}
// connect x, y with an edge of color c
void connect(int x, int y, int c) {
    st[find(x)].insert(y);
    st[find(y)].insert(x);
    color[x][c].push_back(y);
    unionset(y, color[x][c][0]);
    color[y][c].push_back(x);
    unionset(x, color[y][c][0]);
}

char ch[4];

int main() {
    int n, m, c, q;
    scanf("%d%d%d%d", &n, &m, &c, &q);
    init();
    while (m-- > 0) {
        int v1, v2;
        scanf("%d%d%d", &v1, &v2, &c);
        connect(v1, v2, c);
    }

    while (q-- > 0) {
        int v1, v2;
        scanf("%s%d%d", ch, &v1, &v2);
        if (ch[0] == '?') {
            printf("%s\n", (find(v1) == find(v2) || st[find(v1)].find(v2) != st[find(v1)].end()) ? "Yes" : "No");
        } else {
            scanf("%d", &c);
            connect(v1, v2, c);
        }
    }
    return 0;
}