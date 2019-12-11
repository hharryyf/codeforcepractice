#include <bits/stdc++.h>
#define MAX_SIZE 262192
#define INF -1
using namespace std;

int tree[MAX_SIZE];
// which club visited in the ith day
int visited[MAX_SIZE];
// score of the ith club
int score[MAX_SIZE];
map<int, int> mp;
void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index] = score[l];
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index] = max(tree[index * 2], tree[index * 2 + 1]);
}

// return the maximum value within the range
int query(int start, int end, int l, int r, int index) {
	if (start > end || l > r || l > end || start > r) return INF;
	if (start <= l && r <= end) {
		return tree[index];
	}
	
	int mid = l + (r - l) / 2;
	return max(query(start, end, l, mid, index * 2), query(start, end, mid + 1, r, index * 2 + 1));
}

void update(int pt, int l, int r, int index, int val) {
	if (l > r || pt < l || pt > r) return;
	if (l == r && r == pt) {
		tree[index] = val;
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (pt <= mid) {
		update(pt, l, mid, index * 2, val);
	} else {
		update(pt, mid + 1, r, index * 2 + 1, val);
	}
	
	tree[index] = max(tree[index * 2], tree[index * 2 + 1]);
}

int main() {
	int i, n, k, q;
	scanf("%d%d%d", &n, &k, &q);
	for (i = 1; i <= n; i++) {
		scanf("%d", &score[i]);
		mp[score[i]] = i;
	}
	
	build(1, n, 1);
	
	for (i = 1; i <= q; i++) {
		if (i > k + 1) {
			if (visited[i-k-1] != 0) {
				update(visited[i-k-1], 1, n, 1, score[visited[i-k-1]]);	
			}
		}
		
		int l, r;
		scanf("%d%d", &l, &r);
		int val = query(l, r, 1, n, 1);
		// cout << "query " << val << endl;
		if (val == -1) {
			printf("%d\n", val);
		} else {
			int index = mp[val];
			printf("%d\n", index);
			update(index, 1, n, 1, INF);
			visited[i] = index;
		}
	}
	return 0;
}
