#include <bits/stdc++.h>
#define MAX_SIZE 524312
#define MOD 1000000000

typedef long long Long;

using namespace std;

typedef struct segt {
	// let s0 represents fib(0) * a[l] + fib(1) * a[l + 1] + ... + fib(r - l) * a[r]
	// let s1 represents fib(1) * a[l] + fib(2) * a[l + 1] + ... + fib(r - l + 1) * a[r]
	Long s0, s1;
	// let lazy be the update tag of the node
	Long lazy;
	// length of the current interval
	int len;
} segmenttree;

segmenttree tree[MAX_SIZE];

Long fib[MAX_SIZE >> 1];

Long fibprefix[MAX_SIZE >> 1];

int n;

void build(int l, int r, int index);

void update(int pt, int l, int r, int index, Long value);

void increment(int start, int end, int l, int r, int index, Long value);

segmenttree query(int start, int end, int l, int r, int index);

void update(int start, int end, int l, int r, int index, Long value);

int arr[MAX_SIZE >> 1];

int main(int argc, char *argv[]) {
	int i, q;
	scanf("%d%d", &n, &q);
	for (i = 0 ; i <= n; i++) {
		if (i == 0) {
			fib[i] = 1;
			fibprefix[i] = 1;
		} else if (i == 1) {
			fib[i] = 1;
			fibprefix[i] = 2;
			scanf("%d", &arr[i]);
		} else {
			fib[i] = (fib[i - 1] + fib[i - 2]) % MOD;
			fibprefix[i] = (fib[i] + fibprefix[i-1]) % MOD;
			scanf("%d", &arr[i]);
		}
	}
	
	build(1, n, 1);
	/*
	for (i = 1; i <= n; i++) {
		printf("%lld ", query(i, i, 1, n, 1).s0);
	}
	printf("\n");
	*/
	while (q > 0) {
		int t, l, r;
		Long v;
		scanf("%d", &t);
		if (t == 1) {
			scanf("%d%lld", &l, &v);
			update(l, l, 1, n, 1, v);
		} else if (t == 2) {
			scanf("%d%d", &l, &r);
			printf("%lld\n", query(l, r, 1, n, 1).s0);
		} else if (t == 3) {
			scanf("%d%d%lld", &l, &r, &v);
			increment(l, r, 1, n, 1, v);
			/*
			for (i = 1; i <= n; i++) {
				printf("%lld ", query(i, i, 1, n, 1).s0);
			}
			printf("\n");*/
		}
		q--;
	}
	return 0;
}


// merge the result of [l, mid] and [mid + 1, r] to [l, r]
// 
segmenttree merge_interval(segmenttree t1, segmenttree t2) {
	segmenttree t;
	t.lazy = 0ll;
	t.len = t1.len + t2.len;
	Long coeff0 = (t2.s1 * (t1.len > 0 ? fib[t1.len - 1] : 0ll) 
				 + t2.s0 * (t1.len > 1 ? fib[t1.len - 2] : 0ll)) % MOD;
	Long coeff1 = (t2.s1 * fib[t1.len] + t2.s0 * (t1.len > 0 ? fib[t1.len - 1] : 0ll)) % MOD;
	// TODO, merge s0, s1
	t.s0 = (t1.s0 + coeff0) % MOD;
	t.s1 = (t1.s1 + coeff1) % MOD;
	
	return t;
}

void lazy_propagation(int index, int l, int r) {
	if (tree[index].lazy != 0) {
		tree[index].s0 += fibprefix[r - l] * tree[index].lazy;
		tree[index].s1 += (fibprefix[r - l + 1] - 1) * tree[index].lazy;
		tree[index].s0 %= MOD;
		tree[index].s1 %= MOD;
		if (l != r) {
			tree[index * 2].lazy = (tree[index * 2].lazy + tree[index].lazy) % MOD;
			tree[index * 2 + 1].lazy = (tree[index * 2 + 1].lazy + tree[index].lazy) % MOD;
		}
		
		tree[index].lazy = 0ll;
	}
}


segmenttree query(int start, int end, int l, int r, int index) {
	segmenttree t;
	t.s0 = t.s1 = 0ll, t.lazy = 0ll, t.len = 0;
	if (start > end || l > r) return t;
	lazy_propagation(index, l, r);
	if (start > r || l > end) return t;
	if (start <= l && r <= end) {
		//cout << tree[index].s0 << " " << tree[index].s1 << " " << tree[index].len 
		//	 << " <- " << start << " " << end << " " << l << " " << r << endl;
		return tree[index];
	}
	
	int mid = l + (r - l) / 2;
	
	
	if (end <= mid) {
		return query(start, end, l, mid, index * 2);
	} else if (start >= mid + 1) {
		return query(start, end, mid + 1, r, index * 2 + 1);
	} 
	
	segmenttree q1 = query(start, end, l, mid, index * 2);
	segmenttree q2 = query(start, end, mid + 1, r, index * 2 + 1);
	t =  merge_interval(q1, q2);
	
	//cout << q1.s0 << " " << q1.s1 << " " << q2.s0 << " " << q2.s1 
	//	 << " <- " << start << " " << end << " -> " << t.s0 << " " << t.s1 << endl;
	// cout << "query length " << q1.len << " and " << q2.len << " -> " << t.len << endl;
	return t;
}


void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index].s0 = tree[index].s1 = arr[l];
		tree[index].len = 1;
		tree[index].lazy = 0ll;
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index] = merge_interval(tree[index * 2], tree[index * 2 + 1]);
}

// increment all values from start to end by value
void increment(int start, int end, int l, int r, int index, Long value) {
	if (l > r || start > end) return;
	lazy_propagation(index, l, r);
	if (start > r || end < l) return;
	if (start <= l && r <= end) {
		tree[index].s0 = (tree[index].s0 + value * fibprefix[r - l]) % MOD;
		tree[index].s1 = (tree[index].s1 + value * (fibprefix[r - l + 1] - 1)) % MOD;
		if (l != r) {
			tree[index * 2].lazy = (tree[index * 2].lazy + value) % MOD;
			tree[index * 2 + 1].lazy = (tree[index * 2 + 1].lazy + value) % MOD;
		}
		return;
	}
	
	int mid = l + (r - l)  / 2;
	increment(start, end, l, mid, index * 2, value);
	increment(start, end, mid + 1, r, index * 2 + 1, value);
	tree[index] = merge_interval(tree[index * 2], tree[index * 2 + 1]);	
}

// update arr[pt] to value
void update(int start, int end, int l, int r, int index, Long value) {
	if (l > r) return;
	lazy_propagation(index, l, r);
	
	if (start > r || end < l) return;
	if (start <= l && r <= end) {
		tree[index].s0 = value;
		tree[index].s1 = value;
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, index * 2, value);
	update(start, end, mid + 1, r, index * 2 + 1, value);
	tree[index] = merge_interval(tree[index * 2], tree[index * 2 + 1]);	
}
