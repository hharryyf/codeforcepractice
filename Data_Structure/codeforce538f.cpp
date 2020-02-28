#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 262192
#define REP(i,a,b) for(i=a;i<=b;++i)

typedef long long ll;
using namespace std;

struct segt {
    int left, right, value;
};

int a[MAX_SIZE];
int disc[MAX_SIZE];
int tmp[MAX_SIZE];
segt tree[MAX_SIZE * 40];
int root[MAX_SIZE];
int cnt = 0;
int build(int l, int r) {
	if (l > r) return 0;
	int curr = ++cnt;
	if (l == r) return curr;
	int mid = (l + r) >> 1;
	tree[curr].left = build(l, mid);
	tree[curr].right = build(mid + 1, r);
	return curr;
}

int update(int rt, int pos, int l, int r) {
	if (rt == 0 || pos < l || pos > r || l > r) return rt;
	int curr = ++cnt;
	tree[curr] = tree[rt];
	if (l == r && pos == l) {
	   ++tree[curr].value;
	   return curr;
	}
	
	int mid = (l + r) >> 1;
	if (pos <= mid) {
	   tree[curr].left = update(tree[rt].left, pos, l, mid);
	} else {
	   tree[curr].right = update(tree[rt].right, pos, mid + 1, r);
	}
	
	tree[curr].value = tree[tree[curr].left].value + tree[tree[curr].right].value;
	return curr;
}

int query(int rt1, int rt2, int start, int end, int l, int r) {
	if (rt1 > rt2 || start > end || l > r || start > r || l > end) return 0;
	if (start <= l && r <= end) return tree[rt2].value - tree[rt1].value;
	int mid = (l + r) >> 1;
	if (end <= mid) return query(tree[rt1].left, tree[rt2].left, start, end, l, mid);
	if (start >= mid + 1) return query(tree[rt1].right, tree[rt2].right, start, end, mid + 1, r);
	return query(tree[rt1].left, tree[rt2].left, start, end, l, mid) + 
	       query(tree[rt1].right, tree[rt2].right, start, end, mid + 1, r);
}

int main() {
	int i, n, j;
	scanf("%d", &n);
	REP(i, 1, n) {
		scanf("%d", &a[i]);
		tmp[i] = a[i];
	}
	
	sort(tmp + 1, tmp + 1 + n);
	
	int m = 0;
	REP(i, 1, n) {
        if (i == 1 || tmp[i] != tmp[i-1]) disc[m++] = tmp[i];
	}
	
	root[0] = build(0, m - 1);
	
	REP(i, 1, n) {
		int idx = lower_bound(disc, disc + m, a[i]) - disc;
        root[i] = update(root[i-1], idx, 0, m - 1);
	}
	
	// if the root is j then
	// query range is i(j-1)+2, ..., ij+1
	
	REP(i, 1, n-1) {
		int ret = 0;	
        REP(j, 1, n) {
  		    if (1ll * i * (j-1) + 2 > 1ll * n) break;
			// count how many numbers in the range are smaller than a[j]
			int idx = lower_bound(disc, disc + m, a[j]) - disc - 1;
			ret += query(root[i * (j-1) + 1], root[min(i * j + 1, n)], 0, idx, 0, m - 1);   
		}
		printf("%d ", ret);
	}
	printf("\n");
	return 0;
}

