#include <bits/stdc++.h>

#define MOD 777777777
#define MAX_SIZE 262152

typedef long long Long;

using namespace std;

/*
* Let's suppose that tree[i] refers to the range [a, b]
* Then we establish the dp function that dp[a][b][arr[a]][arr[b]]
* = dp[a][(a + b) / 2][arr[a]][arr[(a + b) / 2]] * dp[(a + b) / 2 + 1][b][arr[(a + b) / 2 + 1]][arr[b]]
*/
Long tree[MAX_SIZE][4][4];

int valid[4][4];

int n;

void calculate(int index);

/* initially set all value of arr[i][1][1], arr[i][2][2], arr[i][3][3] to be 1 */
void build(int l, int r, int index);

// update a node's value
// if this update value is 1 to 3 we would block
// the possibility of all the other value
// if it is 0, we would set tree[index][1][1], tree[index][2][2], tree[index][3][3] to be 1
void update(int l, int r, int pos, int index, int value);

int main(int argc, char *argv[]) {
	int m, i, j, k;
	cin >> n >> m;
	for (i = 1; i <= 3; i++) {
		for (j = 1; j <= 3; j++) {
			cin >> valid[i][j];
		}
	}
	
	build(0, n - 1, 1);
	
	for (i = 0 ; i < m; i++) {
		int pos, value;
		Long ans = 0;
		cin >> pos >> value;
		update(0, n - 1, pos - 1, 1, value);
		for (j = 1; j <= 3; j++) {
			for (k = 1; k <= 3; k++) {
				ans = (ans + tree[1][j][k]) % MOD;
			}
		}
		cout << ans % MOD << endl;
	}
	return 0;
}

/* initially set all value of arr[i][1][1], arr[i][2][2], arr[i][3][3] to be 1 */
void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index][1][1] = 1;
		tree[index][2][2] = 1;
		tree[index][3][3] = 1;
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	calculate(index);	
}

void calculate(int index) {
	int i, j, k, l;
	for (i = 1; i <= 3; i++) {
		for (j = 1; j <= 3; j++) {
			tree[index][i][j] = 0;
			for (k = 1; k <= 3; k++) {
				for (l = 1; l <= 3; l++) {
					tree[index][i][j] += tree[index * 2][i][k] * tree[index * 2 + 1][l][j] * valid[k][l];
					tree[index][i][j] %= MOD;
				}
			}		
		}
	}
}

void update(int l, int r, int pos, int index, int value) {
	if (l > r) return;
	if (pos == l && pos == r) {
		if (value == 0) {
			tree[index][1][1] = 1;
			tree[index][2][2] = 1;
			tree[index][3][3] = 1;
		} else {
			tree[index][1][1] = tree[index][2][2] = tree[index][3][3] = 0;
			tree[index][value][value] = 1;			
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (mid >= pos) {
		update(l, mid, pos, index * 2, value);
	} else {
		update(mid + 1, r, pos, index * 2 + 1, value);
	}
	calculate(index);
}
