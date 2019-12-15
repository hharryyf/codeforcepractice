#include <bits/stdc++.h>
#define MAX_SIZE 2097242

using namespace std;

char s[MAX_SIZE >> 1];

// invariant left + right + match = len
struct segt {
	int left, right, match, len;
};

segt tree[MAX_SIZE];

int n;

segt pullup(segt t1, segt t2) {
	segt t;
	t.len = t1.len + t2.len;
	t.match = t1.match + t2.match + 2 * min(t1.left, t2.right);
	t.left = t2.left + t1.left - min(t1.left, t2.right);
	t.right = t1.right + t2.right - min(t1.left, t2.right);
	return t;
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index].match = 0;
		tree[index].len = 1;
		if (s[l] == '(') {
			tree[index].left = 1;
			tree[index].right = 0;
		} else {
			tree[index].right = 1;
			tree[index].left = 0;
		}
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

int main() {
	scanf("%s", s);
	n = strlen(s);
	build(0, n - 1, 1);
	int m;
	scanf("%d", &m);
	while (m > 0) {
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%d\n", query(l - 1, r - 1, 0, n - 1, 1).match);
		m--;
	}
	return 0;
}
