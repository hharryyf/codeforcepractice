#include <bits/stdc++.h>
#define MAX_SIZE 262192
using namespace std;

struct paper {
	int tree[MAX_SIZE];
	int L, R;
	int ivt = 0;
	int n;
	int shift(int x) {
		return x & (-x);
	}

	void update(int pos, int val) {
		if (pos <= 0) return;
		while (pos <= n) {
			tree[pos] += val;
			pos += shift(pos);
		}
	}

	int query(int pos) {
		int ret = 0;
		while (pos > 0) {
			ret += tree[pos];
			pos -= shift(pos);
		}
		
		return ret;
	}

	int getlen(int l, int r) {
		// check whether the paper is inverted
		// cout << L << " -- " << R << endl;
		if (!ivt) {
			l = l + L - 1, r = r + L - 1;
			return query(r) - query(l - 1);
		} 
		auto l1 = R - r + 1, r1 = R - l + 1;
		// cout << "query " << l1 << " " << r1 << endl;
		return query(r1) - query(l1 - 1);
	}
	
	void fold(int len) {
		vector<int> ret;
		int i, j;
		if (2 * len <= R - L + 1) {
			if (!ivt) {
				for (i = L; i <= len + L - 1; ++i) ret.push_back(query(i) - query(i-1));
				for (i = L; i <= len + L - 1; ++i) update(i, -ret[i-L]);
				for (i = len + L, j = (int) ret.size() - 1; i <= 2 * len + L - 1; ++i, --j) update(i, ret[j]);
				L = L + len;
			} else {
				for (i = R; i >= R - len + 1; --i) ret.push_back(query(i) - query(i-1));
				for (i = R, j = 0; i >= R - len + 1; --i, ++j) update(i, -ret[j]);
				for (i = R - len, j = (int) ret.size() - 1; i >= R - 2 * len + 1; --i, --j) update(i, ret[j]);
				R = R - len;
			}
		} else {
			len = R - L + 1 - len;
			if (!ivt) {
				for (i = R; i >= R - len + 1; --i) ret.push_back(query(i) - query(i-1));
				for (i = R, j = 0; i >= R - len + 1; --i, ++j) update(i, -ret[j]);
				for (i = R - len, j = (int) ret.size() - 1; i >= R - 2 * len + 1; --i, --j) update(i, ret[j]);
				R = R - len;
			} else {
				for (i = L; i <= len + L - 1; ++i) ret.push_back(query(i) - query(i-1));
				for (i = L; i <= len + L - 1; ++i) update(i, -ret[i-L]);
				for (i = len + L, j = (int) ret.size() - 1; i <= 2 * len + L - 1; ++i, --j) update(i, ret[j]);
				L = L + len;
			}
			ivt ^= 1;
		}
	}
};

paper p;

int main() {
	int q, i;
	scanf("%d%d", &p.n, &q);
	for (i = 1; i <= p.n; ++i) p.update(i, 1);
	p.L = 1, p.R = p.n;
	
	while (q > 0) {
		int tp;
		scanf("%d", &tp);
		if (tp == 1) {
			int v;
			scanf("%d", &v);
			p.fold(v);
		} else {
			int l, r;
			scanf("%d%d", &l, &r);
			printf("%d\n", p.getlen(l+1, r));
		}
		q--;
	}
	return 0;
}