#pragma GCC optimize(3)
#pragma GCC optimize(2)

#include <bits/stdc++.h>
#define MID ((l+r)>>1)
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)
#define MAX_SIZE 262192
using namespace std;

struct segt {
	int L[10], R[10];
	int l, r;
	int ans;
};

segt tree[MAX_SIZE];
int n, m;
int a[10][MAX_SIZE >> 1];

int f[MAX_SIZE << 3];

int idx(int r, int c) {
	return r * m + c;
}

int find(int x) {
	if (x == f[x]) return x;
	return f[x] = find(f[x]);
}

void unionset(int x, int y) {
	int a = find(x), b = find(y);
	f[a] = b;
}


segt pullup(segt t1, segt t2) {
	segt ret;
	int i;
	for (i = 0 ; i < n; ++i) {
		f[t1.L[i]] = t1.L[i];
		f[t1.R[i]] = t1.R[i];
		f[t2.L[i]] = t2.L[i];
		f[t2.R[i]] = t2.R[i];
	}
	ret.l = t1.l, ret.r = t2.r;
	int cnt = 0;
	for (i = 0 ; i < n; ++i) {
		if (a[i][t1.r] == a[i][t2.l] && find(t1.R[i]) != find(t2.L[i])) {
			cnt++;
			unionset(t1.R[i], t2.L[i]);
		}
	}
	
	for (i = 0; i < n; ++i) {
		ret.L[i] = find(t1.L[i]);
		ret.R[i] = find(t2.R[i]);
	}
	
	ret.ans = t1.ans + t2.ans - cnt;
	return ret;
}

void build(int l, int r, int index) {
	int i;
	if (l > r) return;
	if (l == r) {
		for (i = 0 ; i < n; ++i) {
			f[idx(i, l)] = idx(i, l);
		}
		
		for (i = 0 ; i < n - 1; ++i) {
			if (a[i][l] == a[i+1][l]) {
				unionset(idx(i, l), idx(i+1, l));
			}
		}
		
		int cnt = 0;
		for (i = 0 ; i < n; ++i) {
			tree[index].L[i] = tree[index].R[i] = find(idx(i, l));
			if (idx(i, l) == tree[index].L[i]) cnt++;
		}
		tree[index].l = tree[index].r = l;
		tree[index].ans = cnt;
		return;
	}
	
	build(l, MID, LEFT);
	build(MID + 1, r, RIGHT);
	tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

segt query(int start, int end, int l, int r, int index) {
	if (start > end || l > r || start > r || l > end) return tree[0];
	if (start <= l && r <= end) return tree[index];
	if (end <= MID) {
		return query(start, end, l, MID, LEFT);
	}
	
	if (start >= MID + 1) {
		return query(start, end, MID + 1, r, RIGHT);
	}
	
	return pullup(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}

inline int read() {
        int res = 1, Q = 1; char c;
        while( (c = getchar()) < 48 || c > 57)
            if(c == '-') Q = -1;
        if(Q) res = c - 48;
        while( (c = getchar()) >= 48 && c <= 57)
            res = res * 10 + c - 48;
        return res * Q;
}


int main() {
	int q, i, j;
	scanf("%d%d%d", &n, &m, &q);
	for (i = 0 ; i < n; ++i) {
		for (j = 1; j <= m; ++j) {
			a[i][j] = read();
		}
	} 
	
	build(1, m, 1);
	
	while (q > 0) {
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%d\n", query(l, r, 1, m, 1).ans);
		q--;
	}
	return 0;
}