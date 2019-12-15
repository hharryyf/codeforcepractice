#include <bits/stdc++.h>
#define MAX_SIZE (1048576 + 11)
using namespace std;

// tree first stores the index of the previous occurrence
// tree secind stores the index of the element in the array
pair<int, int> tree[MAX_SIZE];

int arr[MAX_SIZE >> 1];
// pos[i] refers to the previous occurence of the value i
// 0 means non-exist
int pos[MAX_SIZE >> 1];
// stores all the queries 1 indexed
pair<pair<int, int>, int> qrs[MAX_SIZE >> 1];
// number of elements in the array
int n;
// total number of qrs
int m;

int ans[MAX_SIZE];

static bool cmp(const pair<pair<int, int>, int> &a, const pair<pair<int, int>, int> &b) {
	if (a.first.second != b.first.second) return a.first.second < b.first.second;
	return a.first.first < b.first.first; 
}

void update(int pt, int l, int r, int index, int val);
pair<int, int> query(int start, int end, int l, int r, int index);

int main(int argc, char *argv[]) {
	int i, j;
	scanf("%d", &n);
	for (i = 1 ; i <= n; i++) {
		scanf("%d", &arr[i]);
	}	
	
	scanf("%d", &m);
	for (i = 1; i <= m; i++) {
		scanf("%d%d", &qrs[i].first.first, &qrs[i].first.second);
		qrs[i].second = i;
	}
	
	sort(qrs + 1, qrs + 1 + m, cmp);
	
	
	for (i = 1, j = 1; i <= n && j <= m; i++) {
		if (pos[arr[i]] != 0) update(pos[arr[i]], 1, n, 1, MAX_SIZE);
		update(i, 1, n, 1, pos[arr[i]]);
		while (j <= m && qrs[j].first.second == i) {
			pair<int, int> t = query(qrs[j].first.first, qrs[j].first.second, 1, n, 1);
			// cout << t.first << " " << t.second << endl;
			if (t.first < qrs[j].first.first) {
				//cout << "in " << endl;
				ans[qrs[j].second] = arr[t.second];
			}
			j++;
		}				
		pos[arr[i]] = i;
	}
	
	for (i = 1; i <= m; i++) {
		printf("%d\n", ans[i]);
	}
	return 0;
}

void update(int pt, int l, int r, int index, int val) {
	if (l > r) return;
	if (l == r && pt == l) {
		tree[index].first = val;
		tree[index].second = pt;
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (pt <= mid) {
		update(pt, l, mid, index * 2, val);
	} else {
		update(pt, mid + 1, r, index * 2 + 1, val);
	}
	
	tree[index] = min(tree[index * 2], tree[index * 2 + 1]);
}

pair<int, int> query(int start, int end, int l, int r, int index) {
	if (l > r || start > end || l > end || start > r) return make_pair(MAX_SIZE + 1, 0);
	if (start <= l && r <= end) return tree[index];
	int mid = l + (r - l) / 2;
	return min(query(start, end, l, mid, index * 2), query(start, end, mid + 1, r, index * 2 + 1));
}
