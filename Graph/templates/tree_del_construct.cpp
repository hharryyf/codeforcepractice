#include <bits/stdc++.h>
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
#define MID ((l+r)>>1)
#define MAX_SIZE 524292
using namespace std;

int f[MAX_SIZE];
int idx[MAX_SIZE >> 1];
int visited[MAX_SIZE];

int find(int x) {
    if (x == f[x]) return x;
    return f[x] = find(f[x]);
}
 
void unionset(int x, int y) {
    int a = find(x), b = find(y);
    f[a] = b;
}
 
void build(int l, int r, int index) {
    if (l > r) return;
    f[index] = index;
    if (l == r) {
        idx[l] = index;
        return;
    }
    
    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
}

void pushdown(int l, int r, int index) {
    if (l > r || visited[index]) return;
    visited[index] = true;
    if (l == r) return;
    unionset(index, LEFT);
    unionset(index, RIGHT);
    
    pushdown(l, MID, LEFT);
    pushdown(MID + 1, r, RIGHT);
}

vector<int> g[MAX_SIZE >> 1];

void update(int start, int end, int l, int r, int index, int pt) {
    if (start > end || l > r) return;
    if (start <= l && r <= end) {
        if (find(idx[pt]) != find(index)) {
            for (int i = l; i <= r; ++i) {
                if (find(idx[pt]) != find(idx[i])) {
                    g[pt].push_back(i);
                    g[i].push_back(pt);
                    unionset(idx[pt], idx[i]);
                }
            }
        }
        unionset(idx[pt], index);
        pushdown(l, r, index);
        return;
    }
    
    if (end <= MID) {
        update(start, end, l, MID, LEFT, pt);
    } else if (start >= MID + 1) {
        update(start, end, MID + 1, r, RIGHT, pt);
    } else {
        update(start, end, l, MID, LEFT, pt);
        update(start, end, MID + 1, r, RIGHT, pt);
    }
}

void init() {
    int i;
    for (i = 0 ; i < MAX_SIZE; ++i) {
        f[i] = i, visited[i] = 0;
    }
}

int N;
vector<int> add[MAX_SIZE >> 1], del[MAX_SIZE >> 1];
char ch[4];
int color[MAX_SIZE];

void dfs(int v, int pre, int d) {
    color[v] = d % 2 == 0 ? 2 : 1;
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs(nv, v, d + 1);
        }
    }
}

int main() {
    int i, j;
    init();
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        int d;
        scanf("%s%d", ch, &d);
        if (ch[0] == 'C') {
            while (d-- > 0) {
                int v;
                scanf("%d", &v);
                add[i].push_back(v);
            }
        } else {
            while (d-- > 0) {
                int v;
                scanf("%d", &v);
                del[i].push_back(v);
            }
            del[i].push_back(i);
        }
    }

    build(1, N, 1);
    for (i = 1; i <= N; ++i) {
        bool hasone = false;
        sort(add[i].begin(), add[i].end());
        sort(del[i].begin(), del[i].end());
        if (del[i].empty()) {
            for (auto v : add[i]) {
                hasone = true;
                update(v, v, 1, N, 1, i);
            }
        } else {
            for (j = 0 ; j < (int) del[i].size(); ++j) {
                if (j == 0) {
                    if (del[i][j] - 1 >= 1) {
                        update(1, del[i][j] - 1, 1, N, 1, i);
                        hasone = true;
                    }
                } else {
                    if (del[i][j] - 1 >= del[i][j-1] + 1) {
                        update(del[i][j-1] + 1, del[i][j] - 1, 1, N, 1, i);
                        hasone = true;
                    }
                }
            }

            if (del[i].back() + 1 <= N) {
                update(del[i].back() + 1, N, 1, N, 1, i);
                hasone = true;
            }
        }

        if (!hasone) {
            printf("Impossible");
            return 0;
        }
    }

    for (i = 1; i <= N; ++i) {
        if (color[i] == 0) {
            dfs(i, 0, 0);
        }
    }

    for (i = 1; i <= N; ++i) {
        if (color[i] == 1) {
            printf("S");
        } else {
            printf("V");
        }
    }
    return 0;
}