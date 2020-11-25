#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
#define MAX_SIZE 32773
typedef long long ll;
using namespace std;

struct segt {
    ll lz, val;
};

segt tree[53][MAX_SIZE << 1];
int a[53][MAX_SIZE], pre[53][MAX_SIZE];
ll value[MAX_SIZE];
int N, M, K;

void build(int l, int r, int index, int dim) {
    if (l > r) return;
    if (l == r) {
        tree[dim][index].val = value[l];
        return;
    }

    build(l, MID, LEFT, dim);
    build(MID + 1, r, RIGHT, dim);
    tree[dim][index].val = max(tree[dim][LEFT].val, tree[dim][RIGHT].val);
}

void pushdown(int l, int r, int index, int dim) {
    if (l > r) return;
    if (tree[dim][index].lz != 0) {
        if (l != r) {
            tree[dim][LEFT].val += tree[dim][index].lz;
            tree[dim][RIGHT].val += tree[dim][index].lz;
            tree[dim][LEFT].lz += tree[dim][index].lz;
            tree[dim][RIGHT].lz += tree[dim][index].lz;
        }
        tree[dim][index].lz = 0;
    }
}

void update(int start, int end, int l, int r, int index, int val, int dim) {
    if (start > end || l > r || start > r || l > end) return;
    pushdown(l, r, index, dim);
    if (start <= l && r <= end) {
        tree[dim][index].val += val;
        tree[dim][index].lz += val;
        return;
    }

    if (end <= MID) {
        update(start, end, l, MID, LEFT, val, dim);
    } else if (start >= MID + 1) {
        update(start, end, MID + 1, r, RIGHT, val, dim);
    } else {
        update(start, end, l, MID, LEFT, val, dim);
        update(start, end, MID + 1, r, RIGHT, val, dim);
    }
    tree[dim][index].val = max(tree[dim][LEFT].val, tree[dim][RIGHT].val);
}

int main() {
    int i, j;
    scanf("%d%d%d", &N, &M, &K);
    for (i = 0; i < N; ++i) {
        for (j = 1; j <= M; ++j) {
            scanf("%d", &a[i][j]);
            pre[i][j] = pre[i][j-1] + a[i][j];
        }
    }

    for (i = 1; i <= M; ++i) {
        value[i] = pre[0][i] + pre[1][i];
        if (i >= K) {
            value[i] -= pre[0][i-K] + pre[1][i-K];
        }
    }

    build(1, M, 1, 1);
    for (i = 2; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            update(j, min(j + K - 1, M), 1, M, 1, -a[i - 1][j], i - 1);
            // cout << "update " << j << " " << j + K - 1 << " by " << -a[i-1][j] << endl;
            if (j > K) {
                update(j - K, j - 1, 1, M, 1, a[i-1][j - K], i - 1);
                // cout << "upd " << j - K << " " << j-1 << " by " << a[i-1][j-K] << endl;
            }
            value[j] = pre[i][j] + pre[i-1][j];
            if (j >= K) value[j] -= pre[i][j-K] + pre[i-1][j-K];
            value[j] += tree[i-1][1].val;
            // cout << "get value " << i << " " << j << " = " << value[j] << endl;
        }
        build(1, M, 1, i);
    }

    printf("%I64d\n", tree[N][1].val);
    return 0;
}