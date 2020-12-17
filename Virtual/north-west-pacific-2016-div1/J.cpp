#include <bits/stdc++.h>
#define MAX_SIZE 524292
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
typedef long long ll;
using namespace std;

ll tree[MAX_SIZE];
ll a[MAX_SIZE];
int N, Q;

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index] = a[l];
		return;
	}

	build(l, MID, LEFT);
	build(MID + 1, r, RIGHT);
	tree[index] = min(tree[LEFT], tree[RIGHT]);
}

int query(int start, int end, int l, int r, int index, ll val) {
	if (l > r || start > r || l > end || start > end) return MAX_SIZE;
	if (tree[index] > val) return MAX_SIZE;
	if (l == r) return l;
	if (start <= l && r <= end) {
		if (tree[LEFT] <= val) return query(start, end, l, MID, LEFT, val);
		return query(start, end, MID + 1, r, RIGHT, val);
	}

	if (end <= MID) return query(start, end, l, MID, LEFT, val);
	if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT, val);
	return min(query(start, end, l, MID, LEFT, val), query(start, end, MID + 1, r, RIGHT, val));
}

int main() {
	int i;
	scanf("%d%d", &N, &Q);
	for (i = 1; i <= N; ++i) scanf("%I64d", &a[i]);
	build(1, N, 1);
	while (Q-- > 0) {
		ll v;
		int l, r;
		scanf("%I64d%d%d", &v, &l, &r);
		while (l <= r) {
			l = query(l, r, 1, N, 1, v);
			if (l <= r) {
				v = v % a[l];
				l++;
			}
		}

		printf("%I64d\n", v);
	}
	return 0;
}
