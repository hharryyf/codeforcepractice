#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 524292
typedef long long ll;
using namespace std;

int tree[MAX_SIZE];

int tmp[MAX_SIZE >> 1];
pair<int, int> a[MAX_SIZE >> 1];
vector<int> disc;

void update(int pos, int l, int r, int index, int val) {
	 if (pos < l || l > r || pos > r) return;
	 if (l == r && pos == l) {
	 	tree[index] = max(tree[index], val);
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
	if (start > end || l > r || start > r || l > end) return 0;
	if (start <= l && r <= end) return tree[index];
	int mid = l + (r - l) / 2;
	if (end <= mid) return query(start, end, l, mid, index * 2);
	if (start >= mid + 1) return query(start, end, mid + 1, r, index * 2 + 1);
	return max(query(start, end, l, mid, index * 2), query(start, end, mid + 1, r, index * 2 + 1));
}

int main() {
	int n, i;
	int ans = 0;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d%d", &a[i].first, &a[i].second);
		tmp[i] = a[i].second + a[i].first;
	}
	
	sort(a, a + n);
	sort(tmp, tmp + n);
	for (i = 0 ; i < n; i++) {
		if (i == 0 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
	}
	
	for (i = 0 ; i < n; i++) {
		int idx = upper_bound(disc.begin(), disc.end(), a[i].first - a[i].second) - disc.begin() - 1;
		int curr = 1 + query(0, idx, 0, n - 1, 1);
		idx = lower_bound(disc.begin(), disc.end(), a[i].first + a[i].second) - disc.begin();
		update(idx, 0, n - 1, 1, curr);
		ans = max(ans, curr);
	}	
	
	printf("%d\n", ans);
	return 0;
}

