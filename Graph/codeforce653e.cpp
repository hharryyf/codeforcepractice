#include <bits/stdc++.h>
#define MAX_SIZE 1048596
using namespace std;

vector<int> g[MAX_SIZE >> 1];
int f[MAX_SIZE];
// mp[i] stores the index of the ith point
int mp[MAX_SIZE];
bool visited[MAX_SIZE];

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int a, int b) {
    int x = find(a), y = find(b);
    f[x] = y;
}

void preprocess() {
    int i;
    for (i = 0 ; i < MAX_SIZE; i++) f[i] = i;
}

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        mp[l] = index;
        return;
    }
    
    int mid = l + (r - l) / 2;
    build(l, mid, index * 2);
    build(mid + 1, r, index * 2 + 1);
}

void pushdown(int l, int r, int index) {
    if (l > r || visited[index]) return;
    visited[index] = true;
    if (l == r) return;
    unionset(index, index * 2);
    unionset(index, index * 2 + 1);
    int mid = l + (r - l) / 2;
    pushdown(l, mid, index * 2);
    pushdown(mid + 1, r, index * 2 + 1);
}

// join the pos point with [start, end]
void update(int start, int end, int l, int r, int index, int pos) {
    if (start > end || l > r || start > r || l > end) return;
    if (start <= l && r <= end) {
        unionset(mp[pos], index);
        pushdown(l, r, index);
        return;
    }
    
    int mid = l + (r - l) / 2;
    if (end <= mid) {
        update(start, end, l, mid, index * 2, pos);
    } else if (start >= mid + 1) {
        update(start, end, mid + 1, r, index * 2 + 1, pos);
    } else {
        update(start, end, l, mid, index * 2, pos);
        update(start, end, mid + 1, r, index * 2 + 1, pos);
    }
}

int main() {
    preprocess();
    int n, m, i, j, k;
    scanf("%d%d%d", &n, &m, &k);
    build(1, n, 1);
    for (i = 0 ; i < m; i++) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }
    
    for (i = 1; i <= n; i++) {
        sort(g[i].begin(), g[i].end());
    }
    
    for (i = 2; i <= n; i++) {
        if (g[i].size() == 0) {
            update(2, n, 1, n, 1, i);
        } 
        for (j = 0 ; j < g[i].size(); j++) {
            if (j == 0) {
                update(2, g[i][j] - 1, 1, n, 1, i);
            } else {
                update(g[i][j-1] + 1, g[i][j] - 1, 1, n, 1, i);
            }
        }
        
        if (g[i].size() != 0) {
            update(g[i][g[i].size() - 1] + 1, n, 1, n, 1, i);
        }
    }
    
    if (g[1].size() > n - 1 - k) {
        printf("impossible\n");
        return 0;
    }
    
    unordered_set<int> h;
    for (i = 2; i <= n; i++) {
        h.insert(find(mp[i]));
    }
    
    if (h.size() > k) {
        printf("impossible\n");
        return 0;
    }
    
    if (g[1].size() == 0) {
        update(1, n, 1, n, 1, 1);
    } else {
        unordered_set<int> forbi;
        for (auto v : g[1]) forbi.insert(v);
        for (i = 2; i <= n; i++) {
            if (forbi.find(i) == forbi.end()) {
                unionset(mp[1], mp[i]);
            }
        }
    }
    
    int curr = find(mp[1]);
    for (i = 2; i <= n; i++) {
        if (find(mp[i]) != curr) {
            printf("impossible\n");
            return 0;
        }
    }
    
    printf("possible\n");
    return 0;
}
