#include <bits/stdc++.h>
#define MAX_SIZE 500111
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
#define MID ((l+r)>>1)
using namespace std;

int a[MAX_SIZE];
vector<int> pos;
vector<int> tree;
vector<int> disc;
vector<int> tmp;
void update(int pt, int l, int r, int index, int val) {
    if (pt < l || pt > r || l > r) return;
    if (l == r) {
        tree[index] = max(tree[index], val);
        return;
    }

    if (pt <= MID) {
        update(pt, l, MID, LEFT, val);
    } else {
        update(pt, MID + 1, r, RIGHT, val);
    }
    tree[index] = max(tree[LEFT], tree[RIGHT]);
}

int query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return -100000000;
    if (start <= l && r <= end) return tree[index];
    if (end <= MID) return query(start, end, l, MID, LEFT);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
    return max(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT)); 
}

int LIS(vector<int> &arr) {
    int i = 0, sz = arr.size();
    tmp.clear(), disc.clear(), tree.clear();
    vector<int> dp = vector<int>(sz, -100000000);
    tmp = vector<int>(sz, 0);
    tree.clear();
    tree = vector<int>(sz * 4 + 4, -100000000);    
    for (auto v : arr) {
        tmp[i++] = v;
    }

    sort(tmp.begin(), tmp.end());
    for (i = 0 ; i < sz; ++i) {
        if (i == 0 || tmp[i] != tmp[i-1]) {
            disc.push_back(tmp[i]);
        }
    }

    int ds = disc.size();
    for (i = 0 ; i < sz; ++i) {
        int idx = lower_bound(disc.begin(), disc.end(), arr[i]) - disc.begin();
        if (i > 0) {
            dp[i] = 1 + query(0, idx, 0, ds - 1, 1);
        } else {
            dp[i] = 1;
        }
        update(idx, 0, ds - 1, 1, dp[i]);
    }

    return dp[sz - 1];
}

int main() {
    int i, n, k, j;
    scanf("%d%d", &n, &k);
    a[0] = -2000000000, a[n + 1] = 2000000000;
    pos.push_back(0);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        a[i] = a[i] - i;
    }

    for (i = 1; i <= k; ++i) {
        int v;
        scanf("%d", &v);
        pos.push_back(v);
    }

    pos.push_back(n + 1);
    int ans = 0;
    for (i = 0 ; i < (int) pos.size() - 1; ++i) {
        vector<int> curr;
        for (j = pos[i]; j <= pos[i+1]; ++j) {
            curr.push_back(a[j]);
        }

        int ret = LIS(curr);
        // cout << ret << endl;
        if (ret < 2) {
            printf("-1\n");
            return 0;
        }

        ans += pos[i + 1] - pos[i] - ret + 1;
    }

    printf("%d\n", ans);
    return 0;
}