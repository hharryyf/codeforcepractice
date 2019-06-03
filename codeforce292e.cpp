#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#define MAX_LEN 262221

using namespace std;

// tree performs as the segment tree, we simply establish a maximal
// segment tree and then during each t=1 operation
// copy a[x:x+k-1] to b[y:y+k-1] we simply fix all keys of y:y+k-1 to be y-x
// which is the corresponding position of y
// and then when the query operation t=1 comes, we simply call query(i-1, i-1)
// and if the number is -MAX_LEN, then return b[i-1] directly, otherwise
// return a[i-1-(query(i-1,i-1))]
int tree[MAX_LEN];
int lazy[MAX_LEN];
int a[MAX_LEN];
int b[MAX_LEN];
int n;

// basically set all the value to be -MAX_LEN indicates unmodified
void build(int l, int r, int index);
// query function in seg-tree
int query(int l, int r);
// implements query
int queryUtil(int l, int r, int currentl, int currentr, int index);
// update function
void update(int l, int r, int value);
// implements update
void updateUtil(int l, int r, int currentl, int currentr, int value, int index);

int main(int argc, char *argv[]) {
	int m, i;
	int t;
	int l, r, k, v, shift;
		
	cin >> n >> m;
	for (i = 0 ; i < n; i++) {
		cin >> a[i];
	}
	
	for (i = 0 ; i < n; i++) {
		cin >> b[i];
	}
	
	build(0, n-1, 1);
	
	for (i = 0 ; i < m; i++) {
		cin >> t;
		// cout << m << endl;
		if (t == 2) {
			cin >> v;
			shift = query(v - 1, v - 1);
			//cout << "query on index " << v - 1 << " the shift is " << shift << endl;
			if (shift != -MAX_LEN) {
				//cout << "we have a replacement " << v << " shift " << shift << endl;
				cout << a[v-shift-1] << endl;
			} else {
				//cout << "no replacement "<< endl;
				cout << b[v-1] << endl;
			}		
		} else {
			cin >> l >> r >> k;
			// update the shift from r-1 to r + k - 2 to r - l
			//cout << "shift " << r-1 << " to " << r + k - 2 << " by " << r - l << endl; 
			update(r - 1, r + k - 2, r - l);
		}
		
	}
	return 0;
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index] = -MAX_LEN;
		lazy[index] = -MAX_LEN;
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	lazy[index] = -MAX_LEN;
	tree[index] = -MAX_LEN;
}

int query(int l, int r) {
	return queryUtil(l, r, 0, n-1, 1);
}

int queryUtil(int l, int r, int currentl, int currentr, int index) {
	// invalid range
	if (l > r || currentl > currentr) return -MAX_LEN;
	if (lazy[index] != -MAX_LEN) {
		tree[index] = lazy[index];
		if (currentl != currentr) {
			lazy[2 * index] = lazy[2 * index + 1] = lazy[index];
		}
		lazy[index] = -MAX_LEN;
	}
	// no-overlap
	if (currentl > r || l > currentr) return -MAX_LEN;
	// total-overlap
	if (l <= currentl && currentr <= r) {
		return tree[index];
	}
	
	int mid = currentl + (currentr - currentl) / 2;
	return max(queryUtil(l, r, currentl, mid, index * 2), 
			queryUtil(l, r, mid + 1, currentr, index * 2 + 1));
}

void update(int l, int r, int value) {
	updateUtil(l, r, 0, n-1, value, 1);
}

void updateUtil(int l, int r, int currentl, int currentr, int value, int index) {
	if (l > r || currentl > currentr) return;
	if (lazy[index] != -MAX_LEN) {
		tree[index] = lazy[index];
		if (currentl != currentr) {
			lazy[2 * index] = lazy[2 * index + 1] = lazy[index];
		}
		lazy[index] = -MAX_LEN;
	}
	
	// no-overlap
	if (currentl > r || l > currentr) return;
	
	// total-overlap
	if (l <= currentl && currentr <= r) {
		tree[index] = value;
		if (currentl != currentr) {
			lazy[index * 2] = lazy[index * 2 + 1] = value;
		}
		return;
	}
	
	int mid = currentl + (currentr - currentl) / 2;
	updateUtil(l, r, currentl, mid, value, index * 2);
	updateUtil(l, r, mid + 1, currentr, value, index * 2 + 1);
	tree[index] = max(tree[index * 2], tree[index * 2 + 1]);
}

