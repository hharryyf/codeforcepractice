#include <bits/stdc++.h>
#define MAX_LEN 524330

using namespace std;

int tree[MAX_LEN][62], lazy[MAX_LEN][62];

char str[MAX_LEN >> 1];
int n, m;

int value(char ch) {
	if (ch <= '9') return ch - '0';
	if (ch >= 'A' && ch <= 'Z') return ch - 'A' + 10;
	return ch - 'a' + 36;
}

char finalans(int i) {
	if (i < 10) return i + '0';
	if (i >= 10 && i <= 35) return i - 10 + 'A';
	return i - 36 + 'a';
}

void build(int l, int r, int index);
void update(int start, int end, int l, int r, int index, char ch);
int query(int l, int r, int index, int target);
void getans(int l, int r, int index);

int main(int argc, char *argv[]) {
	scanf("%d%d", &n, &m);
	int i;
	scanf("%s", str);
	build(0, n - 1, 1);	
	for (i = 0 ; i < m; i++) {
		int l, r;
		char qr[2];
		scanf("%d%d%s", &l, &r, qr);
		int leftmost = query(0, n - 1, 1, l);
		int rightmost = query(0, n - 1, 1, r);
		// cout << l << " " << r << " " << leftmost << " " << rightmost << endl;
		update(leftmost, rightmost, 0, n - 1, 1, qr[0]);
	}
	
	getans(0, n - 1, 1);
	printf("\n");
	return 0;
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index][value(str[l])] = 1;
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index << 1);
	build(mid + 1, r, (index << 1) | 1);
	for (int i = 0 ; i < 62; i++) {
		tree[index][i] = tree[index * 2][i] + tree[index * 2 + 1][i];
	}
}

void getans(int l, int r, int index) {
	if (l > r) return;
	int i;
	if (l == r) {
		for (i = 0 ; i < 62; i++) {
			if (tree[index][i] != 0) {
				printf("%c", finalans(i));
			}
		}
		return;
	}
	
	for (i = 0 ; i < 62; i++) {
		if (lazy[index][i] != 0) {
			if (l != r) {
				lazy[index * 2][i] = 1;
				lazy[index * 2 + 1][i] = 1;
				tree[index * 2][i] = 0;
				tree[index * 2 + 1][i] = 0;
			}
			lazy[index][i] = 0;
		}
	}
	
	int mid = l + (r - l) / 2;
	getans(l, mid, index * 2);
	getans(mid + 1, r, index * 2 + 1);
}

void update(int start, int end, int l, int r, int index, char ch) {
	if (start > end || l > r) return;
	
	int i;
	for (i = 0 ; i < 62; i++) {
		if (lazy[index][i] != 0) {
			if (l != r) {
				lazy[index * 2][i] = 1;
				lazy[index * 2 + 1][i] = 1;
				tree[index * 2][i] = 0;
				tree[index * 2 + 1][i] = 0;
			}
			lazy[index][i] = 0;
		}
	}
	
	if (start > r || l > end) return;
	
	if (start <= l && r <= end) {
		tree[index][value(ch)] = 0;
		lazy[index][value(ch)] = 1;
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, index * 2, ch);
	update(start, end, mid + 1, r, index * 2 + 1, ch);
	
	for (i = 0 ; i < 62; i++) {
		tree[index][i] = tree[index * 2 + 1][i] + tree[index * 2][i];	
	}
}

int query(int l, int r, int index, int target) {
	if (l == r) return l;
	int lsum = 0, i;
	for (i = 0 ; i < 62; i++) {
		if (lazy[index][i] != 0) {
			if (l != r) {
				lazy[index * 2][i] = 1;
				lazy[index * 2 + 1][i] = 1;
				tree[index * 2][i] = 0;
				tree[index * 2 + 1][i] = 0;
			}
			lazy[index][i] = 0;
		}
		
		lsum += tree[index * 2][i];
	}
	
	int mid = l + (r - l) / 2;
	if (lsum >= target) {
		return query(l, mid, index * 2, target);
	}
	
	return query(mid + 1, r, index * 2 + 1, target - lsum);
}
