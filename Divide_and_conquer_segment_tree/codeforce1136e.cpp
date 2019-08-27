#include <bits/stdc++.h>
#define MAX_LEN 262192

using namespace std;

typedef long long Long;

typedef struct segTree {
	Long rangesum;
	Long rangemax;
	Long lazy;
} SegmentTree;

SegmentTree tree[MAX_LEN];

Long a[MAX_LEN >> 1], k[MAX_LEN >> 1], prefix[MAX_LEN >> 1], prefixdeep[MAX_LEN >> 1];

char str[4];

int n, q;

const Long INF = (1ll << 62);

/*
	we are interested in the smallest m > i such that
	a[m] >= a[i] + x + sum(k[j], j = i..m-1)
	and after we find that m we would like to update all numbers from a[i] to a[m-1] to
	a[j] = a[i] + x + sum(k[p], p= i..j-1)
	
	to modify the first inequality we have
	a[m] >= a[i] + x + sum(k[j], j = 1..m-1) - sum(k[j], j = 1..i-1)
	which is
	a[m] - sum(k[j], j = 1..m-1) >= a[i] + x - sum(k[j], j = 1..i-1)
	we let b[i] = a[i] - sum(k[j], j = 1..i-1)
	hence we are interested in the smallest m such that
	b[m] >= b[i] + x
	
	and we note that after the modification, we still need to update all numbers
	from i to m-1, and we can observe that
	we want to change a[i+1] to a[i] + k[i] which is b[i] + sum(k[j], j=1..i-1) + k[i] 
	= b[i] + sum(k[j], j = 1..i) which means that b[i+1] = a[i+1] - sum(k[j],j = 1..i) is
	changed to b[i+1] =  b[i] + sum(k[j], j = 1..i) - sum(k[j],j = 1..i) = b[i]
	
	then a very interesting property could be seen it is we could actually change all terms
	from i to m - 1 to b[i]
	
	And if we want to query(i), we can simply get b[i] + sum(k[j], j = 1..i-1)
	
*/

void build(int l, int r, int index);

void lazypropagate(int l, int r, int index);

Long query(int start, int end, int l, int r, int index);

void update(int start, int end, int l, int r, int index, Long val);

Long inc(int p, int l, int r, int index, int val);

int minindex(int start, int end, int l, int r, int index, Long target);

Long querymax(int start, int end, int l, int r, int index);

int main(int argc, char *argv[]) {
	scanf("%d", &n);
	int i;
	for (i = 1 ; i <= n; i++) {
		cin >> a[i];
	}
	
	for (i = 1 ; i < n; i++) {
		cin >> k[i];
		prefix[i] = prefix[i-1] + k[i];
		prefixdeep[i] = prefixdeep[i-1] + prefix[i]; 
	}
	build(1, n, 1);
	scanf("%d", &q);
	for (i = 0 ; i < q; i++) {
		int l, r;
		scanf("%s%d%d", str, &l, &r);
		if (str[0] == 's') {
			
			cout << (query(l, r, 1, n, 1) + prefixdeep[r-1] - (l >= 2 ? prefixdeep[l-2] : 0ll)) << endl;
		} else if (str[0] == '+') {
			Long target = inc(l, 1, n, 1, r);
			Long tmp = querymax(l + 1, n, 1, n, 1);
			int index;
			if (tmp < target) {
				index = n + 1;
				update(l + 1, index - 1, 1, n, 1, target);
			} else {
				index = minindex(l + 1, n, 1, n, 1, target);
				if (index != MAX_LEN) {
					update(l + 1, index - 1, 1, n, 1, target);
				}
			}
		}
	}
	
	return 0;
}

Long querymax(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return -INF;
	lazypropagate(l, r, index);
	if (start > r || l > end) return -INF;
	if (start <= l && r <= end) return tree[index].rangemax;
	int mid = l + (r - l) / 2;
	if (end <= mid) {
		return querymax(start, end, l, mid, index * 2);
	}
	
	if (mid + 1 <= start) {
		return querymax(start, end, mid + 1, r, index * 2 + 1);
	}
	
	return max(querymax(start, end, l, mid, index * 2), querymax(start, end, mid + 1, r, index * 2 + 1));
}

