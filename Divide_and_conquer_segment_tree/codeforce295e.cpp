#include <bits/stdc++.h>
#define MAX_SIZE 131082

typedef long long Long;

using namespace std;

Long x[MAX_SIZE], xt[MAX_SIZE], tmp[MAX_SIZE << 1];

// the sorted unique array that stores all possible x values
// we want to query p and return the index of p
vector<Long> arr;

int n, q;

typedef struct segmentt {
	Long num;
	Long rangesum;
	Long diff;
} segmenttree;

segmenttree tree[MAX_SIZE << 2];

int oper[MAX_SIZE][3];

segmenttree merge_interval(segmenttree t1, segmenttree t2, int l, int r);
void update(int pt, int l, int r, int upd, Long d, int index);
segmenttree query(int start, int end, int l, int r, int index);
int getbound(Long value, int isup);

int main(int argc, char *argv[]) {
	int i;
	int index = 0, m;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		scanf("%lld", &x[i]);
		xt[i] = x[i];
		tmp[index++] = x[i];
	}
	
	scanf("%d", &q);
	for (i = 0 ; i < q; i++) {
		scanf("%d%d%d", &oper[i][0], &oper[i][1], &oper[i][2]);
		if (oper[i][0] == 1) {
			tmp[index++] = xt[oper[i][1]] + (Long) oper[i][2];
			xt[oper[i][1]] += oper[i][2];
		}
	}
	
	sort(tmp, tmp + index);

	for (i = 0 ; i < index; i++) {
		if (i == 0) {
			arr.push_back(tmp[i]);
		} else {
			if (tmp[i] != tmp[i-1]) {
				arr.push_back(tmp[i]);
			}
		}
	}
	/*
	for (auto num : arr) {
		cout << num << " ";
	}
	cout << endl;*/
	m = (int) arr.size();
	// insert the points inside the segment tree
	for (i = 1; i <= n; i++) {
		// get the index of the point x[i] in arr
		index = lower_bound(arr.begin(), arr.end(), x[i]) - arr.begin();
		update(index, 0, m - 1, 1, x[i], 1);
	}
	
	for (i = 0 ; i < q; i++) {
		if (oper[i][0] == 1) {
			index = lower_bound(arr.begin(), arr.end(), x[oper[i][1]]) - arr.begin();
			update(index, 0, m - 1, 0, 0, 1);
			// cout << x[oper[i][1]] << "------" << arr[index] << endl;
			x[oper[i][1]] = x[oper[i][1]] + (Long) oper[i][2];
			
			index = lower_bound(arr.begin(), arr.end(), x[oper[i][1]]) - arr.begin();
			// cout << x[oper[i][1]] << "------" << arr[index] << endl;
			update(index, 0, m - 1, 1, x[oper[i][1]], 1);
		} else {
			int l = getbound((Long) oper[i][1], 0);
			int r = getbound((Long) oper[i][2], 1);
			// cout << l << " " << r << " " << oper[i][1] << " " << oper[i][2];
			if (l == -1 || r == -1) {
				cout << 0 << endl;
			} else {
				// cout << " " << arr[l] << " " << arr[r] << endl;
				segmenttree t = query(l, r, 0, m - 1, 1);
				cout << t.diff << endl;
			}
		}
	}
	return 0;
}

int getbound(Long value, int isup) {
	int low = 0, high = (int) arr.size() - 1;
	int ret = -1;
	if (!isup) {
		while (low <= high) {
			int mid = low + (high - low) / 2;
			if (arr[mid] >= value) {
				if (ret == -1) {
					ret = mid;
				} else {
					ret = min(ret, mid);
				}
				high = mid - 1;	
			} else {
				low = mid + 1;
			}
		}
	} else {
		while (low <= high) {
			int mid = low + (high - low) / 2;
			if (arr[mid] <= value) {
				if (ret == -1) {
					ret = mid;
				} else {
					ret = max(ret, mid);
				}
				low = mid + 1;	
			} else {
				high = mid - 1;
			}
		}
	}
	
	return ret;
}

segmenttree merge_interval(segmenttree t1, segmenttree t2) {
	segmenttree t;
	t.rangesum = t1.rangesum + t2.rangesum;
	t.num = t1.num + t2.num;
	t.diff = t1.diff + t2.diff + t1.num * t2.rangesum - t2.num * t1.rangesum;
	return t;
}

void update(int pt, int l, int r, int upd, Long d, int index) {
	if (l > r) return;
	if (pt == l && r == l) {
		// upd == 1 means insert, 0 means delete
		if (upd == 1) {
			tree[index].rangesum = d;
			tree[index].num = 1;
		} else {
			tree[index].rangesum = 0;
			tree[index].num = 0;
		}
		tree[index].diff = 0;
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (pt <= mid) {
		update(pt, l, mid, upd, d, index * 2);
	} else {
		update(pt, mid + 1, r, upd, d, index * 2 + 1);
	}
	
	tree[index] = merge_interval(tree[index * 2], tree[index * 2 + 1]);
}

segmenttree query(int start, int end, int l, int r, int index) {
	segmenttree t;
	t.rangesum = t.num = t.diff = 0;
	if (start > end || l > r) return t;
	if (start > r || l > end) return t;
	if (start <= l && r <= end) return tree[index];
	int mid = l + (r - l) / 2;
	
	
	if (mid >= end) {
		return query(start, end, l, mid, index * 2);
	}
	
	if (mid + 1 <= start) {
		return query(start, end, mid + 1, r, index * 2 + 1);
	}
	
	segmenttree t1 = query(start, end, l, mid, index * 2);
	segmenttree t2 = query(start, end, mid + 1, r, index * 2 + 1);
	t = merge_interval(t1, t2);
	return t;
}
