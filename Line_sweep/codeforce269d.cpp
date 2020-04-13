#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 262192
using namespace std;


const int inf = 1e9 + 10;

struct event {
	int x, id, tp;
	bool operator < (event other) const {
		if (x != other.x) return x < other.x;
		return tp < other.tp;
	}
};


struct panel {
	int l, r, h;
};

event evt[MAX_SIZE];
panel pn[MAX_SIZE];
int sz = 0;
vector<int> g[MAX_SIZE];
int dp[MAX_SIZE];

struct segt {
	int h, id;
	bool operator < (segt other) const {
		if (h != other.h) return h < other.h;
		return id < other.id;
	}
};

void dfs(int v) {
	if (dp[v] != -1) return; 
	for (auto nv : g[v]) {
		dfs(nv);
		int itc = min(pn[nv].r, pn[v].r) - max(pn[nv].l, pn[v].l);
		dp[v] = max(dp[v], min(itc, dp[nv]));
	}
}

void addevent(int pos, int id, int tp) {
	evt[sz++] = event{pos, id, tp};
}

set<pair<int, int>> edg;
void addedge(int from, int to) {
	edg.insert(make_pair(from, to));
	// cout << "addedge " << from << " , " << to << endl;
}

int main() {
	int n, i, t;
	scanf("%d%d", &n, &t);
	pn[0].l = -inf, pn[0].r = inf, pn[0].h = inf;
	pn[n+1].l = -inf, pn[n+1].r = inf, pn[n+1].h = -inf;
	addevent(-inf, 0, 1);
	addevent(inf, 0, -1);
	addevent(-inf, n+1, 1);
	addevent(inf, n+1, -1);
	
	for (i = 0 ; i <= n + 1; ++i) dp[i] = -1;
	
	for (i = 1; i <= n; ++i) {
		scanf("%d%d%d", &pn[i].h, &pn[i].l, &pn[i].r);
		addevent(pn[i].l, i, 1);
		addevent(pn[i].r, i, -1);
	}
	
	
	sort(evt, evt + sz);
	
	set<segt> s;
	
	for (i = 0; i < sz; ++i) {
		int ch = pn[evt[i].id].h;
		if (evt[i].tp == -1) {
			s.erase(segt{ch, evt[i].id});
		} else {
			if (s.empty()) {
				s.insert(segt{ch, evt[i].id});
				continue;
			}
			
			auto iter = s.upper_bound(segt{ch, evt[i].id});
			auto bg = s.begin();
			int t2 = 0;
			if (iter != s.end()) {
				addedge(iter->id, evt[i].id);
				t2++;
			}
			
			if (iter != bg) {
				auto it = prev(iter);
				addedge(evt[i].id, it->id);
				t2++;
			}
			
			if (t2 == 2) {
				auto it = prev(iter);
				edg.erase(make_pair(iter->id, it->id));
				// cout << " remove " << iter->id << " " << it->id << endl;
			}
			s.insert(segt{ch, evt[i].id});
		}
	}
	
	for (auto np : edg) {
		g[np.first].push_back(np.second);
		// cout << "addedge " << np.first << " " << np.second << endl;
	}
	
	dp[n+1] = pn[n+1].r - pn[n+1].l;
	dfs(0);
	
	printf("%d\n", dp[0]);
	return 0;
}