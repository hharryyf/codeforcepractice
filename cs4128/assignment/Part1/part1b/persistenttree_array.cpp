#include <bits/stdc++.h>

#define MAX_SIZE 262192
typedef int ll;
using namespace std;

struct segt {
	int left, right;
	ll lz, rsum;
};

// tree[index] refers to the item at index
segt tree[MAX_SIZE * 40];

// version[i] means the index of the root
int version[MAX_SIZE];
// count the index
int cnt = 0;

int build(int l, int r) {
	int rt = ++cnt;
	tree[rt].rsum = tree[rt].lz = 0;
	if (l == r) {
		tree[rt].left = tree[rt].right = 0;
		return rt;
	}
	
	int mid = l + (r - l) / 2;
	tree[rt].left = build(l, mid);
	tree[rt].right = build(mid + 1, r);
	return rt;
}

void pushdown(int rt, int l, int r) {
	if (rt != 0) {
		if (tree[rt].lz) {
			if (tree[rt].left && tree[rt].right) {
				int mid = l + (r - l)  / 2;
				int len1 = mid - l + 1, len2 = r - mid;
				int nl = ++cnt;
				int nr = ++cnt;
				tree[nl].rsum = tree[rt].lz * len1;
				tree[nr].rsum = tree[rt].lz * len2;
				tree[nl].lz = tree[rt].lz;
				tree[nr].lz = tree[rt].lz;
				tree[nl].left = tree[tree[rt].left].left;
				tree[nl].right = tree[tree[rt].left].right;
				tree[nr].left = tree[tree[rt].right].left;
				tree[nr].right = tree[tree[rt].right].right;
				tree[rt].left = nl;
				tree[rt].right = nr;
			}
			tree[rt].lz = 0;
		}	
	}
}

ll query(int start, int end, int l, int r, int rt) {
	if (start > end || rt == 0) return 0ll;
	pushdown(rt, l, r);
	if (start > r || l > end) return 0ll;
	if (start <= l && r <= end) {
		return tree[rt].rsum;
	}
	int mid = l + (r - l) / 2;
	if (end <= mid) {
		return query(start, end, l, mid, tree[rt].left);
	}
	
	if (start >= mid + 1) {
		return query(start, end, mid + 1, r, tree[rt].right);
	}
	
	return query(start, end, l, mid, tree[rt].left) + query(start, end, mid + 1, r, tree[rt].right);
}

int update(int start, int end, int l, int r, int rt, ll val) {
	if (start > end || rt == 0) return rt;
	int curr = ++cnt;
	pushdown(rt, l, r);
	
	tree[curr].left = tree[rt].left, tree[curr].right = tree[rt].right;
	tree[curr].rsum = tree[rt].rsum;
	tree[curr].lz = tree[rt].lz;
	
	if (start > r || l > end) return curr;
	
	if (start <= l && r <= end) {
		tree[curr].rsum = val * (r - l + 1);
		tree[curr].lz = val;
		return curr;
	}
	
	int mid = l + (r - l) / 2;
	if (end <= mid) { 
		tree[curr].left = update(start, end, l, mid, tree[rt].left, val);
	} else if (start >= mid + 1) {
		tree[curr].right = update(start, end, mid + 1, r, tree[rt].right, val);
	} else {
		tree[curr].left = update(start, end, l, mid, tree[rt].left, val);
		tree[curr].right = update(start, end, mid + 1, r, tree[rt].right, val);
	}
	
	ll c1 = tree[curr].left == 0 ? 0 : tree[tree[curr].left].rsum;
	ll c2 = tree[curr].right == 0 ? 0 : tree[tree[curr].right].rsum;
	tree[curr].rsum = c1 + c2;
	return curr;
}


int n, q;

char str[4];


ll queryversion(int start, int end, int vs) {
	// cout << "qr " << version[vs] << " " << vs << endl;
	return query(start, end, 0, n , version[vs]);
}

/* note that query is [l,r)*/
int main() {
	int vs = 0;
	scanf("%d", &n);
	version[vs++] = build(0, n);
	scanf("%d", &q);
	ll lst = 0;
	while (q > 0) {
		scanf("%s", str);
		if (str[0] == 'U') {
			int l, r;
			ll val;
			scanf("%d%d%d", &l, &r, &val);
		    //l = l ^ lst;
		    //r = r ^ lst;
		    //val = val ^ lst;
			version[vs] = update(l, r-1, 0, n, version[vs-1], val);
			//cout << "--" << version[vs] << endl; 
			vs++;
		} else {
			int v, l, r;
			scanf("%d%d%d", &v, &l, &r);
			//v = v ^ lst;
			//l = l ^ lst;
			//r = r ^ lst;
			lst = queryversion(l, r-1, v);
			printf("%d\n", lst);
		}
		q--;
	}
	
	exit(0);
	return 0;
}
