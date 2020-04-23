#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 554
using namespace std;

struct block {
	int cnt[100011];
	int lz;
};

block blk[MAX_SIZE];
int bid[MAX_SIZE * MAX_SIZE];
int n;
int block_size;
int p[MAX_SIZE * MAX_SIZE];
int value[MAX_SIZE * MAX_SIZE];
int arr[MAX_SIZE * MAX_SIZE];

// add val to [l, r]
void update(int l, int r, int val) {
	// cout << "update " << l << " " << r << " by " << val << endl;
	if (l > r) return;
	int i, L = bid[l], R = bid[r];
	if (L != R) {
		for (i = L + 1; i <= R - 1; ++i) {
			blk[i].lz += val;
		}
		
		for (i = (L - 1) * block_size + 1; i <= L * block_size; ++i) {
			--blk[L].cnt[arr[i]];
			if (i < l) {
				arr[i] = arr[i] + blk[L].lz;
			} else {
				arr[i] = arr[i] + blk[L].lz + val;
			}
			++blk[L].cnt[arr[i]];
		}
		blk[L].lz = 0;
		for (i = (R - 1) * block_size + 1; i <= min(n, R * block_size); ++i) {
			--blk[R].cnt[arr[i]];
			if (i > r) {
				arr[i] = arr[i] + blk[R].lz;
			} else {
				arr[i] = arr[i] + blk[R].lz + val;
			}
			++blk[R].cnt[arr[i]];
		}
		blk[R].lz = 0;
	} else {
		for (i = (R - 1) * block_size + 1; i <= min(n, R * block_size); ++i) {
			--blk[R].cnt[arr[i]];
			if (i > r || i < l) {
				arr[i] = arr[i] + blk[R].lz;
			} else {
				arr[i] = arr[i] + blk[R].lz + val;
			}
			++blk[R].cnt[arr[i]];
		}
		blk[R].lz = 0;
	}
}

// count the number of 1,2 in the range [l, r]
int query(int pos) {
	int L = bid[1], R = bid[pos], i;
	int ret = 0;
	if (L != R) {
		for (i = L + 1; i <= R - 1; ++i) {
			if (blk[i].lz <= 1) {
				ret += blk[i].cnt[1 - blk[i].lz];
			}
			
			if (blk[i].lz <= 2) {
				ret += blk[i].cnt[2 - blk[i].lz];
			}
		}
		
		for (i = 1; i <= block_size; ++i) {
			ret += ((arr[i] + blk[1].lz) == 1);
			ret += ((arr[i] + blk[1].lz) == 2);
		}
		
		for (i = (R - 1) * block_size + 1; i <= pos; ++i) {
			ret += ((arr[i] + blk[R].lz) == 1);
			ret += ((arr[i] + blk[R].lz) == 2);
		}
	} else {
		for (i = 1; i <= pos; ++i) {
			ret += ((arr[i] + blk[1].lz) == 1);
			ret += ((arr[i] + blk[1].lz) == 2);
		}
	}
	
	return ret;
}

int main() {
	int i;
	long long ans = 0;
	scanf("%d", &n);
	
	block_size = sqrt(n);
	for (i = 1; i <= n; ++i) {
		scanf("%d", &value[i]);
		p[value[i]] = i;
	}
	
	for (i = 1; i <= n; ++i) {
		bid[i] = (i-1) / block_size + 1;
	}
	
	for (i = 1; i <= n; ++i) {
		blk[bid[i]].cnt[0]++;
	}
	
	for (i = 1; i <= n; ++i) {
		if (p[i] == 1) {
			int r = value[p[i] + 1];
			if (r < i) {
				update(r + 1, i, 1);
			} else {
				update(1, i, 1);
			}
		} else if (p[i] == n) {
			int l = value[p[i] - 1];
			if (l < i) {
				update(l + 1, i, 1);
			} else {
				update(1, i, 1);
			}
		} else {		
			int l = min(value[p[i] - 1], value[p[i] + 1]), r = max(value[p[i] - 1], value[p[i] + 1]);
			if (r  <= i && l <= i) {
				update(r + 1, i, 1);
				update(1, l, -1);
			} else if (l <= i) {
				update(l + 1, i, 1);
			} else {
				update(1, i, 1);
			}
		}
		// cout << "query " << query(i) << endl;
		ans = ans + query(i);
	}
	
	printf("%I64d\n", ans - n);
	return 0;
}