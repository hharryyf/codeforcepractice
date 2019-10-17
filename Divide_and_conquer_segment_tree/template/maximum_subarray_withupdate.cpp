#include <bits/stdc++.h>
#define MAX_SIZE 524292

typedef long long ll;

using namespace std;

ll arr[MAX_SIZE >> 1];

struct segt {
	ll maxl, maxr, value, rsum;
};

/* 
   1 a b query [a, b] maximum subarray sum
   2 a b   change arr[a] to b
*/

segt tree[MAX_SIZE];

segt pullup(segt t1, segt t2) {
	segt t;
	t.maxl = max(t1.maxl, t1.rsum + t2.maxl);
	t.maxr = max(t2.maxr, t2.rsum + t1.maxr);
	t.rsum = t1.rsum + t2.rsum;
	t.value = max(max(t1.value, t2.value), t1.maxr + t2.maxl);
	return t;
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index].maxl = tree[index].maxr = tree[index].value = arr[l];
		tree[index].rsum = arr[l];
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index] = pullup(tree[index * 2], tree[index * 2 + 1]);
}

segt query(int start, int end, int l, int r, int index) {
	if (start > end || l > r || start > r || l > end) return segt{0,0,0,0};
	if (start <= l && r <= end) return tree[index];
	int mid = l + (r - l) / 2;
	if (end <= mid) return query(start, end, l, mid, index * 2);
	if (start >= mid + 1) return query(start, end, mid + 1, r, index * 2 + 1);
	return pullup(query(start, end, l, mid, index * 2), query(start, end, mid + 1, r, index * 2 + 1));
}

void update(int pt, int l, int r, int index, ll val) {
	if (l > r) return;
	if (pt == l && r == pt) {
		tree[index].maxl = tree[index].maxr = tree[index].value = val;
		tree[index].rsum = val;
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (pt <= mid) {
		update(pt, l, mid, index * 2, val);
	} else {
		update(pt, mid + 1, r, index * 2 + 1, val);
	}
	
	tree[index] = pullup(tree[index * 2], tree[index * 2 + 1]);
}

ll jury(int a, int b) {
	ll curr = arr[a];
	ll ans = arr[a];
	int i;
	for (i = a + 1; i <= b; i++) {
		if (curr < 0) {
			curr = arr[i];
		} else {
			curr = curr + arr[i];
		}
		ans = max(curr, ans);
	}
	
	return ans;
}

int main(int argc, char *argv[]) {
	int n;
	assert(argc == 2);
	int T = atoi(argv[1]);
	int j = 1;
	int i;
	srand(time(NULL));
	for (j = 1; j <= T; j++) {
		n = rand() % 5500 + 200;
		for (i = 1; i <= n; i++) {
			arr[i] = -500000 + rand() % 100000000;
		}
		build(1, n, 1);
		int q;
		q = rand() % 5500 + 200;
		bool fail = false;
		while (q > 0) {
			int t, l, r;
			t = 1 + rand() % 2;
			l = 1 + rand() % n;
			if (t == 1) {
				r = l + rand() % (n - l + 1);
				ll v1 = query(l, r, 1, n, 1).value, v2 = jury(l, r);
				if (v1 != v2) {
					cout << "fail test case " << j << " expected " << v2 << " got " << v1 << endl;
					cout << "current array " << endl;
					for (i = 1; i <= n; i++) {
						cout << arr[i] << " ";
					}
					cout << endl;
					cout << "query l= " << l << " r= " << r << endl;
					fail = true;
					break;
				}
			} else {
				r = -500000 + rand() % 10000000;
				update(l, 1, n, 1, (ll) r);
				arr[l] = (ll) r;
			}
			q--;
		}
		
		if (!fail) {
			cout << "pass test case " << j << endl;
		}
	}
	return 0;
}
