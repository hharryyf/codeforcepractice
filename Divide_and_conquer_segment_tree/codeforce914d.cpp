#include <bits/stdc++.h>
#define MAX_SIZE 1048592

using namespace std;

int tree[MAX_SIZE];
int arr[MAX_SIZE >> 1];
int n;
int judge;
int gcd(int x, int y);
void build(int l, int r, int index);
void update(int pt, int l, int r, int index, int v);
void query(int start, int end, int l, int r, int index, int v);

int main(int argc, char *argv[]) {
	cin >> n;
	int i, m;
	int t, l, r, x;
	
	for (i = 0 ; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	
	build(0, n - 1, 1);
	
	cin >> m;
	for (i = 0 ; i < m; i++) {
		scanf("%d", &t);
		if (t == 1) {
			scanf("%d%d%d", &l, &r, &x);
			judge = 0;
			query(l - 1, r - 1, 0, n - 1, 1, x);
			cout << ((judge <= 1) ? "YES" : "NO") << endl;
		} else if (t == 2) {
			scanf("%d%d", &l, &x);
			update(l - 1, 0, n - 1, 1, x);
		}
		
	}
	return 0;
}

void update(int pt, int l, int r, int index, int v) {
	if (l > r) return;
	if (l == r) {
		tree[index] = v;
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (pt <= mid) {
		update(pt, l, mid, index * 2, v);	
	} else {
		update(pt, mid + 1, r, index * 2 + 1, v);
	}
	tree[index] = gcd(tree[index * 2], tree[index * 2 + 1]);
}

int gcd(int x, int y) {
	if (x == 0) return y;
	return gcd(y % x, x);
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index] = arr[l];
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index] = gcd(tree[index * 2], tree[index * 2 + 1]);
}

void query(int start, int end, int l, int r, int index, int v) {
	if (start > end || l > r) return;
	if (end < l || r < start) return;
	if (judge > 1) return;
	if (start <= l && r <= end) {
		if (tree[index] % v == 0) return;
		if (judge >= 1) {
			judge++;
			return;
		} 
	}
	
	if (l == r) {
		judge++;
		return;
	}
	int mid = l + (r - l) / 2;
	if (mid >= start) {
		query(start, end, l, mid, index * 2, v);
	}
	
	if (mid < end) {
		query(start, end, 1 + mid, r, index * 2 + 1, v);
	}
}