// return the minimum index such that start <= index <= end and b[index] >= target
// if no such index exists return 0
int minindex(int start, int end, int l, int r, int index, Long target) {
	if (l > r || start > end) return MAX_LEN;
	
	lazypropagate(l, r, index);
	
	if (start > r || end < l) return MAX_LEN;
	
	if (l == r) {
		if (tree[index].rangemax >= target) {
			return l;
		}
		return MAX_LEN;
	}
	
	
	int mid = l + (r - l) / 2;
	if (start <= l && r <= end) {
		if (tree[index * 2].rangemax >= target) {
			return minindex(start, end, l, mid, index * 2, target);
		}
	
		if (tree[index * 2 + 1].rangemax >= target) {
			return minindex(start, end, mid + 1, r, index * 2 + 1, target);
		}
		return MAX_LEN;
	}
	
	return min(minindex(start, end, l, mid, index * 2, target), minindex(start, end, mid + 1, r, index * 2 + 1, target));
}

void lazypropagate(int l, int r, int index) {
	
	if (l > r) return;
	if (l == r) return;
	if (tree[index].lazy == INF) return;
	int mid = l + (r - l) / 2;
	Long len1 = mid - l + 1, len2 = r - mid;
	tree[index * 2].rangesum = tree[index].lazy * len1;
	tree[index * 2 + 1].rangesum = tree[index].lazy * len2;
	tree[index * 2].rangemax = tree[index].lazy;
	tree[index * 2 + 1].rangemax = tree[index].lazy;
	tree[index * 2].lazy = tree[index * 2 + 1].lazy = tree[index].lazy;
	tree[index].lazy = INF;
}

Long query(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return 0ll;
	lazypropagate(l, r, index);
	if (start > r || l > end) return 0ll;
	if (start <= l && r <= end) return tree[index].rangesum;
	int mid = l + (r - l) / 2;
	if (end <= mid) {
		return query(start, end, l, mid, index * 2);
	}
	
	if (mid + 1 <= start) {
		return query(start, end, mid + 1, r, index * 2 + 1);
	}
	
	return query(start, end, l, mid, index * 2) + query(start, end, mid + 1, r, index * 2 + 1);
}



void build(int l, int r, int index) {
	if (l > r) return;
	tree[index].lazy = INF;
	if (l == r) {
		tree[index].rangemax = tree[index].rangesum = a[l] - prefix[l-1];
		return;
	}	
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index].rangemax = max(tree[index * 2].rangemax, tree[index * 2 + 1].rangemax);
	tree[index].rangesum = tree[index * 2].rangesum + tree[index * 2 + 1].rangesum;
}

void update(int start, int end, int l, int r, int index, Long val) {
	if (l > r || start > end) return;
	lazypropagate(l, r, index);
	if (start > r || l > end) {
		return;
	}
	
	if (start <= l && r <= end) {
		tree[index].lazy = (Long) val;
		tree[index].rangesum = (Long) ((Long) (r - l + 1) * (Long) val);
		tree[index].rangemax = (Long) val;
		// cout << "we update " << l << " " << r << " to " << val << endl;
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, index * 2, val);
	update(start, end, mid + 1, r, index * 2 + 1, val);
	tree[index].rangemax = max(tree[index * 2].rangemax, tree[index * 2 + 1].rangemax);
	tree[index].rangesum = tree[index * 2].rangesum + tree[index * 2 + 1].rangesum;
}

Long inc(int p, int l, int r, int index, int val) {
	if (l > r) return 0ll;
	lazypropagate(l, r, index);
	if (l == r) {
		tree[index].rangesum += (Long) val;
		tree[index].rangemax += (Long) val;
		return tree[index].rangemax;
	}
	
	int mid = l + (r - l) / 2;
	
	if (p <= mid) {
		Long ans =  inc(p, l, mid, index * 2, val);
		tree[index].rangemax = max(tree[index * 2].rangemax, tree[index * 2 + 1].rangemax);
		tree[index].rangesum = tree[index * 2].rangesum + tree[index * 2 + 1].rangesum;
		return ans;
	} 
		
	Long ans = inc(p, mid + 1, r, index * 2 + 1, val);
	tree[index].rangemax = max(tree[index * 2].rangemax, tree[index * 2 + 1].rangemax);
	tree[index].rangesum = tree[index * 2].rangesum + tree[index * 2 + 1].rangesum;
	return ans;
}
