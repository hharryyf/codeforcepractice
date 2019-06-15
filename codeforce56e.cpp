#include <bits/stdc++.h>
#define MAX_LEN 262242

using namespace std;

// the order of the domino at index i
int order[MAX_LEN >> 1];
// total number of domino
int n;

const int INF = -1000000000;

typedef struct domino {
	int x;
	int h;
	int id;
} Domino;

int dp[MAX_LEN >> 1];

int ans[MAX_LEN >> 1];

int tree[MAX_LEN];

vector<Domino> arr;

static bool cmp(const Domino &a, const Domino &b) {
	return a.x < b.x;
}

void build(int start, int end, int index);

/* upper index in an sorted array such that value <= arr[index] */
int upperindex(int value);

int query(int start, int end, int l, int r, int index);

int main(int argc, char *argv[]) {
	int i, x, h;
	cin >> n;
	unordered_map<int, int> hash = unordered_map<int, int>();
	
	arr = vector<Domino>();
	for (i = 0 ; i < n; i++) {
		cin >> x >> h;
		Domino d;
		d.x = x;
		d.h = h;
		d.id = i;
		arr.push_back(d);
	}
	
	sort(arr.begin(), arr.end(), cmp);
	/*
	for (i = 0 ; i < n; i++) {
		cout << "index " << i << " " <<arr[i].id << " " << arr[i].x << " " << arr[i].h << endl;
	}*/
	
	build(0, n - 1, 1);
	
	for (i = n - 1; i >= 0; i--) {
		/*
			dp[i] = (j - i) + dp[j] which j is the domino with maximum 
			x + h value that x[i] + h[i] > x[j]
		*/
		int index = upperindex(arr[i].x + arr[i].h - 1);
		if (index <= i) {
			dp[i] = 1;
		} else {
			int rangemax = query(i + 1, index, 0, n - 1, 1);
			//cout << "query at i= " << i << " to " << index << " rangemax is " << rangemax << endl; 
			index = hash[rangemax];
			//cout << "index is " << index << endl;
			dp[i] = (index - i) + dp[index];
		}
		
		ans[arr[i].id] = dp[i]; 
		unordered_map<int, int> :: iterator iter = hash.find(arr[i].x + arr[i].h);
		if (iter != hash.end()) {
			iter->second = i;
		} else {
			hash[arr[i].x + arr[i].h] = i;
		}
	}
	
	for (i = 0 ; i < n; i++) cout << ans[i] << " ";
	cout << endl;
	return 0;
}

/* upper index in an sorted array such that value <= arr[index] */
int upperindex(int value) {
	int low = 0, high = n - 1;
	int ans = -1;
	while (low <= high) {
		int mid = low + (high - low) / 2;
		if (arr[mid].x <= value) {
			ans = max(ans, mid);
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}
	return ans;
}

void build(int start, int end, int index) {
	if (start > end) {
		return;
	}
	
	if (start == end) {
		tree[index] = arr[start].x + arr[start].h;
		return;
	}
	
	build(start, start + (end - start) / 2, index * 2);
	build(1 + start + (end - start) / 2, end, index * 2 + 1);
	tree[index] = max(tree[index * 2], tree[index * 2 + 1]);
}

int query(int start, int end, int l, int r, int index) {
	if (start > end || l > r) {
		return INF;
	}
	
	if (start > r || end < l) {
		return INF;
	}
	
	if (start <= l && r <= end) return tree[index];
	int mid = l + (r - l) / 2;
	return max(query(start, end, l, mid, index * 2), query(start, end, mid + 1, r, index * 2 + 1));
}
