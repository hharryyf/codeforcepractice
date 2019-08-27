#include <bits/stdc++.h>
#define MAX_LEN 1048602

using namespace std;

typedef struct female {
	int x, y, z;
} Female;

Female arr[MAX_LEN >> 1];

int tree[MAX_LEN];

int n;

vector<int> discrete;

void build(int l, int r, int index);

// update the pos to max(value[pos], val)
void update(int pos, int l, int r, int index, int val);

int query(int start, int end, int l, int r, int index);

static bool cmp(const Female &a, const Female &b) {
	if (a.y != b.y) return a.y > b.y;
	return a.z < b.z;
}

int main(int argc, char *argv[]) {
	scanf("%d", &n);
	int i, ans = 0, m;
	discrete = vector<int>();
	
	for (i = 0 ; i < n; i++) {
		scanf("%d", &arr[i].x);
		discrete.push_back(arr[i].x);
	}
	
	for (i = 0 ; i < n; i++) {
		scanf("%d", &arr[i].y);
	}
	
	for (i = 0 ; i < n; i++) {
		scanf("%d", &arr[i].z);
	}
	
	sort(discrete.begin(), discrete.end());
	unique(discrete.begin(), discrete.end());
	sort(arr, arr+n, cmp);
	/*
	for (i = 0 ; i < n; i++) {
		cout << arr[i].x << " " << arr[i].y << " " << arr[i].z << "the index in the segment tree is ";
		cout << lower_bound(discrete.begin(), discrete.end(), arr[i].x) - discrete.begin();
		cout << endl;
	}*/
	m = (int) discrete.size();
	build(0, m - 1, 1);
	
	for (i = 0 ; i < n; i++) {
		int index = lower_bound(discrete.begin(), discrete.end(), arr[i].x) - discrete.begin();
		if (query(index + 1, m - 1, 0, m - 1, 1) > arr[i].z) ans++;
		update(index, 0, m - 1, 1, arr[i].z);
	}
	
	printf("%d\n", ans);
	return 0;
}

void build(int l, int r, int index) {
	if (l > r) {
		return;
	}
	if (l == r) {
		tree[index] = -1;
		return;
	}
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index] = -1;
}

// update the pos to max(value[pos], val)
void update(int pos, int l, int r, int index, int val) {
	if (l > r) return;
	if (l == r && r == pos) {
		tree[index] = max(val, tree[index]);
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (pos <= mid) {
		update(pos, l, mid, index * 2, val);
	} else {
		update(pos, mid + 1, r, index * 2 + 1, val);
	}
	tree[index] = max(tree[index * 2], tree[index * 2 + 1]);
}

int query(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return -1;
	if (start > r || end < l) return -1;
	if (start <= l && r <= end) return tree[index];
	int mid = l + (r - l) / 2;
	return max(query(start, end, l, mid, index * 2), query(start, end, mid + 1, r, index * 2 + 1));
}
