#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
#define MAX_SIZE 1048597
using namespace std;

int a[MAX_SIZE], tree[MAX_SIZE], nxt[MAX_SIZE];
int pos[MAX_SIZE], pre[MAX_SIZE], dp[MAX_SIZE], tmp[MAX_SIZE];
int trans[MAX_SIZE][4];
vector<int> occ[MAX_SIZE];
vector<int> disc;
int N;

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

int query(int start, int end, int l, int r, int index, int val) {
    if (start > end || l > r || start > r || l > end) return 0;
    if (tree[index] <= val) return 0;
    if (l == r) return l;
    if (start <= l && r <= end) {
        if (tree[RIGHT] > val) return query(start, end, MID + 1, r, RIGHT, val);
        return query(start, end, l, MID, LEFT, val);
    }

    if (end <= MID) {
        return query(start, end, l, MID, LEFT, val);
    } else if (start >= MID + 1) {
        return query(start, end, MID + 1, r, RIGHT, val);
    }

    return max(query(start, end, MID + 1, r, RIGHT, val), query(start, end, l, MID, LEFT, val));
}

int main() {
    int i, endpos = 0;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &a[i]);
        tmp[i] = a[i];
    }

    sort(tmp + 1, tmp + 1 + N);
    for (i = 1; i <= N; ++i) {
        if (i == 1 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
    }

    for (i = 1; i <= N; ++i) {
        a[i] = lower_bound(disc.begin(), disc.end(), a[i]) - disc.begin();
    }   

    for (i = N; i >= 1; --i) {
        nxt[i] = pos[a[i]];
        pos[a[i]] = i;
    }

    for (i = 1; i <= N; ++i) {
        dp[i] = dp[i-1];
        trans[i][0] = trans[i][1] = trans[i][2] = trans[i][3] = -1;
        pre[i] = i - 1;
        occ[a[i]].push_back(i);
        int sz = occ[a[i]].size();
        if (sz > 3) {
            if(dp[i] < dp[occ[a[i]][sz-4] - 1] + 4) {
                dp[i] = dp[occ[a[i]][sz-4] - 1] + 4;
                pre[i] = occ[a[i]][sz-4] - 1;
                trans[i][0] = occ[a[i]][sz-1];
                trans[i][1] = occ[a[i]][sz-2];
                trans[i][2] = occ[a[i]][sz-3];
                trans[i][3] = occ[a[i]][sz-4];
            }
        }

        if (sz > 1) {
            int idx = query(1, occ[a[i]][sz-2] - 1, 1, N, 1, occ[a[i]][sz-2]);
            // cout << "index= " << i << " get " << idx << endl;
            if (idx > 0 && dp[idx - 1] + 4 > dp[i]) {
                dp[i] = dp[idx - 1] + 4;
                pre[i] = idx - 1;
                trans[i][3] = idx;
                trans[i][2] = occ[a[i]][sz-2];
                trans[i][1] = nxt[idx];
                trans[i][0] = occ[a[i]][sz-1];
            }
            update(occ[a[i]][sz - 2], 1, N, 1, i);
        }

        if (dp[i] > dp[endpos]) endpos = i;
    }

    printf("%d\n", dp[endpos]);
    vector<int> ret;
    int idx = endpos;
    while (idx > 0) {
        if (trans[idx][0] != -1) {
            ret.push_back(disc[a[trans[idx][0]]]);
            ret.push_back(disc[a[trans[idx][1]]]);
            ret.push_back(disc[a[trans[idx][2]]]);
            ret.push_back(disc[a[trans[idx][3]]]);
        }
        idx = pre[idx];
    }

    reverse(ret.begin(), ret.end());
    for (auto v : ret) {
        printf("%d ", v);
    }
    return 0;
}