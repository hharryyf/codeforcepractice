#include <bits/stdc++.h>
#define MAX_SIZE 262192
typedef long long ll;

using namespace std;

struct segt {
	int rlds, rlis;
	int llds, llis;
	int len;
	ll rmax, rsum, left, right;
};

segt tree[MAX_SIZE];
ll arr[MAX_SIZE];
int n, m;
char s[4];

segt pullup(segt t1, segt t2) {
	segt t;
	t.rmax = max(t1.rmax, t2.rmax);
	t.rsum = t1.rsum + t2.rsum;
	t.left = t1.left;
	t.right = t2.right;
	if (t1.right < t2.left) {
		t.llis = t1.llis + (t1.llis == t1.len) * t2.llis;
		t.rlis = t2.rlis + (t2.rlis == t2.len) * t1.rlis;
		t.llds = t1.llds;
		t.rlds = t2.rlds;
	} else if (t1.right > t2.left) {
		t.llds = t1.llds + (t1.llds == t1.len) * t2.llds;
		t.rlds = t2.rlds + (t2.rlds == t2.len) * t1.rlds;
		t.llis = t1.llis;
		t.rlis = t2.rlis;
	} else {
		t.llds = t1.llds + (t1.llds == t1.len) * t2.llds;
		t.rlds = t2.rlds + (t2.rlds == t2.len) * t1.rlds;
		t.llis = t1.llis + (t1.llis == t1.len) * t2.llis;
		t.rlis = t2.rlis + (t2.rlis == t2.len) * t1.rlis;
	}
	
	t.len = t1.len + t2.len;
	return t;
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index].rmax = tree[index].rsum = tree[index].left = tree[index].right = arr[l];
		tree[index].llis = tree[index].llds = tree[index].rlis = tree[index].rlds = 1;		
		tree[index].len = 1;
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index] = pullup(tree[index * 2], tree[index * 2 + 1]);
}

void update(int pt, int l, int r, int index, ll val) {
	if (l > r) return;
	if (l == pt && r == l) {
		tree[index].rmax = tree[index].rsum = tree[index].left = tree[index].right = val;
		tree[index].llis = tree[index].llds = tree[index].rlis = tree[index].rlds = 1;		
		tree[index].len = 1;
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

segt query(int start, int end, int l, int r, int index) {
	if (start > end || l > r || start > r || l > end) return segt{0,0,0,0,0ll,0ll,0ll,0ll,0ll};
	if (start <= l && r <= end) return tree[index];
	int mid = l + (r - l) / 2;
	if (end <= mid) {
		return query(start, end, l, mid, index * 2);
	}
	
	if (start >= mid + 1) {
		return query(start, end, mid + 1, r, index * 2 + 1);
	}
	
	return pullup(query(start, end, l, mid, index * 2), 
				  query(start, end, mid + 1, r, index * 2 + 1));
}

int main() {
	scanf("%d%d", &n, &m);
	int i;
	for (i = 1; i <= n; i++) {
		scanf("%lld", &arr[i]);
	}
	
	build(1, n, 1);
	
	
	
	while (m > 0) {
		int x, y;
		scanf("%s%d%d", s, &x, &y);
		if (s[0] == 'U') {
			update(x, 1, n, 1, (ll) y);
		} else {
			segt t = query(x, y, 1, n, 1);
			// cout << x << " " << y << " " << t.llis << " " << t.len << " " << t.llds << endl;
			if (s[0] == 'M') {
				printf("%lld\n", t.rmax);
			} else if (s[0] == 'S') {
				printf("%lld\n", t.rsum);
			} else if (s[0] == 'I') {
				printf("%d\n", (t.llis == t.len));
			} else {
				printf("%d\n", (t.llds == t.len));
			}
		}
		m--;
	}
	return 0;
}
