#include <bits/stdc++.h>
#define MAX_SIZE 2098002
#define NO_VALUE -10000000002ll
typedef long long Long;

using namespace std;

typedef struct segt {
	Long value;
	Long lazy;
} segmenttree; 

segmenttree tree[MAX_SIZE];
Long maxt[MAX_SIZE]; 

/*
	consider the length of the ith array to be l
	the resultant array could be affected by this array in the following way:
	if w >= 2 * l:
		the affect range would be
		arr[1] -> 1 to 1
		arr[2] -> 1 to 2
		arr[3] -> 1 to 3
		arr[4] -> 1 to 4
		...
		arr[l] -> 1 to l
		...
		arr[w- l + 1] ->1 to l
		arr[w- l + 2] -> 2 to l
		arr[w - l + 3] -> 3 to l
		arr[w - l + 4] -> 4 to l
		...
		arr[w] -> l to l
	else if w > l:
		arr[1] -> 1 to min(1, l)
		arr[2] -> max(2 - (w - l), 1) to min(2, l)
		arr[3] -> max(3 - (w - l), 1) to min(3, l)
		arr[4] -> max(4 - (w - l), 1) to min(4, l)
		arr[5] -> max(5 - (w - l), 1) to min(5, l)
		arr[6] -> max(6 - (w - l), 1) to min(6, l)
		...
		arr[w] -> max(w - (w - l), 1) to min(w, l)
*/

void build(int l, int r, int index);

Long rmq(int start, int end, int l, int r, int index);

Long query(int start, int end, int l, int r, int index);

void update(int start, int end, int l, int r, int index, Long value);

int main(int argc, char *argv[]) {
	int n, w;
	int i, len, j;
	scanf("%d%d", &n, &w);
	for (i = 0 ; i < n; i++) {
		scanf("%d", &len);
		// cout << "w= " << w << " len= " << len << endl;
		// build a segment tree of length "len"
		build(1, len, 1);
		if (w >= 2 * len) {
			for (j = 1; j <= len; j++) {
				//cout << i<< " update " << j << " affected by " << 1 << ", " 
				//		 << j << " can be 0" << " increment by " <<  max(rmq(1, j, 1, len, 1), 0ll) << endl;
				update(j, j, 1, w, 1, max(rmq(1, j, 1, len, 1), 0ll));
			}
			
			//cout << i<< " update " << len + 1 << " " << w - len << " affected by " << 1 << ", " 
			//			 << len << " can be 0" << " increment by " <<  max(rmq(1, len, 1, len, 1), 0ll) << endl;
						 
			update(len + 1, w - len, 1, w, 1, max(rmq(1, len, 1, len, 1), 0ll));
			
			int p = 1;
			for (j = w - len + 1; j <= w; j++) {
				//cout << i<< " update " << j << " affected by " << p << ", " 
				//		 << len << " can be 0" << " increment by " <<  max(rmq(p, len, 1, len, 1), 0ll) << endl;
				update(j, j, 1, w, 1, max(rmq(p++, len, 1, len, 1), 0ll));
			}
		} else {
			// cout << "w= " << w << " len= " << len << endl;
			for (j = 1; j <= w; j++) {
				
				if (j <= w - len || j >= len + 1) {
				    //cout << i<< " update " << j << " affected by " << max(j - (w - len), 1) << ", " 
					//	 << min(j, len) << " can be 0" << " increment by " << max(rmq(max(j - (w - len), 1), min(j, len), 1, len, 1), 0ll) << endl;
					update(j, j, 1, w, 1, max(rmq(max(j - (w - len), 1), min(j, len), 1, len, 1), 0ll));
				} else {
					update(j, j, 1, w, 1, rmq(max(j - (w - len), 1), min(j, len), 1, len, 1));
					//cout << i<< " update " << j << " affected by " << max(j - (w - len), 1) << ", " 
					//	 << min(j, len) << " cannot be 0" << " increment by " << rmq(max(j - (w - len), 1), min(j, len), 1, len, 1) << endl;
				}
			}
		}
	}
	
	for (i = 1; i <= w; i++) {
		printf("%lld ", query(i, i, 1, w, 1));
	}
	cout << endl;
	return 0;
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		scanf("%lld", &maxt[index]);
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	maxt[index] = max(maxt[index * 2], maxt[index * 2 + 1]);
}

Long rmq(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return NO_VALUE;
	if (start > r || l > end) return NO_VALUE;
	if (start <= l && r <= end) return maxt[index];
	int mid = l + (r - l) / 2;
	return max(rmq(start, end, l, mid, index * 2), rmq(start, end, mid + 1, r, index * 2 + 1));
}

void update(int start, int end, int l, int r, int index, Long value) {
	if (start > end || l > r || value == NO_VALUE) return;
	if (tree[index].lazy) {
		tree[index].value += tree[index].lazy * ((Long) (r - l + 1));
		if (l != r) {
			tree[index * 2].lazy += tree[index].lazy;
			tree[index * 2 + 1].lazy += tree[index].lazy;
		}
		tree[index].lazy = 0ll;
	}
	
	if (start > r || l > end) {
		return;
	}
	
	if (start <= l && r <= end) {
		tree[index].value += value * ((Long) (r - l + 1));
		if (l != r) {
			tree[index * 2].lazy += value;
			tree[index * 2 + 1].lazy += value;
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, index * 2, value);
	update(start, end, mid + 1, r, index * 2 + 1, value);
	tree[index].value = tree[index * 2].value + tree[index * 2 + 1].value;
}


Long query(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return 0ll;
	if (tree[index].lazy) {
		tree[index].value += tree[index].lazy * ((Long) (r - l + 1));
		if (l != r) {
			tree[index * 2].lazy += tree[index].lazy;
			tree[index * 2 + 1].lazy += tree[index].lazy;
		}
		tree[index].lazy = 0ll;
	}
	
	if (start > r || l > end) {
		return 0ll;
	}
	
	if (start <= l && r <= end) {
		return tree[index].value;
	}
	int mid = l + (r - l) / 2;
	return query(start, end, l, mid, index * 2) + query(start, end, mid + 1, r, index * 2 + 1);
}
