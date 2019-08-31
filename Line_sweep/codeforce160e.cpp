#include <bits/stdc++.h>
#define MAX_SIZE 524312


using namespace std;

typedef struct segt {
	int value;
	int id;
} segmenttree;


typedef struct qur {
	// left, right
	int l, r;
	// time
	int t;
	// id
	int id;
} queries;

segmenttree tree[MAX_SIZE];

queries rq[MAX_SIZE];

int tt[MAX_SIZE];

int ans[MAX_SIZE];

static bool cmp(const queries &a, const queries &b) {
	if (a.l != b.l) {
		return a.l < b.l;
	}
	// make sure that the person comes after the bus
	return a.id < b.id;
}

void update(int pos, int l, int r, int value, int id, int index);

int query(int pos, int right, int l, int r, int index);

int main(int argc, char *argv[]) {
	int i, n, m;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n + m; i++) {
		scanf("%d%d%d", &rq[i].l, &rq[i].r, &rq[i].t);
		rq[i].id = i;
		tt[i] = rq[i].t;
	}
	
	sort(rq + 1, rq + 1 + n + m, cmp);
	sort(tt + 1, tt + 1 + n + m);
	
	for (i = 1; i <= n + m; i++) {
		// it is a bus
		int pos = lower_bound(tt + 1, tt + 1 +n + m, rq[i].t) - tt;
		if (rq[i].id <= n) {
			update(pos, 1, n + m, rq[i].r, rq[i].id, 1);
		} else {
			// it is a person, we want to search the minimum possible
			// t's id
			ans[rq[i].id - n] = query(pos, rq[i].r, 1, n + m, 1);
		}
	}
	
	for (i = 1; i <= m; i++) {
		printf("%d ", ans[i]);
	}
	
	printf("\n");
	return 0;
}

void update(int pos, int l, int r, int value, int id, int index) {
	if (l > r) return;
	if (pos == l && l == r) {
		tree[index].value = value;
		tree[index].id = id;
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (mid >= pos) {
		update(pos, l, mid, value, id, index * 2);
	} else {
		update(pos, mid + 1, r, value, id, index * 2 + 1);
	}
	
	tree[index].value = max(tree[index * 2].value, tree[index * 2 + 1].value);
}

int query(int pos, int right, int l, int r, int index) {
	if (l > r) return -1;
	
	// the bus's maximum right is less than the person's right
	if (tree[index].value < right) return -1;
	if (l == r) return tree[index].id;
	int mid = l + (r - l) / 2;
	if (mid >= pos) {
		int ret = query(pos, right, l, mid, index * 2);
		if (ret != -1) {
			return ret;
		}
	}
	
	return query(pos, right, mid + 1, r, index * 2 + 1);
}
