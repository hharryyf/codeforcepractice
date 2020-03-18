#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#define MAX_SIZE 2000111
typedef long long ll;
using namespace std;

namespace BIT {
	ll t[MAX_SIZE];
	int n;
	
	void init(int p) {
		n = p;
		fill(t, t + n + 1, 0);
	}
	
	int shift(int x) {
		return x & (-x);
	}
	
	void update(int idx, ll v) {
		if (idx == 0) return;
		while (idx <= n) {
			t[idx] += v;
			idx += shift(idx);
		}
	}
	
	ll query(int pos) {
		ll ret = 0;
		while (pos > 0) {
			ret += t[pos];
			pos -= shift(pos);
		}
		return ret;
	}
}

struct qrs {
	int t, x, y, v, id, si;
};

vector<qrs> vc;
vector<ll> ans;

// suppose that the cost [l, mid] and cost[mid+1, r] are calculated
// we need to consider the merging cost, currently all t[l, mid] <= t[mid+1, r]
// we want to sort vc according to x
// if left(x) <= right(x), we update the y value
// otherwise, we increment the query
void cdq(int l, int r) {
	// cout << l << " " << r << endl;
	if (l >= r) return;
	vector<qrs> tmp;
	vector<pair<int, ll> > del;
	int mid = (l+r) >> 1;
	cdq(l, mid);
	cdq(mid + 1, r);
	int i = l, j = mid + 1;
	while (i <= mid && j <= r) {
		if (vc[i].x <= vc[j].x) {
			BIT::update(vc[i].y, vc[i].v);
			del.push_back(make_pair(vc[i].y, -vc[i].v));
			tmp.push_back(vc[i]);
			i++;
		} else {
			ans[vc[j].id] += BIT::query(vc[j].y) * vc[j].si;
			tmp.push_back(vc[j]);
			j++;
		}
	}
	while (i <= mid) {
		tmp.push_back(vc[i++]);
	}
	
	while (j <= r) {
		ans[vc[j].id] += BIT :: query(vc[j].y) * vc[j].si;
		tmp.push_back(vc[j]);
		j++;
	}
	
	for (i = l; i <= r; ++i) {
		vc[i] = tmp[i-l];
	}
	
	for (i = 0 ; i < (int) del.size(); ++i) {
		BIT::update(del[i].first, del[i].second);
	}
}

int main() {
	int s, m;
	scanf("%d%d", &s, &m);
	BIT::init(m);
	int tp = 0, i = 0;
	ans.push_back(0);
	while (scanf("%d", &tp) != EOF) {
		if (tp == 3) break;
		if (tp == 1) {
			int x, y, a;
			scanf("%d%d%d", &x, &y, &a);
			vc.push_back(qrs{i, x, y, a, 0, 0});
			i++;
		} else {
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			vc.push_back(qrs{i, x1-1, y1-1, 0, (int) ans.size(), 1});
			vc.push_back(qrs{i, x1-1, y2, 0, (int) ans.size(), -1});
			vc.push_back(qrs{i, x2, y1-1, 0, (int) ans.size(), -1});
			vc.push_back(qrs{i, x2, y2, 0, (int) ans.size(), 1});
			i++;
			ans.push_back((ll) s * (x2-x1+1) * (y2-y1+1));
		}
		// cout << tp << endl;
	}
	cdq(0, (int) vc.size() - 1);
	int sz = ans.size();
	for (i = 1; i < sz; ++i) cout << ans[i] << endl;
	return 0;
}