#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 262192
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)
#define MID ((l+r)>>1)
typedef long long ll;
using namespace std;

struct segt {
	// xor, left endpoint
	vector<pair<int, int>> L, R;
	ll ans;
};

segt tree[MAX_SIZE];
int a[MAX_SIZE];
int n, q, x;

void print(segt t) {
	cout << "interval ans= " << t.ans << endl;
	cout << "left sum " << endl;
	for (auto v : t.L) {
		cout << "(" << v.first << ", " << v.second << ") ";
	}
	cout << endl;
	cout << "right sum " << endl;
	for (auto v : t.R) {
		cout << "(" << v.first << ", " << v.second << ") ";
	}
	cout << endl;
}

void change(int index, int pt) {
	tree[index].L.clear();
	tree[index].R.clear();
	tree[index].L.emplace_back(a[pt], pt);
	tree[index].R.emplace_back(a[pt], pt);
	tree[index].ans = (a[pt] >= x);
}
// the focal point of all divide and conquer type
// range tree problems
segt pullup(segt &t1, segt &t2) {
	segt ret;
	ret.ans = t1.ans + t2.ans;
	int i, j, sz1 = (int) t1.R.size(), sz2 = (int) t2.L.size();
	// calculate the cost using a 2 pointers approach
	j = sz2 - 1;
	for (i = 0; i < sz1; ++i) {
		while (j >= 0) {
			int v = t1.R[i].first | t2.L[j].first;
			if (v >= x) {
				--j;
			} else {
				break;
			} 
		}
		
		int lsz = (i == sz1-1 ? (t1.R[i].second - t1.L[0].second + 1) : (-t1.R[i+1].second + t1.R[i].second));
		int rsz = t2.R[0].second - (j == sz2 - 1 ? (t2.R[0].second + 1): t2.L[j+1].second) + 1;
		ret.ans += 1ll * lsz * rsz;
	}
	
	for (auto p : t1.L) ret.L.push_back(p);
	for (auto p : t2.R) ret.R.push_back(p);
	// merge the 2 segments
	for (i = 0 ; i < sz2; ++i) {
		int v = ret.L.back().first | t2.L[i].first;
		if (v != ret.L.back().first) {
			ret.L.emplace_back(v, t2.L[i].second);
		}
	}
	
	for (i = 0 ; i < sz1; ++i) {
		int v = ret.R.back().first | t1.R[i].first;
		if (v != ret.R.back().first) {
			ret.R.emplace_back(v, t1.R[i].second);
		}
	}
	/*
	printf("we merge 2 intervals\n");
	print(t1);
	print(t2);
	cout << "result" << endl;
	print(ret);
	*/
	return ret;
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		change(index, l);
		return;
	}
	
	build(l, MID, LEFT);
	build(MID + 1, r, RIGHT);
	tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

void update(int pt, int l, int r, int index, int val) {
	if (l > r || pt < l || pt > r) return;
	if (l == r && r == pt) {
		a[pt] = val;
		change(index, pt);
		return;
	}
	
	if (pt <= MID) {
		update(pt, l, MID, LEFT, val);
	} else {
		update(pt, MID + 1, r, RIGHT, val);
	}
	
	tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

segt query(int start, int end, int l, int r, int index) {
	if (start > r || l > end || l > r || start > end) return tree[0];
	if (start <= l && r <= end) return tree[index];
	if (end <= MID) {
		return query(start, end, l, MID, LEFT);
	} else if (start >= MID + 1) {
		return query(start, end, MID + 1, r, RIGHT);
	} 
	
	auto t1 = query(start, end, l, MID, LEFT);
	auto t2 = query(start, end, MID + 1, r, RIGHT);
	return pullup(t1, t2);
}

int main() {
	int i;
	scanf("%d%d%d", &n, &q, &x);
	for (i = 1; i <= n; ++i) scanf("%d", &a[i]);
	build(1, n, 1);
	while (q > 0) {
		int tp, y, z;
		scanf("%d%d%d", &tp, &y, &z);
		if (tp == 1) {
			update(y, 1, n, 1, z);
		} else {
			printf("%I64d\n", query(y, z, 1, n, 1).ans);
		}
		--q;
	}
	return 0;
}