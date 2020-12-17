#include <bits/stdc++.h>
#define MAX_SIZE 262192
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
typedef long long ll;
using namespace std;

int tree[MAX_SIZE];
int a[MAX_SIZE];

void update(int pt, int l, int r, int index, int val) {
	if (l > r || pt < l || pt > r) return;
	if (l == r) {
		tree[index] = val;
		return;
	}

	if (pt <= MID) {
		update(pt, l, MID, LEFT, val);
	} else {
		update(pt, MID + 1, r, RIGHT, val);
	}

	tree[index] = tree[LEFT] + tree[RIGHT];
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index] = a[l];
		return;
	}

	build(l, MID, LEFT);
	build(MID + 1, r, RIGHT);
	tree[index] = tree[LEFT] + tree[RIGHT];
}

int query(int start, int end, int l, int r, int index) {
	if (start > end || l > r || start > r || l > end) return 0;
	if (start <= l && r <= end) return tree[index];
	if (end <= MID) {
		return query(start, end, l, MID, LEFT);
	} else if (start >= MID + 1) {
		return query(start, end, MID + 1, r, RIGHT);
	}

	return query(start, end, l, MID, LEFT) + query(start, end, MID + 1, r, RIGHT);
}

int N, K, R;

int main() {
	int i;
	scanf("%d%d%d", &N, &K, &R);
	for (i = 1; i <= K; ++i) {
		int v;
		scanf("%d", &v);
		a[v] = 1;
	}

	build(1, N, 1);
	int ans = 0;
	for (i = R; i <= N; ++i) {
		int tol = query(i - R + 1, i, 1, N, 1);
		if (tol >= 2) continue;
		if (tol == 0) {
			a[i-1] = a[i] = 1;
			update(i - 1, 1, N, 1, 1);
			update(i, 1, N, 1, 1);
			ans += 2;
		}  else {
			if (a[i] == 1) {
				update(i - 1, 1, N, 1, 1);
				a[i-1] = 1;
			} else {
				update(i, 1, N, 1, 1);
				a[i] = 1;
			}
			ans += 1;
		}
	}

	printf("%d\n", ans);
	return 0;
}
