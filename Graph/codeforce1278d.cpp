#include <bits/stdc++.h>
#define MAX_SIZE 500011
#define INF 1000000000
using namespace std;

static bool cmp(const pair<int, int> &a, const pair<int, int> &b) {
    return a.second < b.second;
}

pair<int, int> itv[MAX_SIZE];
int f[MAX_SIZE];

int tree[MAX_SIZE * 4];
int n;

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index] = itv[l].first;
        return;
    }
    
    int mid = l + (r - l) / 2;
    build(l, mid, index * 2);
    build(mid + 1, r, index * 2 + 1);
    tree[index] = min(tree[index * 2], tree[index * 2 + 1]);
}
// return the pos and range min of [start, end]
pair<int, int> query(int start, int end, int l, int r, int index) {
    if (l > r || start > end || l > end || start > r) return make_pair(INF, INF);
    int mid = l + (r - l) / 2;
    if (start <= l && r <= end) {
        if (l == r) {
            return make_pair(tree[index], l);
        }
        
        if (tree[index * 2] <= tree[index * 2 + 1]) {
            return query(start, end, l, mid, index * 2);
        }
        return query(start, end, mid + 1, r, index * 2 + 1);
    }
    
    if (end <= mid) {
         return query(start, end, l, mid, index * 2);
    }
    
    if (start >= mid + 1) {
        return query(start, end, mid + 1, r, index * 2 + 1);
    }
    
    return min(query(start, end, l, mid, index * 2), 
               query(start, end, mid + 1, r, index * 2 + 1));
}

void update(int pos, int l, int r, int index, int val) {
    if (l > r) return;
    if (pos < l || pos > r) return;
    if (l == r && l == pos) {
        tree[index] = val;
        return;
    }
    
    int mid = l + (r - l) / 2;
    if (pos <= mid) {
        update(pos, l, mid, index * 2, val);
    } else {
        update(pos, mid + 1, r, index * 2 + 1, val);
    }
    
    tree[index] = min(tree[index * 2], tree[index * 2 + 1]);
}

void preprocess() {
    int i;
    for (i = 0 ; i < MAX_SIZE; i++) f[i] = i;
}

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

int getindex(int num) {
    int low = 0, high = n - 1;
    int ans = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (itv[mid].second >= num) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    
    return ans;
}

int main() {
    int i;
    preprocess();
    scanf("%d", &n);
    
    for (i = 0 ; i < n; i++) {
        scanf("%d%d", &itv[i].first, &itv[i].second);
    }
    sort(itv, itv + n, cmp);
    build(0, n - 1, 1);
    for (i = 0 ; i < n; i++) {
        unordered_set<int> visited;
        while (true) {
            auto p = query(getindex(itv[i].first), i - 1, 0, n - 1, 1);
            if (p.first > itv[i].first) {
                break;
            }
            update(p.second, 0, n - 1, 1, INF);
            visited.insert(p.second);
            int x = find(p.second), y = find(i);
            if (x == y) {
                printf("NO\n");
                return 0;
            }
            f[x] = y;
        }
        
        for (auto v : visited) {
            update(v, 0, n - 1, 1, itv[v].first);
        }
    }
    
    int curr = find(0);
    for (i = 0 ; i < n; i++) {
        if (find(i) != curr) {
            printf("NO\n");
            return 0;
        }
    }
    
    printf("YES\n");
    return 0;
}
