#include <cstdio>
#include <iostream>
#include <algorithm>
#define MAX_SIZE 131081
#define MAX_LEN 13
using namespace std;

long long Fenwick[MAX_SIZE][MAX_LEN];
long long arr[MAX_SIZE];

long long query(int dim, int pos);
void update(int dim, int pos, long long value);

int main(int argc, char *argv[]) {
	int n, k, i, j;
	cin >> n >> k;
	for (i = 1; i <= n; i++) {
		cin >> arr[i];
	}
	// a very misleading part, k+1 not k !!!
	k++;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= k; j++) {
			if (i < j) break;
			if (j == 1) {
				update(j, arr[i], 1);
			} else {
				// dp[i][j] = sum(dp[1][j-1] + dp[2][j-1] + ... +dp[i-1][j])
				long long t = query(j-1, arr[i] - 1);
				update(j, arr[i], t);
			}
		}
	}
	// we want the answer of the prefix sum of all dp[i][k] which 1 <= i <= n
	// hence we query k, n
	cout << query(k, n) << endl;
	return 0;
}

int shift(int x) {
	return (x & (-x));
}

void update(int dim, int pos, long long value) {
	while (pos <= 131072) {
		Fenwick[pos][dim] += value;
		pos += shift(pos);
	}
}

long long query(int dim, int pos) {
	long long t = 0;
	while (pos > 0) {
		t += Fenwick[pos][dim];
		pos -= shift(pos);
	}
	return t;
}
