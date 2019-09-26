#include <bits/stdc++.h>
#define MAX_SIZE 262192
using namespace std;

typedef struct ball {
	int x, y, c;
} Ball;

set<int> occ[MAX_SIZE];

// we use a line sweep algorithm, note that there's a condition that
// all k types of balls must occur, so that we could easily see that 
// the final answer would lies between some intervals such that this interval
// miss at least one type of balls

int n, k, total;

int tree[MAX_SIZE];

Ball balls[MAX_SIZE];

int xi[MAX_SIZE];

int shift(int x) {
	return x & (-x);
}

void update(int x, int val) {
	while (x <= total) {
		tree[x] += val;
		x += shift(x);
	}
}

int query(int x) {
	if (x <= 0) return 0;
	int ret = 0;
	while (x > 0) {
		ret += tree[x];
		x = x - shift(x);
	}
	
	return ret;
}

static bool cmp(const Ball &a, const Ball &b) {
	if (a.y != b.y) return a.y < b.y;
	return a.x < b.x;
}

int main() {
	int T, i, j, ans = 0;
	set<int> :: iterator iter;
	cin >> T;
	while (T > 0) {
		memset(tree, 0, sizeof(tree));
		scanf("%d%d", &n, &k);
		ans = 0;
		total = 0;
		for (i = 1; i <= n; i++) {
			scanf("%d%d%d", &balls[i].x, &balls[i].y, &balls[i].c);
			xi[++total] = balls[i].x;
		}
		
		sort(xi + 1, xi + 1 + total);
		
		total = unique(xi + 1, xi + 1 + total) - xi - 1;
		// cout << n << endl;
		for (i = 1; i <= n; i++) {
			balls[i].x = lower_bound(xi + 1, xi + total + 1, balls[i].x) - xi;
		}
		/*
		for (i = 1; i <= n; i++) {
			cout << balls[i].x << " ";
		}
		cout << endl;
		*/
		for (i = 1; i <= k; i++) {
			occ[i].clear();
			occ[i].insert(0);
			occ[i].insert(total + 1);
		}
		
		sort(balls + 1, balls + 1 + n, cmp);
		
		for (i = 1, j = 1; i <= n;) {
			for (j = i; j <= n && balls[j].y == balls[i].y; j++) {
				int c = balls[j].c;
				iter = occ[c].lower_bound(balls[j].x);
				int qr = *iter, ql = *(--iter);
				ans = max(ans, query(qr - 1) - query(ql));
			}
			
			while (i < j) {
				occ[balls[i].c].insert(balls[i].x);
				update(balls[i].x, 1);
				i++;
			}
		}
		
		for (i = 1; i <= k; i++) {
			int ql = 0;
			iter = ++occ[i].begin();
			while (iter != occ[i].end()) {
				int qr = *iter;
				ans = max(ans, query(qr - 1) - query(ql));
				ql = qr;
				iter++;
			}
		}
		
		printf("%d\n", ans);
		T--;
	}
	return 0;
}
