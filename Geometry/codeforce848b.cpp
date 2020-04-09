#include <bits/stdc++.h>
#define MAX_SIZE 222111
using namespace std;

int w, h, n;

const int shift = 110011;
// x coord or y coord, id
vector<pair<int, int>> g[MAX_SIZE][2];
pair<int, int> ans[MAX_SIZE];

void solve(int cid) {
	int sz1 = (int) g[cid][0].size();
	int sz2 = (int) g[cid][1].size();
	int i;
	for (i = 0 ; i < sz1; ++i) {
		int right = sz1 - i - 1;
		int up = sz2;
		if (right >= up) {
			ans[g[cid][0][i].second] = {g[cid][0][i + up].first, h};
		} else {
			ans[g[cid][0][i].second] = {w, g[cid][1][right].first};
		}
	}
	
	for (i = 0 ; i < sz2; ++i) {
		int right = sz1;
		int up = sz2 - i - 1;
		if (up >= right) {
			ans[g[cid][1][i].second] = {w, g[cid][1][i + right].first};
		} else {
			ans[g[cid][1][i].second] = {g[cid][0][up].first, h};
		}
	}
}

int main() {
	int i;
	scanf("%d%d%d", &n, &w, &h);
	for (i = 1; i <= n; ++i) {
		int tp, p, t;
		scanf("%d%d%d", &tp, &p, &t);
		// x-coord
		if (tp == 1) {
			g[p - t + shift][0].emplace_back(p, i);
		} else {
			g[p - t + shift][1].emplace_back(p, i);
		}
	}
	
	for (i = 0; i < MAX_SIZE; ++i) {
		sort(g[i][0].begin(), g[i][0].end());
		sort(g[i][1].begin(), g[i][1].end());
		solve(i);
	}
	
	for (i = 1; i <= n; ++i) {
		printf("%d %d\n", ans[i].first, ans[i].second);
	}
	
	return 0;
}