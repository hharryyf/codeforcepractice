#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 1048597
typedef long long ll;
using namespace std;

unordered_map<int, int> pre;

struct qrs {
	   int l, r, id;
	   bool operator < (qrs other) const {
	   		return r < other.r;
	   }
};

int tree[MAX_SIZE];
int a[MAX_SIZE];
qrs q[MAX_SIZE];
int n;
int ans[MAX_SIZE];

int shift(int x) {
	return x & (-x);
}

void update(int index, int val) {
	 while (index <= n) {
	 	   tree[index] ^= val;
	 	   index += shift(index);
	 }
}

int getans(int index) {
	int ret = 0;
	while (index > 0) ret ^= tree[index], index -= shift(index);
	return ret;
}

int query(int l, int r) {
	return getans(l-1) ^ getans(r);
}

int main() {
	int i, j;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) scanf("%d", &a[i]);
	int m;
	scanf("%d", &m);
	for (i = 1; i <= m; i++) {
		scanf("%d%d", &q[i].l, &q[i].r); 
		q[i].id = i;
	}
	sort(q + 1, q + 1 + m);
	
	for (i = 1, j = 1; i <= m; i++) {
		while (j <= n && j <= q[i].r) {
			  if (pre.find(a[j]) != pre.end()) update(pre[a[j]], a[j]);
			  pre[a[j]] = j;
			  j++;
		}
		ans[q[i].id] = query(q[i].l, q[i].r);
	}
	
	for (i = 1; i <= m; i++) printf("%d\n", ans[i]);
	return 0;
}
