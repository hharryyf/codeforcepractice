#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 300111
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;
typedef long long ll;

// left bound and id
vector<pair<int, int>> q[MAX_SIZE];
int tree[MAX_SIZE << 2];
int ans[MAX_SIZE];
int a[MAX_SIZE];

int query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return 0;
    if (start <= l && r <= end) return tree[index];
    if (end <= MID) {
        return query(start, end, l, MID, LEFT);
    }

    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
    return query(start, end, l, MID, LEFT) + query(start, end, MID + 1, r, RIGHT);
}

void update(int pt, int l, int r, int index, int val) {
    if (pt < l || pt > r || l > r) return;
    if (l == r) {
        tree[index] += val;
        return;
    }

    if (pt <= MID) {
        update(pt, l, MID, LEFT, val);
    } else {
        update(pt, MID + 1, r, RIGHT, val);
    }

    tree[index] = tree[LEFT] + tree[RIGHT];
}

int main() {
    int i, N, Q;
    scanf("%d%d", &N, &Q);
    for (i = 1; i <= N; ++i) scanf("%d", &a[i]);
    for (i = 1; i <= Q; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        // query is [x + 1, N - y]
        q[N - y].emplace_back(x + 1, i);
        // cout << x + 1 << " , " << N - y << endl;
    }

    for (i = 1; i <= N; ++i) {
        if (a[i] <= i) {
            // find the right most index idx such that 
            // sum[idx, i] >= a[i] - i
            int idx = -1, low = 1, high = i;
            while (low <= high) {
                int mid = (low + high) >> 1;
                if (query(mid, i, 1, N, 1) >= i - a[i]) {
                    idx = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            // cout << idx << endl;
            if (idx != -1) {
                update(idx, 1, N, 1, 1);
            }
        }
        
        for (auto p : q[i]) {
            ans[p.second] = query(p.first, i, 1, N, 1);
        }
    }

    for (i = 1; i <= Q; ++i) {
        printf("%d\n", ans[i]);
    }
    return 0;
}