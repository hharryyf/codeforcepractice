#pragma GCC optimize(2)
#include <cstdio>
#include <algorithm>
#include <vector>
#define MOD 1000000007
#define MAX_SIZE 262192
typedef long long ll;
using namespace std;

struct segt {
	   int l, r, value;
	   int left, right;
};
	
int cnt = 0;
	
segt tree[MAX_SIZE * 35];
int root[MAX_SIZE];
	
int build(int l, int r) {
	if (l > r) return 0;
	int curr = ++cnt;
	tree[curr].l = l, tree[curr].r = r;
	tree[curr].left = 0, tree[curr].right = 0;
	tree[curr].value = 0;
	if (l == r) {
 	    return curr;
	} 
		
	int mid = l + (r - l) / 2;
	tree[curr].left = build(l, mid);
	tree[curr].right = build(mid + 1, r);
	return curr;
}
	
int inc(int rt, int pos, int val) {
	if (rt == 0 || pos < tree[rt].l || pos > tree[rt].r) return rt;
 	int curr = ++cnt;
    tree[curr] = tree[rt];
    if (pos == tree[rt].l && pos == tree[rt].r) {
		 	tree[curr].value += val;
		 	return curr;
    }
		 
	 int mid = tree[curr].l + (tree[curr].r - tree[curr].l) / 2;
	 if (pos <= mid) {
		 	tree[curr].left = inc(tree[rt].left, pos, val);
	 } else {
		    tree[curr].right = inc(tree[rt].right, pos, val);
	 }
		 
		 tree[curr].value = tree[tree[curr].left].value + tree[tree[curr].right].value;
		 return curr;
}
	
void update(int version, int pos, int val) {
	 root[version] =  inc(root[version - 1], pos, val);
}
	
int getans(int rt1, int rt2, int k) {
	if (tree[rt1].l == tree[rt1].r) return tree[rt1].l;
	int tol = tree[tree[rt2].left].value - tree[tree[rt1].left].value;
	if (tol >= k) {
 	   return getans(tree[rt1].left, tree[rt2].left, k);
	} 
	return getans(tree[rt1].right, tree[rt2].right, k - tol);
}
	
int query(int version1, int version2, int k) {
		// printf("%d %d\n", root[version1 - 1], root[version2]);
	return getans(root[version1 - 1], root[version2], k);
}

vector<int> disc; 
int a[MAX_SIZE], tmp[MAX_SIZE];
int n, q, m;

int getindex(int num) {
	return lower_bound(disc.begin(), disc.end(), num) - disc.begin();
}

int main() {
	scanf("%d%d", &n, &q);
	int i;
	for (i = 0; i < n; i++) {
		scanf("%d", &tmp[i]);
		a[i] = tmp[i];
	}
	
	sort(tmp, tmp + n);
	
	for (i = 0 ; i < n; i++) {
		if (i == 0 || tmp[i] != tmp[i-1]) {
		   disc.push_back(tmp[i]);
		}
	}
	
	m = (int) disc.size();
	
	root[0] = build(0, m - 1);
	
	for (i = 0; i < n; i++) {
		update(i + 1, getindex(a[i]),1);
	}
	
	for (i = 0; i < q; i++) {
		int v1, v2, k;
		scanf("%d%d%d", &v1, &v2, &k);
		printf("%d\n", disc[query(v1, v2, k)]);
	}
	return 0;
}

