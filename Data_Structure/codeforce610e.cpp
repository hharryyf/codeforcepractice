#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 524292
#define MID ((l+r)>>1)
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)

using namespace std;

struct segt {
	int occ[10][10];
	int lz;
	char lc, rc;
};

segt tree[MAX_SIZE];
char st[MAX_SIZE];
char ss[12];
int n, k;

void pullup(int l, int r, int index) {
	if (l >= r) return;
	int i, j;
	for (i = 0 ; i < k; ++i) {
		for (j = 0 ; j < k; ++j) {
			tree[index].occ[i][j] = tree[LEFT].occ[i][j] + tree[RIGHT].occ[i][j];
		}
	}
	tree[index].occ[tree[LEFT].rc - 'a'][tree[RIGHT].lc - 'a']++;
	tree[index].lc = tree[LEFT].lc, tree[index].rc = tree[RIGHT].rc;
}

void pushdown(int l, int r, int index) {
	if (l > r || tree[index].lz == -1) return;
	int i, j;
	if (l != r) {
		for (i = 0 ; i < k; ++i) {
			for (j = 0 ; j < k; ++j) {
				tree[LEFT].occ[i][j] = tree[RIGHT].occ[i][j] = 0;
			}
		}
		tree[LEFT].lz = tree[RIGHT].lz = tree[index].lz;
		tree[LEFT].occ[tree[index].lz][tree[index].lz] = MID - l;
		tree[RIGHT].occ[tree[index].lz][tree[index].lz] = r - MID - 1;
		tree[LEFT].lc = tree[LEFT].rc = tree[RIGHT].lc = tree[RIGHT].rc = tree[index].lz + 'a';
	}
	tree[index].lz = -1;
}

void build(int l, int r, int index) {
	if (l > r) return;
	tree[index].lz = -1;
	if (l == r) {
		tree[index].lc = tree[index].rc = st[l];
		return;
	}
	
	build(l, MID, LEFT);
	build(MID + 1, r, RIGHT);
	pullup(l, r, index);
}

void update(int start, int end, int l, int r, int index, int v) {
	if (start > end || l > r || start > r || l > end) return;
	pushdown(l, r, index);
	int i, j;
	if (start <= l && r <= end) {
		for (i = 0 ; i < k; ++i) {
			for (j = 0 ; j < k; ++j) {
				tree[index].occ[i][j] = 0;
			}
		}
		tree[index].occ[v][v] = r - l;
		tree[index].lz = v;
		tree[index].lc = tree[index].rc = v + 'a';
		return;
	}
	
	if (end <= MID) {
		update(start, end, l, MID, LEFT, v);
	} else if (start >= MID + 1) {
		update(start, end, MID + 1, r, RIGHT, v);
	} else {
		update(start, end, l, MID, LEFT, v);
		update(start, end, MID + 1, r, RIGHT, v);
	}
	pullup(l, r, index);
}

int weight[12];

int getans() {
	int i, j, ans = 0;
	for (i = 0 ; i < k; ++i) {
		weight[ss[i] - 'a'] = i;
	}
	
	for (i = 0 ; i < k; ++i) {
		for (j = 0 ; j < k; ++j) {
			if (weight[i] >= weight[j]) ans+= tree[1].occ[i][j];
		}
	}
	return ans + 1;
}

int main() {
	int q;
	scanf("%d%d%d", &n, &q, &k);
	scanf("%s", st + 1);
	build(1, n, 1);
	while (q > 0) {
		int tp, l, r;
		scanf("%d", &tp);
		if (tp == 1) {
			scanf("%d%d%s", &l, &r, ss);
			update(l, r, 1, n, 1, ss[0] - 'a');
		} else {
			scanf("%s", ss);
			printf("%d\n", getans());
		}
		--q;
	}
	return 0;
}