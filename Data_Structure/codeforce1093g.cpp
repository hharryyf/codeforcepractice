#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 524292
typedef long long ll;
using namespace std;

int n, k;
struct segt {
	   int rmax, rmin;
	   int rans;
};

segt tree[MAX_SIZE][32];
int b[MAX_SIZE >> 1][5];

void calc(int index, int a[]) {
	 int i, j, len = 1 << k;
	 for (i = 0 ; i < len; i++) {
	 	 tree[index][i].rmax = 0;
	 	 for (j = 0 ; j < k; j++) {
		 	 if (i & (1 << j)) {
			  	tree[index][i].rmax += a[j];
		     } else {
 	     	    tree[index][i].rmax -= a[j];
			 } 
         }
         tree[index][i].rmin = tree[index][i].rmax;
         tree[index][i].rans = 0;
	 }
}

segt pullup(segt t1, segt t2) {
	 segt t;
	 t.rmax = max(t1.rmax, t2.rmax);
	 t.rmin = min(t1.rmin, t2.rmin);
	 t.rans = max(max(t1.rans, t2.rans), max(t1.rmax - t2.rmin, t1.rmin - t2.rmax));
	 return t;
}

void build(int l, int r, int index) {
	 if (l > r) return;
	 int mid = l + (r - l) / 2;
	 if (l == r) {
	 	calc(index, b[l]);
	 	return;
	 }
	 
	 build(l, mid, index * 2);
	 build(mid + 1, r, index * 2 + 1);
	 int i;
	 for (i = 0 ; i < (1 << k); i++) {
	 	 tree[index][i] = pullup(tree[index * 2][i], tree[index * 2 + 1][i]);
	 }
}

void update(int pos, int l, int r, int index) {
	 if (pos < l || l > r || pos > r) return;
	 if (pos == l && l == r) {
	 	calc(index, b[pos]);
	 	return;
	 }
	 
	 int mid = l + (r - l) / 2;
	 if (pos <= mid) {
	 	update(pos, l, mid, index * 2);
	 } else {
	    update(pos, mid + 1, r, index * 2 + 1);
	 }
	 int i;
	 for (i = 0 ; i < (1 << k); i++) {
	 	 tree[index][i] = pullup(tree[index * 2][i], tree[index * 2 + 1][i]);
	 }
}

segt query(int start, int end, int l, int r, int index, int dim) {
	 if (start <= l && r <= end) return tree[index][dim];
	 int mid = l + (r - l) / 2;
	 if (end <= mid) return query(start, end, l, mid, index * 2, dim);
	 if (start >= mid + 1) return query(start, end, mid + 1, r, index * 2 + 1, dim);
	 return pullup(query(start, end, l, mid, index * 2, dim), query(start, end, mid + 1, r, index * 2 + 1, dim)); 
}

int main() {
	scanf("%d%d", &n, &k);
	int i, j;
	for (i = 1; i <= n; i++) {
		for (j = 0 ; j < k; j++) {
			scanf("%d", &b[i][j]);
		}
	}
	
	build(1, n, 1);
	
	int q;
	scanf("%d", &q);
	while (q > 0) {
		  int tp;
		  scanf("%d", &tp);
		  if (tp == 1) {
		  	 int pos;
		  	 scanf("%d", &pos);
		  	 for (i = 0 ; i < k; i++) scanf("%d", &b[pos][i]);
		  	 update(pos, 1, n, 1);
		  } else {
		  	 int l, r;
		  	 scanf("%d%d", &l, &r);
		  	 int ans = query(l, r, 1, n, 1, 0).rans;
		  	 for (i = 1; i < (1 << k); i++) ans = max(ans, query(l, r, 1, n, 1, i).rans);
		  	 printf("%d\n", ans);
		  }
		  
		  q--;
	}
	return 0;
}
