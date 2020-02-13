#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 1048596

using namespace std;
int f[MAX_SIZE];
int idx[MAX_SIZE >> 1];
int visited[MAX_SIZE];

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch>'9' || ch<'0') { if(ch=='-') f=-1; ch=getchar(); }
    while(ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    return x*f;
}

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
    
    int mid = l + (r - l) / 2;
    build(l, mid, index << 1);
    build(mid + 1, r, (index << 1) | 1);
}

void pushdown(int l, int r, int index) {
    if (l > r || visited[index]) return;
    visited[index] = true;
    if (l == r) return;
    int mid = l + (r - l) / 2;
    unionset(index, index << 1);
    unionset(index, (index << 1) | 1);
    
    pushdown(l, mid, index << 1);
    pushdown(mid + 1, r, (index << 1) | 1);
}

// connect pt to all points from start to end
void update(int start, int end, int l, int r, int index, int pt) {
    if (start > end || l > r) return;
    if (start <= l && r <= end) {
        unionset(pt,index);
        pushdown(l, r, index);
        return;
    }
    
    int mid = l + (r - l) / 2;
    if (end <= mid) {
        update(start, end, l, mid, index << 1, pt);
    } else if (start >= mid + 1) {
        update(start, end, mid + 1, r, (index << 1) | 1, pt);
    } else {
        update(start, end, l, mid, index << 1, pt);
        update(start, end, mid + 1, r, (index << 1) | 1, pt);
    }
}

vector<int> g[MAX_SIZE];
vector<int> ans[MAX_SIZE];

int main() {
    int i, n, m, j;
    n = read(), m = read();
    build(1, n, 1);
    for (i = 1; i <= m; i++) {
        int v1, v2;
        v1 = read(), v2 = read();
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }
    for (i = 1; i <= n; i++) {
        sort(g[i].begin(), g[i].end());
        if (g[i].empty()) {
            update(1, n, 1, n, 1, idx[i]);
            break;
        }
        
        for (j = 0 ; j < (int) g[i].size(); j++) {
            if (j == 0) {
                update(1, g[i][j] - 1, 1, n, 1, idx[i]);
            } else {
                update(g[i][j-1] + 1, g[i][j] - 1, 1, n, 1, idx[i]);
            }
        }
        
        update(g[i].back() + 1, n, 1, n, 1, idx[i]);
    }
    
    unordered_set<int> h;
    for (i = 1; i <= n; i++) {
        h.insert(find(idx[i]));
        ans[find(idx[i])].push_back(i);
    }
    
    printf("%d\n", h.size());
    auto iter = h.begin();
    while (iter != h.end()) {
        printf("%d", ans[*iter].size());
        for (auto v : ans[*iter]) {
            printf(" %d", v);
        }
        printf("\n");
        iter++;
    }
    return 0;
}
