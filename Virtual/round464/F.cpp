#include <bits/stdc++.h>
#define MAX_SIZE 262192
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;

int N, K, L[101], R[101];
int tree[101][MAX_SIZE];
deque<int> q;

void update(int pt, int l, int r, int index, int val, int dim) {
    if (pt < l || pt > r || l > r) return;
    if (l == r) {
        tree[dim][index] = min(tree[dim][index], val);
        return;
    }

    if (pt <= MID) {
        update(pt, l, MID, LEFT, val, dim);
    } else {
        update(pt, MID + 1, r, RIGHT, val, dim);
    }

    tree[dim][index] = min(tree[dim][LEFT], tree[dim][RIGHT]);
}

int query(int start, int end, int l, int r, int index, int dim) {
    if (start > end || l > r || start > r || l > end) return MAX_SIZE;
    if (start <= l && r <= end) return tree[dim][index];
    if (end <= MID) return query(start, end, l, MID, LEFT, dim);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT, dim);
    return min(query(start, end, l, MID, LEFT, dim), query(start, end, MID + 1, r, RIGHT, dim));
}

int F(int x, int dim) {
	return x < 0 || x > N ? MAX_SIZE : query(x, x, 0, N, 1, dim);
}


int main() {
    int i, j;
	scanf("%d%d", &N, &K);
    // dp[i][j] = minimum flips when we have R[i] seconds and the current side has been cooked for j seconds
    // it is easy to see the base case dp[0][0] = 0 and dp[0][1:N] = INF
    // for the recursive case, we use the property that in each interval only 0-2 swaps can happen
    // case when we have 0 swaps, then dp[i][j] = dp[i-1][j-R[i] + R[i-1]]
    // case when we have 2 swaps, then suppose there are t seconds we cook the other side,
    // dp[i][j] = 2 + min(any t = 0..R[i] - L[i], dp[i-1][j - R[i] + R[i-1] + t])
    // i.e. dp[i][j] = 2 + min(dp[i-1][k], k = [j - R[i] + R[i-1], j - L[i] + R[i-1]])
    // case when we have 1 swap, then suppose t seconds we cook the current side
    // dp[i][j] = 1 + min(dp[i-1][R[i-1] + R[i] - L[i] - j + t], t = [0, R[i] - L[i]])
    // dp[i][j] = 1 + min(dp[i-1][k], k = [R[i-1] - j, R[i-1] + R[i] - L[i] - j])
    memset(tree, MAX_SIZE, sizeof(tree));
	for (i = 1; i <= K; i++)
		scanf("%d%d", &L[i], &R[i]);
	update(0, 0, N, 1, 0, 0);
    
    for (i = 1; i <= K; ++i) {
        for (j = 0 ; j <= N; ++j) {
            update(j, 0, N, 1, F(j - R[i] + R[i-1], i - 1), i);
        }

        for (j = 0 ; j <= N; ++j) {
            int l = R[i-1] - j, r = R[i-1] + R[i] - L[i] - j, ret = query(l, r, 0, N, 1, i - 1) + 1;
            update(j, 0, N, 1, ret, i);
            l = j - R[i] + R[i-1], r = j - L[i] + R[i-1], ret = query(l, r, 0, N, 1, i - 1) + 2;
            update(j, 0, N, 1, ret, i);
        }
    }

    int ret = F(R[K] - N, K);
	if (ret >= MAX_SIZE) {
		printf("Hungry\n");
    } else {
		printf("Full\n%d\n", ret);
    }

	return 0;
}