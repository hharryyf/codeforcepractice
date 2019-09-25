#include <vector>
#include <cstdio>
#include <iostream>
#include <algorithm>
#define MAX_SIZE 1048592

using namespace std;

typedef struct segt {
	int lazy, value;
} segmenttree;

segmenttree tree[MAX_SIZE];

vector<int> disc;

vector<int> points;

static bool cmp(const pair<int, int> &a, const pair<int, int> &b) {
	if (a.second == b.second) return a.first < b.first;
	return a.second < b.second;
}

vector<pair<int, int> > event;

void update(int st, int ed, int l, int r, int index, int val) {
	if (st > ed || l > r) return;
	if (tree[index].lazy != 0) {
		tree[index].value += tree[index].lazy;
		if (l != r) {
			tree[index * 2].lazy += tree[index].lazy;
			tree[index * 2 + 1].lazy += tree[index].lazy;
		}
		tree[index].lazy = 0;
	}
	
	if (st > r || l > ed) return;
	if (st <= l && r <= ed) {
		tree[index].value += val;
		if (l != r) {
			tree[index * 2].lazy += val;
			tree[index * 2 + 1].lazy += val;
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(st, ed, l, mid, index * 2, val);
	update(st, ed, mid + 1, r, index * 2 + 1, val);
	tree[index].value = max(tree[index * 2].value, tree[index * 2 + 1].value);
}

int query(int st, int ed, int l, int r, int index) {
	if (st > ed || l > r) return 0;
	if (tree[index].lazy != 0) {
		tree[index].value += tree[index].lazy;
		if (l != r) {
			tree[index * 2].lazy += tree[index].lazy;
			tree[index * 2 + 1].lazy += tree[index].lazy;
		}
		tree[index].lazy = 0;
	}
	
	if (st > r || l > ed) return 0;
	if (st <= l && r <= ed) return tree[index].value;
	
	int mid = l + (r - l) / 2;
	return max(query(st, ed, l, mid, index * 2), query(st, ed, mid + 1, r, index * 2 + 1));
}

int main() {
	int n, k, i;
	scanf("%d%d", &n, &k);
	for (i = 0 ; i < n; i++) {
		int st, ed;
		scanf("%d%d", &st, &ed);
		event.push_back(make_pair(st, ed));
		points.push_back(st);
		points.push_back(ed);
	}
	
	sort(points.begin(), points.end());
	sort(event.begin(), event.end(), cmp);
	for (i = 0 ; i < (int) points.size(); i++) {
		if (i == 0) disc.push_back(points[i]);
		else if (points[i] != points[i-1]) disc.push_back(points[i]);
	}
	int cnt = 0;
	int total = (int) disc.size();
	for (i = 0 ; i < n; i++) {
		// cout << i << endl;
		int st = lower_bound(disc.begin(), disc.end(), event[i].first) - disc.begin();
		int ed = lower_bound(disc.begin(), disc.end(), event[i].second) - disc.begin();
		if (query(st,ed, 0, total - 1, 1) < k) {
			update(st,ed, 0, total - 1, 1, 1);
			cnt++;
		}
	}
	
	cout << cnt << endl;
	return 0;
}
