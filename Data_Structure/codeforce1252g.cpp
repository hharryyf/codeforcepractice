#include <bits/stdc++.h>
#define MAX_SIZE 524292
using namespace std;

vector<int> g[MAX_SIZE];

struct segt {
    int value, lz;
};
// tree maintains the total number of people smaller than the person
segt tree[MAX_SIZE];

// p[i] is the initial entry of the tree
int p[MAX_SIZE];

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index].value = p[l];
        return;
    }
    
    int mid = l + (r - l) / 2;
    build(l, mid, index * 2);
    build(mid + 1, r, index * 2 + 1);
    tree[index].value = min(tree[index * 2].value, tree[index * 2 + 1].value);
}

void pushdown(int l, int r, int index) {
    if (l > r) return;
    if (tree[index].lz) {
        if (l != r) {
            tree[index * 2].value += tree[index].lz;
            tree[index * 2 + 1].value += tree[index].lz;
            tree[index * 2].lz += tree[index].lz;
            tree[index * 2 + 1].lz += tree[index].lz;
        }
        tree[index].lz = 0;
    }
}

void update(int start, int end, int l, int r, int index, int val) {
    if (start > end || l > r) return;
    pushdown(l, r, index);
    if (start > r || l > end) return;
    if (start <= l && r <= end) {
        tree[index].value += val;
        tree[index].lz += val;
        return;
    }
    
    int mid = l + (r - l) / 2;
    update(start, end, l, mid, index * 2, val);
    update(start, end, mid + 1, r, index * 2 + 1, val);
    tree[index].value = min(tree[index * 2].value, tree[index * 2 + 1].value);
}
// sm[i] refers to how many small numbers are smaller than the first person
// in the ith update
int sm[MAX_SIZE];

int main() {
    int n, m, q, i, j;
    scanf("%d%d%d", &n, &m, &q);
    int candidate;
    scanf("%d", &candidate);
    for (i = 0; i < n - 1; i++) {
        int v;
        scanf("%d", &v);
        if (v < candidate) {
            p[0]++;
        }
    }
    
    for (i = 1; i <= m; i++) {
        int r;
        scanf("%d", &r);
        for (j = 0; j < r; j++) {
            int v;
            scanf("%d", &v);
            g[i].push_back(v);
            if (v < candidate) {
                sm[i]++;
            }
        }
        
        p[i * 2 - 1] = p[i * 2 - 2] - r;
        p[i * 2] = p[i * 2 - 1] + sm[i];
    }
    
    build(0, 2 * m, 1);
    
    while (q > 0) {
        int x, y, v;
        scanf("%d%d%d", &x, &y, &v);
        int curr = g[x][y-1];
        if (curr < candidate && v > candidate) {
            update(2 * x, 2 * m, 0, 2 * m, 1, -1);
        } else if (curr > candidate && v < candidate) {
            update(2 * x, 2 * m, 0, 2 * m, 1, 1);
        }
        
        g[x][y-1] = v;
        printf("%d\n", (tree[1].value >= 0));
        q--;
    }
    
    return 0;
}
