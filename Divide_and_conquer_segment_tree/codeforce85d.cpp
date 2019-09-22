#include <bits/stdc++.h>
#define MAX_SIZE 262222

typedef long long Long;

using namespace std;

Long oper[MAX_SIZE >> 1][2];

char op[5];

typedef struct segt {
	// p0 the sum of all the elements of arr[l] + arr[l + 5] + [l + 10] + ...
	// p1 the sum of all the elements of arr[l + 1] + arr[l + 6] + arr[l + 10] + ...
	// p2 the sum of all elements of arr[l + 2] + .....
	Long p[5];
	// length of existing elements in range[l, r]
	int len;
} segmenttree;

segmenttree tree[MAX_SIZE];

vector<int> arr; 

vector<int> discrete;

void update(int pos, int l, int r, int index, Long value);

int main(int argc, char *argv[]) {
	int m;
	int i;
	Long val;
	scanf("%d", &m);
	for (i = 0 ; i < m; i++) {
		scanf("%s", op);
		if (op[0] == 'a') {
			scanf("%lld", &val);
			oper[i][0] = 1;
			oper[i][1] = val;
			arr.push_back(val);
		} else if (op[0] == 'd') {
			scanf("%lld", &val);
			oper[i][0] = 2;
			oper[i][1] = val;
			arr.push_back(val);
		} else {
			oper[i][0] = 3;
		}
	}
	
	sort(arr.begin(), arr.end());
	for (i = 0 ; i < (int) arr.size(); i++) {
		if (i == 0) {
			discrete.push_back(arr[i]);
		} else {
			if (arr[i] != arr[i-1]) {
				discrete.push_back(arr[i]);
			}
		}
	}
	
	int n = (int) discrete.size();
	
	for (i = 0 ; i < m; i++) {
		if (oper[i][0] == 1) {
			val = lower_bound(discrete.begin(), discrete.end(), oper[i][1]) - discrete.begin();
			update(val, 0, n - 1, 1, oper[i][1]);
		} else if (oper[i][0] == 2) {
			val = lower_bound(discrete.begin(), discrete.end(), oper[i][1]) - discrete.begin();
			update(val, 0, n - 1, 1, 0);
		} else {
			printf("%lld\n", tree[1].p[2]);
		}
	}
	
	return 0;
}

segmenttree merge_interval(segmenttree t1, segmenttree t2) {
	segmenttree t;
	t.len = t1.len + t2.len;
	int i;
	for (i = 0 ; i < 5; i++) {
		t.p[i] = t1.p[i] + t2.p[(i - (t1.len % 5) + 5) % 5];
	}
	return t;
}

void update(int pos, int l, int r, int index, Long value) {
	if (l > r) return;
	if (l == r && l == pos) {
		if (value != 0) {
			tree[index].len = 1;
		} else {
			tree[index].len = 0;
		}
		
		tree[index].p[0] = value;
		tree[index].p[1] = tree[index].p[2] = tree[index].p[3] = tree[index].p[4] = 0;
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (pos <= mid) {
		update(pos, l, mid, index * 2, value);
	} else {
		update(pos, mid + 1, r, index * 2 + 1, value);
	}
	
	tree[index] = merge_interval(tree[index * 2], tree[index * 2 + 1]);
}


