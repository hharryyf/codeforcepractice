#include <cstdio>
#include <iostream>
#define MAX_SIZE 1048596

using namespace std;
typedef long long Long;
// solution to codeforce739c
// using segment tree and divide and conquer

// invariant:
// lefthill >= leftinc, lefthill >= leftdec
// righthill >= rightinc, righthill >= rightdec
// ans >= lefthill, ans >= righthill
typedef struct segmentt {
	// leftend point value
	Long leftval;
	// right end point value
	Long rightval;
	// lazy tag, increment-count
	Long lazy;
	// longest hill include leftend
	int lefthill;
	// longest hill include rightend
	int righthill;
	// longest increasing subarray include leftend
	int leftinc;
	// longest decreasing subarray include leftend
	int leftdec;
	// longest increasing subarray include rightend
	int rightinc;
	// longest decreasing subarray include rightend
	int rightdec;
	// longest hill in the given interval
	int ans;
} segmenttree;

segmenttree tree[MAX_SIZE];

Long arr[300011];

int n;
// build the segment tree
void build(int l, int r, int index);

segmenttree merge_interval(segmenttree t1, segmenttree t2, int l, int r);

void update(int start, int end, int l, int r, Long d, int index);

segmenttree query(int start, int end, int l, int r, int index);

int main(int argc, char *argv[]) {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
	    scanf("%lld", &arr[i]);
	}
	build(1, n, 1);
	int m;
	scanf("%d", &m);
	while (m > 0) {
		int v, u;
		Long d;
		scanf("%d %d %lld", &u, &v, &d);
		update(u, v, 1, n, d, 1);
		segmenttree t = query(1, n, 1, n, 1);
		printf("%d\n", t.ans);
		m--;
	}
	return 0;
}

segmenttree merge_interval(segmenttree t1, segmenttree t2, int l, int r) {
	segmenttree t;
	int mid = l + (r - l) / 2;
	int l1 = mid - l + 1, l2 = r - mid;
	t.leftval = t1.leftval;
	t.rightval = t2.rightval;
	t.lazy = 0;
	if (t1.rightval < t2.leftval) {
		// rightdec cannot be changed
		t.rightdec = t2.rightdec;
		// leftdec cannot be changed
		t.leftdec = t1.leftdec;
		// rightinc could only be affected if t2's rightinc has length l2
		t.rightinc = t2.rightinc + t1.rightinc * (t2.rightinc == l2);
		// leftinc could only be affected similarly
		t.leftinc = t1.leftinc + t2.leftinc * (t1.leftinc == l1);
		// right hill could only be affected similarly
		t.righthill = t2.righthill + t1.rightinc * (t2.righthill == l2);
		// lefthill could be t1's lefthill or t's left inc, dec
		t.lefthill = max(t1.lefthill, max(t.leftdec, t.leftinc));
		if (t1.leftinc == l1) {
			t.lefthill = max(t.lefthill, t1.leftinc + t2.lefthill);
		}
		
		// merge for the answer
		t.ans = max(max(t1.ans, t2.ans), max(t.lefthill, t.righthill));
		t.ans = max(t.ans, t2.lefthill + t1.rightinc);
	} else if (t1.rightval > t2.leftval) {
		t.rightinc = t2.rightinc;
		t.leftinc = t1.leftinc;
		
		t.leftdec = t1.leftdec + t2.leftdec * (t1.leftdec == l1);
		t.rightdec = t2.rightdec + (t2.rightdec == l2) * t1.rightdec;
		t.lefthill = t1.lefthill + t2.leftdec * (t1.lefthill == l1);
		t.righthill = max(t2.righthill, max(t.rightinc, t.rightdec));
		if (t.rightdec >= l2) {
			t.righthill = max(t.righthill, t2.rightdec + t1.righthill);
		}
		t.ans = max(max(t1.ans, t2.ans), max(t.lefthill, t.righthill));
		t.ans = max(t.ans, t1.righthill + t2.leftdec);
	} else {
		t.leftinc = t1.leftinc;
		t.leftdec = t1.leftdec;
		t.rightinc = t2.rightinc;
		t.rightdec = t2.rightdec;
		t.lefthill = t1.lefthill;
		t.righthill = t2.righthill;
		t.ans = max(t1.ans, t2.ans);
	}
	return t;
}

segmenttree query(int start, int end, int l, int r, int index) {
	segmenttree t;
	t.leftval = t.rightval = 0ll;
	t.leftdec = t.rightdec = t.leftinc 
			  = t.rightinc = t.righthill = t.lefthill = t.ans = 0;
	t.lazy = 0;
	if (start > end || l > r) return t;
	if (tree[index].lazy != 0ll) {
		tree[index].leftval += tree[index].lazy;
		tree[index].rightval += tree[index].lazy;
		if (l != r) {
			tree[index * 2].lazy += tree[index].lazy;
			tree[index * 2 + 1].lazy += tree[index].lazy;
		}
		tree[index].lazy = 0ll;
	}
	
	if (start > r || l > end) return t;
	
	if (start <= l && r <= end) {
		return tree[index];	
	}
	
	int mid = l + (r - l) / 2;
	if (mid >= end) {
		return query(start, end, l, mid, index * 2);
	} else if (mid + 1 <= start) {
		return query(start, end, mid + 1, r, index * 2 + 1);
	}
	
	t = merge_interval(query(start, end, l, mid, index * 2), 
					   query(start, end, mid + 1, r, index * 2 + 1), l, r);
	return t;
}

void build(int l, int r, int index) {
	if (l > r) {
		return;
	}
	
	if (l == r) {
		tree[index].rightval = tree[index].leftval = arr[l];
		tree[index].leftinc = tree[index].leftdec = 
		tree[index].rightinc = tree[index].rightdec = 
		tree[index].righthill = tree[index].lefthill = tree[index].ans = 1;
		tree[index].lazy = 0ll;
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index] = merge_interval(tree[index * 2], tree[index * 2 + 1], l, r);
}



void update(int start, int end, int l, int r, Long d, int index) {
	if (start > end || l > r) return;
	if (tree[index].lazy != 0ll) {
		tree[index].leftval += tree[index].lazy;
		tree[index].rightval += tree[index].lazy;
		if (l != r) {
			tree[index * 2].lazy += tree[index].lazy;
			tree[index * 2 + 1].lazy += tree[index].lazy;
		}
		tree[index].lazy = 0ll;
	}
	
	if (start > r || l > end) return;
	if (start <= l && r <= end) {
		tree[index].leftval += d;
		tree[index].rightval += d;
		if (l != r) {
			tree[index * 2].lazy += d;
			tree[index * 2 + 1].lazy += d;
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, d, index * 2);
	update(start, end, mid + 1, r, d, index * 2 + 1);
	tree[index] = merge_interval(tree[index * 2], tree[index * 2 + 1], l, r);
}
