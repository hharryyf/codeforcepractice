#include <bits/stdc++.h>
#define MAX_SIZE 262192
using namespace std;

typedef struct segt {
	int level, value;
} segmenttree;

segmenttree tree[MAX_SIZE];

int n;

int arr[MAX_SIZE];

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index].value = arr[l];
		tree[index].level = 0;
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index].level = tree[index * 2].level + 1;
	if (tree[index].level % 2 == 1) {
		tree[index].value = (tree[index * 2].value | tree[index * 2 + 1].value);
	} else {
		tree[index].value = (tree[index * 2].value ^ tree[index * 2 + 1].value);
	}
}

void update(int pt, int l, int r, int index, int v) {
	if (l > r) return;
	if (l == r && pt == l) {
		tree[index].value = v;
		tree[index].level = 0;
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (pt <= mid) {
		update(pt, l, mid, index * 2, v);
	} else {
		update(pt, mid + 1, r, index * 2 + 1, v);
	}
	
	tree[index].level = tree[index * 2].level + 1;
	if (tree[index].level % 2 == 1) {
		tree[index].value = (tree[index * 2].value | tree[index * 2 + 1].value);
	} else {
		tree[index].value = (tree[index * 2].value ^ tree[index * 2 + 1].value);
	}
}

int main() {
	int q;
	cin >> n >> q;
	for (int i = 1; i <= (1 << n); i++) {
		scanf("%d", &arr[i]);
	}
	
	build(1, 1 << n, 1);
	while (q > 0) {
		int idx, v;
		scanf("%d%d", &idx, &v);
		update(idx, 1, 1 << n, 1, v);
		cout << tree[1].value << endl;
		q--;
	}
	return 0;
}
