#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 262192
#define MID ((l+r)>>1)
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)

using namespace std;

int f[MAX_SIZE];

int find(int x) {
	if (f[x] == x) return x;
	return f[x] = find(f[x]);
}

void unionset(int a, int b) {
	int x = find(a), y = find(b);
	f[x] = y;
}

struct segt {
	int ans, l, r;
	int L[5], R[5];
	int lsz, rsz;
};
int K;
segt tree[MAX_SIZE];
vector<int> g[MAX_SIZE];

segt pullup(segt t1, segt t2) {
	int i;
	segt ret;
	ret.l = t1.l, ret.r = t2.r;
	ret.ans = t1.ans + t2.ans;
	ret.lsz = min(K, ret.r - ret.l + 1);
	ret.rsz = min(K, ret.r - ret.l + 1);
	for (i = 0 ; i < t1.lsz; ++i) {
		f[t1.L[i]] = t1.L[i];
	}
	
	for (i = 0; i < t1.rsz; ++i) {
		f[t1.R[i]] = t1.R[i];
	}
	
	for (i = 0 ; i < t2.lsz; ++i) {
		f[t2.L[i]] = t2.L[i];
	}
	
	for (i = 0; i < t2.rsz; ++i) {
		f[t2.R[i]] = t2.R[i];
	}
	
	for (i = t1.r; i > t1.r - t1.rsz; --i) {
		for (auto v : g[i]) {
			int idx = v - t2.l;
			if (idx >= 0 && idx < t2.lsz) {
				int a = find(t2.L[idx]), b = find(t1.R[t1.r-i]);
				if (a != b) {
					ret.ans--;
					unionset(a, b);
				}
			}
		}
	}
	
	for (i = 0; i < t1.lsz; ++i) {
		ret.L[i] = find(t1.L[i]);
	}
	
	for (i = 0 ; i < ret.lsz - t1.lsz; ++i) {
		ret.L[i+t1.lsz] = find(t2.L[i]);
	}
	
	for (i = 0; i < t2.rsz; ++i) {
		ret.R[i] = find(t2.R[i]);
	}
	
	for (i = 0 ; i < ret.rsz - t2.rsz; ++i) {
		ret.R[i+t2.rsz] = find(t1.R[i]);
	}
	
	return ret;
}

void print(segt ret) {
	cout << "print info" << endl;
	cout << ret.l << " " << ret.r << endl;
	cout << ret.lsz << " " << ret.rsz << endl;
	int i;
	for (i = 0 ; i < ret.lsz; ++i) {
		cout << ret.L[i] << " ";
	}
	cout << endl;
	for (i = 0 ; i < ret.lsz; ++i) {
		cout << ret.R[i] << " ";
	}
	cout << endl;
	cout << ret.ans << endl;
	cout << "print end" << endl;
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index].l = l, tree[index].r = l;
		tree[index].ans = 1;
		tree[index].L[0] = l, tree[index].R[0] = r;
		tree[index].lsz = tree[index].rsz = 1;
		return;
	}
	
	build(l, MID, LEFT);
	build(MID + 1, r, RIGHT);
	tree[index] = pullup(tree[LEFT], tree[RIGHT]);
	//print(tree[index]);
}

segt query(int start, int end, int l, int r, int index) {
	if (start > end || l > r || start > r || l > end) return tree[0];
	if (start <= l && r <= end) return tree[index];
	if (end <= MID) return query(start, end, l, MID, LEFT);
	if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
	return pullup(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}

int main() {
	int n, i;
	scanf("%d%d", &n, &K);
	for (i = 0 ; i < MAX_SIZE; ++i) f[i] = i;
	int m;
	scanf("%d", &m);
	for (i = 0 ; i < m; ++i) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].push_back(v2);
		g[v2].push_back(v1);
	}
	
	build(1, n, 1);
	int q;
	scanf("%d", &q);
	while (q > 0) {
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%d\n", query(l, r, 1, n, 1).ans);
		--q;
	}
	return 0;
}