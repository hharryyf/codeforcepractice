#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#define MAX_LEN 262211
#define MAX_WALL 101000
using namespace std;


/*
	this problem has a very trivial solution with time complexity O(n^2)
	the idea is let dp[i] refers to the maximum jumping length that ends at i
	dp[i] = max(dp[j]) + 1, for all 0 <= j < i and h[j] <= h[i] - d or h[j] >= h[i] + d
	Note that even if such method will cause TLE, we can see that actually
	only the two interval's current maximum value will affect dp[i].
	Hence we can use a segment tree, and instead of iterate all j to get dp[i],
	we can directly query the two ranges and get a value.
*/
// the wall height and the dp array
long long h[MAX_WALL], dp[MAX_WALL], a[MAX_WALL];
// the maximal segment tree
long long tree[MAX_LEN];
// number of pillars
int n;
// the number of position in the segment tree
int total;
// the mapping array between height and the index in the array
long long mymap[MAX_WALL];

// get the rightmost index that value is less that or equal to value
// note that C++ lower bound is not very convenient for this query
int get_low(long long arr[], long long value, int l, int r);
// get the leftmost index that value is greater than or equal to the current value
int get_high(long long arr[], long long value, int l, int r);
// seg-tree query
long long query(int l, int r, int cl, int cr, int index);
// seg-tree update
void update(int l, int r, int pos, long long value, int index);

int main(int argc, char *argv[]) {
	long long d;
	int i;
	long long ans = 1;
	cin >> n >> d;
	for (i = 0 ; i < n; i++) {
		cin >> h[i];
		a[i] = h[i];
	}
	
	sort(a, a + n);
	// cout << "hello" << endl;
	total = 0;
	mymap[0] = a[0];
	total = 1;
	for (i = 1; i < n; i++) {
		if (mymap[total - 1] != a[i]) {
			mymap[total++] = a[i];
		}
	}
	
	
	dp[0] = 1;
	i = get_low(mymap, h[0], 0, total - 1);
	update(0, total - 1, i, dp[0], 1);
	for (i = 1; i < n; i++) {
		int low = get_low(mymap, h[i] - d, 0, total - 1);
		int high = get_high(mymap, h[i] + d, 0, total - 1);
		// maximum dp[j] such that h[j] <= h[i] - d
		int leftmax = query(0, low, 0, total - 1, 1);
		// maximum dp[j] such that h[j] >= h[i] + d
		int rightmax = query(high, total - 1, 0, total - 1, 1);
		// fix dp[i]
		dp[i] = max(leftmax, rightmax) + 1;
		// update i
		int current = get_low(mymap, h[i], 0, total - 1);
		update(0, total - 1, current, dp[i], 1);
		ans = max(ans, dp[i]);
		
	}
	
	cout << ans << endl;
	/*
	for (i = 0 ; i < n; i++) {
		cout << dp[i] << " ";
	}
	cout << endl; */
	vector<int> t = vector<int>();
	i = n - 1;
	long long current_height = -1;
	while (i >= 0) {
		if (ans == dp[i]) {
			if (t.size() == 0) {
				t.push_back(i+1);
				current_height = h[i];
				ans--;
			} else {
				if (abs(h[i] - current_height) >= d) {
					current_height = h[i];
					t.push_back(i+1);
					ans--;
				}
			}
		}
		i--;
	}
	
	cout << t[t.size() - 1];
	for (i = t.size() - 2; i >= 0; i--) {
		cout << " " << t[i];
	}
	cout << endl;
	return 0;
}

int get_low(long long arr[], long long value, int l, int r) {
	int low = l, high = r;
	int ans = -1;
	while (low <= high) {
		// cout << "debug" << endl;
		int mid = low + (high - low) / 2;
		if (arr[mid] <= value) {
			ans = mid;
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}
	
	return ans;
}

int get_high(long long arr[], long long value, int l, int r) {
	int low = l, high = r;
	int ans = MAX_LEN;
	while (low <= high) {
	    // cout << "debug" << endl;
		int mid = low + (high - low) / 2;
		if (arr[mid] >= value) {
			ans = mid;
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}
	
	return ans;
}

long long query(int l, int r, int cl, int cr, int index) {
	// invalid or no overlap
	if (l > r || cr < l || r < cl || cl > cr) {
		return -1;
	}
	// total overlap
	if (l <= cl && cr <= r) {
		return tree[index];
	}
	// partial overlap
	int mid = cl + (cr - cl) / 2;
	return max(query(l, r, cl, mid, index * 2), query(l, r, mid + 1, cr, index * 2 + 1));
}

void update(int l, int r, int pos, long long value, int index) {
	// invalid range
	if (l > r || pos < l || pos > r) return;
	int mid = l + (r - l) / 2;
	if (pos == l &&  pos == r) {
		tree[index] = value;
		return;
	}
	
	if (pos <= mid) {
		update(l, mid, pos, value, index * 2);
	} else {
		update(mid + 1, r, pos, value, index * 2 + 1);
	}
	
	tree[index] = max(tree[index * 2], tree[index * 2 + 1]);
}
