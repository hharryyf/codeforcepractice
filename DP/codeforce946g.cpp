#include <bits/stdc++.h>
#define MAX_SIZE 1048597
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;

int tree[MAX_SIZE][2];

void update(int pt, int l, int r, int index, int val, int dim) {
    if (l > r || pt < l || pt > r) return;
    if (l == r) {
        tree[index][dim] = max(tree[index][dim], val);
        return;
    }

    if (pt <= MID) {
        update(pt, l, MID, LEFT, val, dim);
    } else {
        update(pt, MID + 1, r, RIGHT, val, dim);
    }

    tree[index][dim] = max(tree[LEFT][dim], tree[RIGHT][dim]);
}

int query(int start, int end, int l, int r, int index, int dim) {
    if (start > end || l > r || start > r || l > end) return 0;
    if (start <= l && r <= end) return tree[index][dim];
    if (end <= MID) return query(start, end, l, MID, LEFT, dim);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT, dim);
    return max(query(start, end, l, MID, LEFT, dim), query(start, end, MID + 1, r, RIGHT, dim));
}

int dp[MAX_SIZE][2];
int tmp[MAX_SIZE];
int a[MAX_SIZE];
vector<int> disc;
int n;

int main() {
    int i;
    for (i = 0; i < MAX_SIZE; ++i) {
        dp[i][0] = dp[i][1] = -MAX_SIZE;
        tree[i][0] = tree[i][1] = -MAX_SIZE;
    }

    scanf("%d", &n);
    a[0] = tmp[0] = -2000000000;
    a[n + 1] = tmp[2 * n + 1] = 2000000000;
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        tmp[2 * i - 1] = a[i] - i;
        tmp[2 * i] = a[i] - 1 + 1;
        a[i] -= i;
    }

    sort(tmp, tmp + 2 + 2 * n);
    for (i = 0; i <= 2 * n + 1; ++i) {
        if (i == 0 || tmp[i] != tmp[i-1]) {
            disc.push_back(tmp[i]);
        }
    }

    dp[0][0] = dp[0][1] = 0;
    int sz = disc.size(), ans = 0;
    for (i = 0 ; i <= n; ++i) {
        int idx = upper_bound(disc.begin(), disc.end(), a[i]) - disc.begin();
        ans = max(ans, tree[1][0] + 1);
        update(idx, 1, sz, 1, dp[i][0], 0);
        update(idx, 1, sz, 1, dp[i][1], 1);
        idx = upper_bound(disc.begin(), disc.end(), a[i+1]) - disc.begin();
        dp[i+1][0] = max(dp[i+1][0], query(1, idx, 1, sz, 1, 0) + 1);
        dp[i+1][1] = max(dp[i+1][1], query(1, idx, 1, sz, 1, 1) + 1);
        idx = upper_bound(disc.begin(), disc.end(), a[i + 1] + 1) - disc.begin();
        dp[i+1][1] = max(dp[i+1][1], query(1, idx, 1, sz, 1, 0) + 1);
        idx = upper_bound(disc.begin(), disc.end(), a[i + 2] + 1) - disc.begin();
        dp[i + 2][1] = max(dp[i+2][1], query(1, idx, 1, sz, 1, 0) + 2);
        ans = max(ans, dp[i][0]);
        ans = max(ans, dp[i][1]);
    }

    printf("%d\n", n - ans);
    return 0;
}