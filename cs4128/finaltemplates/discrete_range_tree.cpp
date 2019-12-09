// periodic RMQ

#include <bits/stdc++.h>
#define MAX_SIZE 2097252

using namespace std;

struct segt {
	int l, r;
	int lz, value;
	bool isleaf;
};

int orig[MAX_SIZE >> 3];

segt tree[MAX_SIZE];
// start and end interval
vector<pair<int, int> > interval;

// initial values
int a[MAX_SIZE >> 4];

// important points without point compression
int pt[MAX_SIZE >> 1];

// all the related points, guarenteed unique
vector<int> disc;

int oper[MAX_SIZE >> 4][4];

int k, q, n;


segt pullup(segt t1, segt t2) {
	segt t;
	t.lz = 0;
	t.value = min(t1.value, t2.value);
	t.l = t1.l;
	t.r = t2.r;
	t.isleaf = false;
	return t;
}

void pushdown(int index) {
	if (tree[index].lz) {
		if (!tree[index].isleaf) {
			tree[index * 2].value = tree[index].lz;
			tree[index * 2 + 1].value = tree[index].lz;
			tree[index * 2].lz = tree[index].lz;
			tree[index * 2 + 1].lz = tree[index].lz;
		}
		tree[index].lz = 0;
	}
}

// get the initial rmq of range start, end
int rmq(int start, int end, int l, int r, int index) {
	if (start > end || l > r || start > r || l > end) return 1000000000 + 7;
	if (start <= l && r <= end) return orig[index];
	int mid = l + (r - l) / 2;
	return min(rmq(start, end, l, mid, index * 2), rmq(start, end, mid + 1, r, index * 2 + 1));
}


void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index].l = interval[l].first;
		tree[index].r = interval[l].second;
		tree[index].isleaf = true;
		if (tree[index].r - tree[index].l + 1 >= n) {
			tree[index].value = rmq(1, n, 1, n, 1);
		} else {
			int left = (tree[index].l % n != 0 ? tree[index].l % n : n);
			int right = (tree[index].r % n != 0 ?  tree[index].r % n : n);
			
			if (left > right) {
				tree[index].value = min(rmq(left, n, 1, n, 1), rmq(1, right, 1, n, 1));
			} else {
				tree[index].value = rmq(left, right, 1, n, 1);
			}
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index] = pullup(tree[index * 2], tree[index * 2 + 1]);
}

void update(int start, int end, int index, int val) {
	if (start > end) return;
	pushdown(index);
	if (start > tree[index].r || tree[index].l > end) return;
	if (start <= tree[index].l && tree[index].r <= end) {
		tree[index].value = val;
		tree[index].lz = val;
		return;
	}
	
	update(start, end, index * 2, val);
	update(start, end, index * 2 + 1, val);
	tree[index] = pullup(tree[index * 2], tree[index * 2 + 1]);
}

int query(int start, int end, int index) {
	if (start > end) {
		return 1000000000 + 7; 
	}
	
	pushdown(index);
	
	if (start > tree[index].r || tree[index].l > end) return 1000000000 + 7;
	if (start <= tree[index].l && tree[index].r <= end) return tree[index].value;
	return min(query(start, end, index * 2), query(start, end, index * 2 + 1));
}

void buildint(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		orig[index] = a[l];
		return;
	}
	
	int mid = l + (r - l) / 2;
	buildint(l, mid, index * 2);
	buildint(mid + 1, r, index * 2 + 1);
	orig[index] = min(orig[index * 2], orig[index * 2 + 1]);
}

int main() {
	int i, cnt = 0;
	scanf("%d%d", &n, &k);
	for (i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		pt[cnt++] = i;
	}	
	
	pt[cnt++] = n * k;
	
	scanf("%d", &q);
	for (i = 0 ; i < q; i++) {
		scanf("%d%d%d", &oper[i][0], &oper[i][1], &oper[i][2]);
		if (oper[i][0] == 1) {
			scanf("%d", &oper[i][3]);
		}
		pt[cnt++] = oper[i][1];
		pt[cnt++] = oper[i][2];
	}
	
	sort(pt, pt + cnt);
	for (i = 0 ; i < cnt; i++) {
		if (i == 0 || pt[i] != pt[i-1]) {
			disc.push_back(pt[i]);
		}
	}
	
	for (i = 0 ; i < (int) disc.size(); i++) {
		if (i == 0) {
			interval.emplace_back(disc[0], disc[0]);
		} else {
			if (disc[i] - disc[i-1] > 1) {
				interval.emplace_back(disc[i-1] + 1, disc[i] - 1);
			}
			interval.emplace_back(disc[i], disc[i]);
		}
	}
	
	int m = (int) interval.size();
	
	buildint(1, n, 1);
	
	build(0, m - 1, 1);
	
	
	for (i = 0 ; i < q; i++) {
		if (oper[i][0] == 1) {
			update(oper[i][1], oper[i][2], 1, oper[i][3]);
		} else {
			printf("%d\n", query(oper[i][1], oper[i][2], 1));
		}
	}
	return 0;
}
