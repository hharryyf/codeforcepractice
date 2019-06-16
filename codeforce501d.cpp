#include <bits/stdc++.h> 
#define MAX_SIZE 262152
#define CLEAR memset()
using namespace std;

// the size of the permutation
int n;

// p and q
int p[MAX_SIZE];
int q[MAX_SIZE];

// the Fenwick tree for p, q, and ans
int tree[3][MAX_SIZE];

// the order of p and q
int ordp[MAX_SIZE];
int ordq[MAX_SIZE];

// the ord of the ans
int ordans[MAX_SIZE];

// the ans
int ans[MAX_SIZE];

// query rangesum from 0 to n
int query(int arr[], int index);

// helper function shift
int shift(int x);

// update function
void update(int arr[], int index, int delta);

// solve function using binary search
int solve(int arr[], int value);

int main(int argc, char *argv[]) {
	int i;
	cin >> n;
	for (i = 0 ; i < n; i++) {
		cin >> p[i];
		p[i]++;
		update(tree[0], i + 1, 1);
	}
	
	for (i = 0 ; i < n; i++) {
		cin >> q[i];
		q[i]++;
		update(tree[1], i + 1, 1);
	}
	
	for (i = 0 ; i < n; i++) {
		ordp[i] = query(tree[0], p[i]) - 1;
		update(tree[0], p[i], -1);
		ordq[i] = query(tree[1], q[i]) - 1;
		update(tree[1], q[i], -1);
	}
	/*
		for (i = 0 ; i < n; i++) {
			cout << ordp[i] << " ";
		}
		cout << endl;
		for (i = 0 ; i < n; i++) {
			cout << ordq[i] << " ";
		}
		cout << endl;
	*/
	
	int carry = 0;
	for (i = n - 1; i >= 0; i--) {
		ordans[i] = (ordp[i] + ordq[i] + carry) % (n - i);
		carry = (ordp[i] + ordq[i] + carry) / (n - i);
		update(tree[2], i + 1, 1);
		// reuse p[i] as a boolean array, if p[i] == 1 then the ith position is chosen
		p[i] = 0;
	}
	
	// for every i we need to find the index that satisfy
	// 1. query(tree[2], index) == ordans[i] + 1
	// 2. p[index] == 0
	for (i = 0 ; i < n; i++) {
		ans[i] = solve(tree[2], ordans[i] + 1);
		update(tree[2], ans[i], -1);
		p[ans[i]] = 1;
	}
	
	for (i = 0 ; i < n; i++) {
		cout << ans[i] - 1 << " ";
	}
	cout << endl;
	return 0;
}

int solve(int arr[], int value) {
	int low = 0, high = n;
	while (low <= high) {
		int mid = low + (high - low) / 2;
		int current = query(arr, mid);
		if (current == value) {
			if (p[mid] == 0) {
				return mid;
			} else {
				high = mid - 1;
			}
		} else if (current < value) {
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}
	return 0;
}

void update(int arr[], int index, int delta) {
	while (index <= n) {
		arr[index] += delta;
		index += shift(index);
	}
}

int shift(int x) {
	return x & (-x);
}

int query(int arr[], int index) {
	int ans = 0;
	while (index >= 1) {
		ans = ans + arr[index];
		index = index - shift(index);
	}
	return ans;
}
