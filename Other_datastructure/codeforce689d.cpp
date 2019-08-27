#include <bits/stdc++.h>
#define MAX_CHUNK 20
#define MAX_SIZE 272145

using namespace std;

// create a sparse table: dimension[0] is range max of the array a, [1] is range
// min of array b
int table[MAX_CHUNK][MAX_SIZE][2];

// two arrays
int a[MAX_SIZE], b[MAX_SIZE];

// n is the size of the table
int n;

// f[i] is the value of log2(i)
int f[MAX_SIZE];

void buildtable(int end);

int query(int start, int end, int dim);

int findleft(int start);

int findright(int start);

long long bruteforce();

int main(int argc, char *argv[]) {


	while(scanf("%d", &n) != EOF) {
	
	int i, l, r;
	
	long long ans = 0ll;
	
	for (i = 1 ; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	
	f[1] = 0;
	for (i = 1 ; i <= n; i++) {
		scanf("%d", &b[i]);
		if (i >= 2) {
			f[i] = f[i / 2] + 1;
		}
	}
	
	buildtable(n);
	
	for (i = 1; i <= n; i++) {
		l = findleft(i);
		r = findright(i);
		if (l != n + 1 && r != -1) {
			// cout << i << " " << l << " " << r << endl;
			ans += (long long) (r - l + 1);
		}
	}
	#ifdef DEBUG
	long long trueval = bruteforce();
	
	if (trueval != ans) {
		cout << "fail the test case " << "expected: " << trueval << " output: " << ans << endl;
	} else {
		cout << "success" << endl;
	}
	#endif
	cout << ans << endl;
	}
	return 0;
}

long long bruteforce() {
	int i, j, k;
	long long count = 0ll;
	for (i = 1; i <= n; i++) {
		for (j = i; j <= n; j++) {
			int minval = b[i], maxval = a[i];
			for (k = i; k <= j; k++) {
				minval = min(b[k], minval);
				maxval = max(a[k], maxval);
			}
			
			if (minval == maxval) {
				count++;
			}
		}
	}
	
	return count;
}

int findleft(int start) {
	int mid, low = start, high = n;
	int ret = n + 1;
	while (low <= high) {
		mid = low + (high - low) / 2;
		int am = query(start, mid, 0), bm = query(start, mid, 1); 
		if (am == bm) {
			ret = mid;
			high = mid - 1;
		} else if (am < bm) {
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}
	
	return ret;
}

int findright(int start) {
	int mid, low = start, high = n;
	int ret = -1;
	while (low <= high) {
		mid = low + (high - low) / 2;
		int am = query(start, mid, 0), bm = query(start, mid, 1);
		if (am == bm) {
			ret = mid;
			low = mid + 1;
		} else if (am < bm) {
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}
	
	return ret;
}


void buildtable(int end) {
	int i, j;
	for (i = 0 ; i < MAX_CHUNK; i++) {
		for (j = 1 ; j <= end; j++) {
			if (i == 0) {
				table[i][j][0] = table[i][j][1] = j;
			} else {
				if((1 << i) + j > end + 1) {
					break;
				} 
				
				if (a[table[i - 1][j][0]] >= a[table[i-1][j + (1 << (i - 1))][0]]) {
					table[i][j][0] = table[i - 1][j][0];	
				} else {
					table[i][j][0] = table[i - 1][j + (1 << (i - 1))][0];
				}
				
				if (b[table[i - 1][j][1]] <= b[table[i-1][j + (1 << (i - 1))][1]]) {
					table[i][j][1] = table[i - 1][j][1];	
				} else {
					table[i][j][1] = table[i - 1][j + (1 << (i - 1))][1];
				}
			}
		}		
	}
}

int query(int start, int end, int dim) {
	int l = end - start + 1;
	if (dim == 0) {
		return max(a[table[f[l]][start][0]], a[table[f[l]][end - (1 << f[l]) + 1][0]]);
	}
	
	return min(b[table[f[l]][start][1]], b[table[f[l]][end - (1 << f[l]) + 1][1]]);
}


