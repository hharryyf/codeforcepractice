#include <bits/stdc++.h>
#define MAX_SIZE 611
using namespace std;

int n;

vector<double> disc;

double tmp[MAX_SIZE];

struct segt {
	int lz;
	double rsum; 
};

segt tree[MAX_SIZE];

struct line {
	double x1, x2, y;
	int event;
};

static bool cmp(const line &a, const line &b) {
	if (a.y != b.y) return a.y < b.y;
	return a.event > b.event;
}

vector<line> rec;

/*
	each node of the tree represents the status of the interval, not end points!!
*/

void init() {
	int i;
	for (i = 0 ; i < MAX_SIZE; i++) {
		tree[i].lz = 0;
		tree[i].rsum = 0.0;
		tmp[i] = 0.0;
	}
	rec.clear();
	disc.clear();
}

void pullup(int l, int r, int index) {
	if (l != r) {
		if (tree[index].lz) {
			tree[index].rsum = disc[r+1] - disc[l];
		} else {
			tree[index].rsum = tree[index * 2].rsum + tree[index * 2 + 1].rsum;
		}
	} else {
		if (tree[index].lz) {
			tree[index].rsum = disc[r+1] - disc[l];
		} else {
			tree[index].rsum = 0.0;
		}
	}
}

void update(int start, int end, int l, int r, int index, int val) {
	if (start > end || l > r) return;
	pullup(l, r, index);
	if (start > r || l > end) return;
	if (start <= l && r <= end) {
		tree[index].lz += val;
		pullup(l, r, index);
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (end <= mid) {
		update(start, end, l, mid, index * 2, val);
	} else if (start >= mid + 1) {
		update(start, end, mid + 1, r, index * 2 + 1, val);
	} else {
		update(start, end, l, mid, index * 2, val);
		update(start, end, mid + 1, r, index * 2 + 1, val);
	}
	
	pullup(l, r, index);
}

double query() {
	return tree[1].rsum;
}

int main() {
	double ans = 0.0;
	int n;
	int i = 1, j;
	while (scanf("%d", &n)) {
		if (n == 0) break;
		ans = 0.0;
		double x1, y1, x2, y2;
		init();
		for (j = 0 ; j < n; j++) {
			scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
			tmp[2 * j] = x1;
			tmp[2 * j + 1] = x2;
			rec.push_back(line{x1, x2, y1, 1});
			rec.push_back(line{x1, x2, y2, -1});
		}
		
		sort(tmp, tmp + 2 * n);
		
		for (j = 0 ; j < 2 * n; j++) {
			if (j == 0 || tmp[j] != tmp[j-1]) {
				disc.push_back(tmp[j]);
			}
		}
		
		sort(rec.begin(), rec.end(), cmp);
		int m = (int) disc.size();
		for (j = 0; j < (int) rec.size() - 1; j++) {
			int lx = lower_bound(disc.begin(), disc.end(), rec[j].x1) - disc.begin();
			int rx = lower_bound(disc.begin(), disc.end(), rec[j].x2) - disc.begin();
			update(lx, rx - 1, 0, m - 2, 1, rec[j].event);
			ans += query() * (rec[j+1].y - rec[j].y);
		}
		printf("Test case #%d\n", i);
		printf("Total explored area: %.2lf\n\n", ans);
		i++;
	}
	return 0;
}
