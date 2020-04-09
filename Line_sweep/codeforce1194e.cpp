#include <bits/stdc++.h>
#define MAX_SIZE 10011
typedef long long ll;
using namespace std;

const int offst = 5002;

struct BIT {
	int tree[MAX_SIZE];
	void init() {
		memset(tree, 0, sizeof(tree));
	}
	
	int shift(int x) {
		return x & (-x);
	}
	
	void update(int pos, int val) {
		pos += offst;
		while (pos < MAX_SIZE) {
			tree[pos] += val;
			pos += shift(pos);
		}
	}
	
	int getans(int pos) {
		pos += offst;
		int ret = 0;
		while (pos > 0) {
			ret += tree[pos];
			pos -= shift(pos);
		}
		return ret;
	}
	
	int query(int l, int r) {
		// cout << "query " << l << " " << r << endl;
		if (l > r) return 0;
		return getans(r) - getans(l-1);
	}
};

BIT t;
ll ans = 0;
// y1,y2 , x
vector<pair<int, pair<int, int>>> ver;
// x1, x2, y
vector<pair<int, pair<int, int>>> hor;

static bool cmp(const pair<int, pair<int, int>> &a, const pair<int, pair<int, int>> &b) {
	return a.second.second > b.second.second;
}

int main() {
	int n, i, j;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		if (x1 == x2) {
			if (y1 > y2) swap(y1, y2);
			ver.push_back(make_pair(x2, make_pair(y1, y2)));
		} else {
			if (x1 > x2) swap(x1, x2);
			hor.push_back(make_pair(y2, make_pair(x1, x2)));
		}
	}
	
	
	sort(ver.begin(), ver.end(), cmp);
	sort(hor.begin(), hor.end());
	int sz1 = (int) ver.size(), sz2 = (int) hor.size();
	for (i = 0 ; i < sz2; ++i) {
		t.init();
		// y2, x
		vector<pair<int, int>> vc;
		for (j = 0 ; j < sz1; ++j) {
			if (ver[j].first <= hor[i].second.second && ver[j].first >= hor[i].second.first
			    && ver[j].second.second >= hor[i].first && ver[j].second.first <= hor[i].first) {
				vc.emplace_back(ver[j].second.second, ver[j].first);
				t.update(ver[j].first, 1);
				//cout << "update " << ver[j].first << " by " << 1 << endl;
			}
		}
		
		for (j = i + 1; j < sz2; ++j) {
			while (!vc.empty()) {
				if (vc.back().first < hor[j].first) {
					t.update(vc.back().second, -1);
					vc.pop_back();
					//cout << "update " << vc.back().second << " by " << -1 << endl;
				} else {
					break;
				}
			}
			
			int cnt = t.query(max(hor[i].second.first, hor[j].second.first), min(hor[i].second.second, hor[j].second.second));
			ans += 1ll * cnt * (cnt - 1) / 2;
		}
	}
	
	printf("%I64d\n", ans);
	return 0;
}