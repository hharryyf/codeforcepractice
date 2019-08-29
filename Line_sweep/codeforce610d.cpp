#include <bits/stdc++.h>

#define MAX_SIZE 524298
#define IN 1
#define OUT -1
using namespace std;

typedef long long Long;

int n;
/*
 	something special on this problem, consider the parenthesis property
 	we don't need to lazy propagate!
*/
typedef struct segtree {
	Long rangesum;
	Long lazy;
} segmenttree;

segmenttree tree[MAX_SIZE];

Long arr[MAX_SIZE >> 1];

typedef struct interval {
	Long l ,r ,y;
	int event;
} Interval;

vector<Interval> intervals;
vector<Long> mymap;

static bool cmp(const Interval &iv1, const Interval &iv2) {
	if (iv1.y != iv2.y) {
		return iv1.y < iv2.y;
	}
	
	return iv1.event < iv2.event;
}

void update(int start, int end, int l, int r, int index, int value);

int main(int argc, char *argv[]) {
	int i;
	scanf("%d", &n);
	for (i = 0 ; i < n; i++) {
		Long a, b, c, d;
		scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
		Interval it;
		if (b > d) {
			swap(b, d);
		}
		
		if (a > c) {
			swap(a, c);
		}
		
		it.l = a, it.r = c + 1, it.y = b, it.event = IN;
		intervals.push_back(it);
		it.l = a, it.r = c + 1, it.y = d + 1, it.event = OUT;
		intervals.push_back(it);
		arr[i] = a;
		arr[i + n] = c + 1;
	}
	
	sort(arr, arr + 2 * n);
	// store all the x coordinate inside the mymap vector in ascending order
	for (i = 0 ; i < 2 * n; i++) {
		if (i == 0) {
			mymap.push_back(arr[i]);
		} else {
			if (arr[i] != arr[i-1]) {
				mymap.push_back(arr[i]);
			}
		}
	}
	
	sort(intervals.begin(), intervals.end(), cmp);
	Long ans = 0ll;
	for (i = 0 ; i < ((int) intervals.size()) - 1; i++) {
		int start = lower_bound(mymap.begin(), mymap.end(), intervals[i].l) - mymap.begin();
		int end = lower_bound(mymap.begin(), mymap.end(), intervals[i].r) - mymap.begin();
		update(start, end - 1, 0, (int) mymap.size() - 2, 1, intervals[i].event);
		ans += tree[1].rangesum * (intervals[i + 1].y - intervals[i].y);
		// cout << intervals[i].l << " " << intervals[i].r << " " << ans << endl;
	}
	
	cout << ans << endl;
	return 0;
}

void update(int start, int end, int l, int r, int index, int value) {
	if (start > end || l > r) return;
	if (start > r || end < l) return;
	if (start <= l && r <= end) {
		tree[index].lazy += value;
		if (tree[index].lazy > 0) {
			tree[index].rangesum = mymap[r + 1] - mymap[l];
		} else {
			if (l == r) {
				tree[index].rangesum = 0;
			} else {
				tree[index].rangesum = tree[index * 2].rangesum + tree[index * 2 + 1].rangesum;
			}
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (mid >= end) {
		update(start, end, l, mid, index * 2, value);
	} else if (start >= mid + 1) {
		update(start, end, mid + 1, r, index * 2 + 1, value);
	} else {
		update(start, end, l, mid, index * 2, value);
		update(start, end, mid + 1, r, index * 2 + 1, value);
	}
	
	if (tree[index].lazy > 0) {
		tree[index].rangesum = mymap[r + 1] - mymap[l];
	} else {
		if (l == r) {
			tree[index].rangesum = 0;
		} else {
			tree[index].rangesum = tree[index * 2].rangesum + tree[index * 2 + 1].rangesum;
		}
	}
	
}

