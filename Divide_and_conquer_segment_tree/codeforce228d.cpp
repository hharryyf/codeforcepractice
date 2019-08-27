#include <bits/stdc++.h>
#define MAX_SIZE 131082
typedef long long Long;

using namespace std;
// tree[z][first element's s index][segment tree nodes]
Long tree[7][11][MAX_SIZE << 1];

Long arr[MAX_SIZE];

int ds[7] = {0,0,2,4,6,8,10};

Long s[7][11] = {
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,1,2,0,0,0,0,0,0,0,0},
	{0,1,2,3,2,0,0,0,0,0,0},
	{0,1,2,3,4,3,2,0,0,0,0},
	{0,1,2,3,4,5,4,3,2,0,0},
	{0,1,2,3,4,5,6,5,4,3,2}};

int n;

void build(int z, int sindex, int start, int end, int index);

Long getans(int l, int r, int z);

Long query(int z, int sindex, int start, int end, int l, int r, int index);

void update(int pt, int l, int r, int index, Long value);

int main(int argc, char *argv[]) {	
	cin >> n;
	int i, j;
	for (i = 1; i <= n; i++) {
		cin >> arr[i];
	}	
	
	for (i = 2; i <= 6; i++) {
		for (j = 1; j <= ds[i]; j++) {
			build(i, j, 1, n, 1);
		}
	}
	/*
	for (i = 1; i <= n; i++) {
		cout << getans(i, i, 2) << " ";
	}*/
	// cout << endl;
	int m;
	cin >> m;
	while (m > 0) {
		int t, z, l, r;
		scanf("%d", &t);
		if (t == 1) {
			scanf("%d%d", &l, &r);
			update(l, 1, n, 1, r);
		} else if (t == 2) {
			scanf("%d%d%d", &l, &r, &z);
			cout << getans(l, r, z) << endl;
		}
		m--;
	}
	
	
	return 0;
}

void update(int pt, int l, int r, int index, Long value) {
	int i, j;
	if (l > r) return;
	if (pt == l && l == r) {
		for (i = 2; i <= 6; i++) {
			for (j = 1; j <= ds[i]; j++) {
				tree[i][j][index] = value * s[i][((j + pt - 2) % ds[i]) + 1];
			}
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (pt <= mid) {
		update(pt, l, mid, index * 2, value);
	} else {
		update(pt, mid + 1, r, index * 2 + 1, value);
	}
	
	for (i = 2; i <= 6; i++) {
		for (j = 1; j <= ds[i]; j++) {
			tree[i][j][index] = tree[i][j][index * 2] + tree[i][j][index * 2 + 1];
		}
	}
}

Long getans(int l, int r, int z) {
	// l to be of dim 1, then 1 must be at dim k
	// k = ds[z] - (l - 1) % ds[z] + 1; 
	int dim = (ds[z] - (l - 1) % ds[z]) % ds[z] + 1;
	// cout << "l= " << l << " r= " << r << " dim= " << dim << " z= " << z<< endl;
	return query(z, dim, l, r, 1, n, 1);
}

Long query(int z, int sindex, int start, int end, int l, int r, int index) {
	if (start > end || l > r) return 0ll;
	if (start > r || end < l) return 0ll;
	if (start <= l && r <= end) return tree[z][sindex][index];
	int mid = l + (r - l) / 2;
	Long t1 = query(z, sindex, start, end, l, mid, index * 2);
	Long t2 = query(z, sindex, start, end, mid + 1, r, index * 2 + 1);
	return t1 + t2;
}

void build(int z, int sindex, int start, int end, int index) {
	if (start > end) {
		return;
	}
	
	if (start == end) {
		tree[z][sindex][index] = arr[start] * s[z][((sindex + start - 2) % ds[z]) + 1];
		return;
	}
	
	int mid = start + (end - start) / 2;
	build(z, sindex, start, mid, index * 2);
	build(z, sindex, mid + 1, end, index * 2 + 1);
	tree[z][sindex][index] = tree[z][sindex][index * 2] + tree[z][sindex][index * 2 + 1];
}
