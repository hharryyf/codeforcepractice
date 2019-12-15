#include <bits/stdc++.h>
#define MAX_SIZE 262222
typedef long long Long;

using namespace std;

/*
	time complexity analysis:
	worst case for the update: the given range has all different colors
	so in total it would cost (r - l + 1) * log(n), but this must have happened
	after (r - l + 1) O(logn) queries so in total the worst case complaxity is
	still O(qlogn) which q is the number of queries, n is the size of the tree
*/

typedef struct segt {
	// the queried answer: colorness
	Long colorness;
	// the color of the segment, 0 means different, otherwise means unique
	Long color;
	// the increment tag, 0 for unchanged
	Long lazyinc;
	// the changed color tag, 0 for unchanged
	Long lazycolor;
} segmenttree;

segmenttree tree[MAX_SIZE];

void update(int start, int end, int l, int r, int index, Long c);
Long query(int start, int end, int l, int r, int index);
void build(int l, int r, int index);

int main(int argc, char *argv[]) {
	int n, m;
	scanf("%d%d", &n, &m);
	
	build(1, n, 1);
	
	while (m > 0) {
		int l, r, t;
		scanf("%d%d%d", &t, &l, &r);
		if (t == 1) {
			Long x;
			scanf("%lld", &x);
			update(l, r, 1, n, 1, x);
		} else {
			printf("%lld\n", query(l, r, 1, n, 1));
		}
		m--;
	}
	/*
	for (int i = 1; i <= n; i++) {
		printf("%d=: %lld\n", i, query(i,i,1,n,1));
	}*/
	return 0;
}

void push_down(int index, int l, int r) {
	if (tree[index].lazycolor != 0) {
		tree[index].color = tree[index].lazycolor;
		if (l != r) {
			tree[index * 2].lazycolor = tree[index].lazycolor;
			tree[index * 2 + 1].lazycolor = tree[index].lazycolor;
		}
		tree[index].lazycolor = 0;
	}	
	
	if (tree[index].lazyinc != 0) {
		tree[index].colorness += tree[index].lazyinc * (r - l + 1);
		if (l != r) {
			tree[index * 2].lazyinc += tree[index].lazyinc;
			tree[index * 2 + 1].lazyinc += tree[index].lazyinc;
		}
		tree[index].lazyinc = 0;
	}
}

void merge_interval(int index, int l, int r) {
	if (l != r) {
		if (tree[index * 2].color == tree[index * 2 + 1].color) {
			tree[index].color = tree[index * 2].color;
		} else {
			tree[index].color = 0;
		}
		
		tree[index].colorness = tree[index * 2 + 1].colorness + tree[index * 2].colorness;
	} 
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index].color = l;
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	merge_interval(index, l, r);
}

// change start to end's color to c
void update(int start, int end, int l, int r, int index, Long c) {
	if (start > end || l > r) return;
	
	push_down(index, l, r);
	if (start > r || l > end) return;
	// currently we can make sure that tree[index].lazycolor = 0 
	// and tree[index].lazyinc = 0
	if (start <= l && r <= end && tree[index].color != 0) {
		tree[index].colorness += (r - l + 1) * llabs(tree[index].color - c);
		if (l != r) {
			tree[index * 2].lazycolor = c;
			tree[index * 2 + 1].lazycolor = c;
			tree[index * 2].lazyinc += llabs(tree[index].color - c);
			tree[index * 2 + 1].lazyinc += llabs(tree[index].color - c);
		}
		tree[index].color = c;
		return;
	}	
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, index * 2, c);
	update(start, end, mid + 1, r, index * 2 + 1, c);
	// at this point the point and its two childs has lazy value 0
	merge_interval(index, l, r);
}

// return the colorness of [start, end]
Long query(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return 0;
	push_down(index, l, r);
	if (start > r || l > end) return 0ll;
	if (start <= l && r <= end) {
		return tree[index].colorness;
	}
	
	int mid = l + (r - l) / 2;
	return query(start, end, l, mid, index * 2) + query(start, end, mid + 1, r, index * 2 + 1);
}
