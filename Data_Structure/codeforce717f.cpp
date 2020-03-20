#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 524292
#define INF 1000000000000ll
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)
#define MID ((l+r)>>1)

using namespace std;

/*
	Instead of constructing the valid solution, we should derive
	an if and only if condition for the existance of a valid solution.
	we define a move(i, j) predicate.
	move(i, j) :- j-i = 1 or i-j=1.
	Then, just like the flow of network, we can see that if it is possible to move
	from 1 to n then,
	move(2, 1) + 1 = a1
	move(1, 2) + move(3, 2) = a2
	move(2, 3) + move(4, 3) = a3
	...
	move(n-1, n) = an
	move(1, 2) - move(2, 1) = 1
	move(2, 3) - move(3, 2) = 1
	move(3, 4) - move(4, 3) = 1;
	...
	move(i, i+1) - move(i+1, i) = 1.
	
	Hence, 1 can move to n iff
	a1-a2+a3-a4+... >= (n % 2)
	and a1 >= 1
	a2-a1 >= 0
	a3-a2+a1 >= 1
	a4-a3+a2-a1 >= 0
	...
	an-a_(n-1) + ... >= n%2
	We should maintain this alternating sum using range tree
*/

struct segt {
	// 1 refers to the odd term
	// 0 refers to the even term
	ll rmin[2], lz[2];
};

segt tree[MAX_SIZE];
// a[i] is the alternating sum v[i] - v[i-1] + ...
ll a[MAX_SIZE];
int n;

segt pullup(segt t1, segt t2) {
	segt t;
	t.rmin[0] = min(t1.rmin[0], t2.rmin[0]);
	t.rmin[1] = min(t1.rmin[1], t2.rmin[1]);
	t.lz[0] = t.lz[1] = 0ll;
	return t;
}

void pushdown(int l, int r, int index) {
	if (l > r) return;
	int i;
	for (i = 0 ; i < 2; ++i) {
		if (l != r) {
			tree[LEFT].rmin[i] += tree[index].lz[i];
			tree[RIGHT].rmin[i] += tree[index].lz[i];
			tree[LEFT].lz[i] += tree[index].lz[i];
			tree[RIGHT].lz[i] += tree[index].lz[i];
		}
		tree[index].lz[i] = 0;
	}
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index].lz[0] = tree[index].lz[1] = 0;
		tree[index].rmin[l & 1] = a[l];
		tree[index].rmin[(l & 1) ^ 1] = INF;
		return;
	}
	
	build(l, MID, LEFT);
	build(MID + 1, r, RIGHT);
	tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

void update(int start, int end, int l, int r, int index, ll val, int dim) {
	if (start > end || l > r) return;
	pushdown(l, r, index);
	if (start > r || l > end) return;
	if (start <= l && r <= end) {
		tree[index].rmin[dim] += val;
		tree[index].lz[dim] += val;
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
	tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

segt query(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return tree[0];
	pushdown(l, r, index);
	if (start > r || l > end) return tree[0];
	if (start <= l && r <= end) return tree[index];
	if (end <= MID) {
		return query(start, end, l, MID, LEFT);
	} 
	
	if (start >= MID + 1) {
		return query(start, end, MID + 1, r, RIGHT);
	}
	
	return pullup(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}

int main() {
	int i;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		ll v;
		scanf("%I64d", &v);
		a[i] = -a[i-1] + v;
	}
	
	build(1, n, 1);
	int q;
	scanf("%d", &q);
	while (q > 0) {
		int tp, l, r;
		scanf("%d%d%d", &tp, &l, &r);
		l++, r++;
		if (tp == 1) {
			ll v;
			scanf("%I64d", &v);
			// update range 1
			update(l, r, 1, n, 1, v, l & 1);
			// update range 2
			if ((r - l + 1) & 1) {
				update(r+1, n, 1, n, 1, v, l & 1);
				update(r+1, n, 1, n, 1, -v, (l & 1) ^ 1);
			}
		} else {
			segt ret = query(l, r, 1, n, 1);
			segt ret1 = query(l-1, l-1, 1, n, 1);
			segt ret2 = query(r, r, 1, n, 1);
			// length is odd
			if ((r-l+1) & 1) {
				if (ret2.rmin[r & 1] + ret1.rmin[((l-1) & 1)] == 1 
				    && ret.rmin[(r & 1) ^ 1] - ret1.rmin[(l-1) & 1] >= 1 
					&& ret.rmin[r & 1] + ret1.rmin[(l-1) & 1] >= 0) {
					printf("1\n");
				} else {
					// fail condition
					printf("0\n");
				}
			} else {
				if (ret2.rmin[r & 1] - ret1.rmin[(l-1) & 1] == 0 
				  && ret.rmin[r & 1] - ret1.rmin[(l-1) & 1] >= 0
				  && ret.rmin[(r & 1) ^ 1] + ret1.rmin[(l-1) & 1] >= 1) {
					printf("1\n");
				} else {
					// fail condition
					printf("0\n");
				}
			}
		}
		q--;
	}
	return 0;
}