#include <bits/stdc++.h>
#define MAX_SIZE 262192
using namespace std;

struct segt {
    double value, lz;  
};

segt tree[MAX_SIZE];
map<int, int> mp; 
vector<int> disc;

void build(int l, int r, int index) {
    if (l > r) return;
    tree[index].value = 1.0 * (double) mp[disc[l]];
    tree[index].lz = 1.0;
    if (l == r) return;
    int mid = l + (r - l) / 2;
    build(l, mid, index * 2);
    build(1 + mid, r, index * 2 + 1);
    tree[index].value = tree[index * 2].value + tree[index * 2 + 1].value;
}

void pushdown(int l, int r, int index) {
    if (l > r) return;
    if (l < r) {
        if (tree[index].lz != 1.0) {
            tree[index * 2].lz *= tree[index].lz;
            tree[index * 2 + 1].lz *= tree[index].lz;
            tree[index * 2].value *= tree[index].lz;
            tree[index * 2 + 1].value *= tree[index].lz;
        }
    }
    tree[index].lz = 1.0;
}

void update(int start, int end, int l, int r, int index, double val) {
    if (start > end || l > r) return;
    
    pushdown(l, r, index);
    
    if (start > r || l > end) return;
    if (start <= l && r <= end) {
        tree[index].value *= val;
        tree[index].lz *= val;
        return;
    }
    
    int mid = l + (r - l) / 2;
    update(start, end, l, mid, index * 2, val);
    update(start, end, 1 + mid, r, index * 2 + 1, val);
    tree[index].value = tree[index * 2].value + tree[index * 2 + 1].value;
}

struct qrs {
    int a, h, l, r;  
};

qrs q[MAX_SIZE];
int n, m;
int tmp[MAX_SIZE];

int main() {
    scanf("%d%d", &n, &m);
    int i;
    for (i = 1; i <= n; i++) {
        scanf("%d%d%d%d", &q[i].a, &q[i].h, &q[i].l, &q[i].r);
    }
    
    for (i = 1; i <= m; i++) {
        int v;
        scanf("%d%d", &tmp[i], &v);
        mp[tmp[i]] += v;
    }
    
    sort(tmp + 1, tmp + 1 + m);
    
    for (i = 1; i <= m; i++) {
        if (i == 1 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
    }
    
    int tol = (int) disc.size();
    build(0, tol - 1, 1);
    
    for (i = 1; i <= n; i++) {
        // [x - h, x)
        int l1 = lower_bound(disc.begin(), disc.end(), q[i].a - q[i].h) - disc.begin();
        int l2 = lower_bound(disc.begin(), disc.end(), q[i].a) - disc.begin() - 1;
        update(l1, l2, 0, tol - 1, 1, 0.01 * (100 - q[i].l));
        // (x, x + h]
        int r1 = upper_bound(disc.begin(), disc.end(), q[i].a) - disc.begin();
        int r2 = upper_bound(disc.begin(), disc.end(), q[i].a + q[i].h) - disc.begin() - 1;
        update(r1, r2, 0, tol - 1, 1, 0.01 * (100 - q[i].r));
    }
    printf("%.10lf\n", tree[1].value);
    return 0;
}
