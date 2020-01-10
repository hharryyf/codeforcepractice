#include <bits/stdc++.h>
#define MAX_SIZE 1048596
using namespace std;

struct segt {
    int value;
    int lz;
};

segt tree[MAX_SIZE];

struct pt {
    int x, y;
};

static bool cmp(const pt &a, const pt &b) {
    return a.x < b.x;
}

pt p[MAX_SIZE >> 1];
int tmp[MAX_SIZE >> 1];
vector<int> disc;

int R;
int n;

int getindex(int y) {
    return lower_bound(disc.begin(), disc.end(), y) - disc.begin();
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
    tree[index].value = max(tree[index * 2].value, tree[index * 2 + 1].value);
}

int main() {
    int i, j;
    int ans = 0;
    scanf("%d%d", &n, &R);
    R = R << 1;
    for (i = 0 ; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        p[i].x = x + y;
        p[i].y = y - x;
        tmp[i] = p[i].y;
    }
    
    sort(tmp, tmp + n);
    sort(p, p + n, cmp);
    for (i = 0 ; i < n; i++) {
        if (i == 0 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
    }
    int m = disc.size();
    i = 0, j = 0;
    while (i < n) {
        while (j < n && p[i].x + R >= p[j].x) {
            update(getindex(p[j].y - R), getindex(p[j].y), 0, m - 1, 1, 1);
            j++;
        }
        
        ans = max(ans, tree[1].value);
        
        int curr = p[i].x;
        while (i < n && curr == p[i].x) {
            update(getindex(p[i].y - R), getindex(p[i].y), 0, m - 1, 1, -1);
            i++;
        }
    }
    
    printf("%d\n", ans);
    return 0;
}
