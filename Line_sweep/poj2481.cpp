#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#define MAX_SIZE 131073

using namespace std;

struct cow {
	int st, ed, id;
};

int tree[MAX_SIZE];
vector<cow> event;

int n;

int ans[MAX_SIZE];

void init() {
	event.clear();
	memset(tree, 0, sizeof(tree));
	memset(ans, 0, sizeof(ans));
}

int shift(int x) {
	return (x & (-x));
}

int m = 0;

void update(int pt, int val) {
	while (pt <= m) {
		tree[pt] += val;
		pt = pt + shift(pt);
	}
}

int getans(int pt) {
	int ret = 0;
	while (pt > 0) {
		ret = ret + tree[pt];
		pt = pt - shift(pt);
	}
	
	return ret;
}

int query(int start, int end) {
	return getans(end) - getans(start - 1);
}

static bool cmp(const cow &a, const cow &b) {
	if (a.st != b.st) return a.st < b.st;
	return a.ed > b.ed;
}

int main() {
	
	while (scanf("%d", &n)) {
		m = 0;
		if (n == 0) break;
		int i;
		init();
		for (i = 0 ; i < n; i++) {
			int st, ed;
			scanf("%d%d", &st, &ed);
			m = max(ed+1, m);
			event.push_back(cow{st+1, ed+1, i + 1});
		}
		
		sort(event.begin(), event.end(), cmp);
		
		for (i = 0 ; i < n; i++) {
			if (i > 0 && event[i].st == event[i-1].st && event[i].ed == event[i-1].ed) {
				ans[event[i].id] = ans[event[i-1].id];
			} else {
				ans[event[i].id] = query(event[i].ed, m);
			}
			
			update(event[i].ed, 1);
		}
		// cout << "m= " << m << endl;
		for (i = 1 ; i <= n; i++) {
			printf("%d ", ans[i]);
		}
		printf("\n");
	}	
	return 0;
}
