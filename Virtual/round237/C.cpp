#include <bits/stdc++.h>
#define MAXN 100005
#define ii pair<int, int>
#define x first
#define y second
using namespace std;

int n, k;
int d[MAXN];
vector<int> c[MAXN];
vector<ii> e;

void dfs(int at) {
	for (int i = (d[at] == 0 ? 0 : 1); i < k && c[d[at]+1].size(); i++) {
		int next = c[d[at]+1].back();
		c[d[at]+1].pop_back();
		e.push_back(make_pair(at, next));
		dfs(next);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> d[i];
		if (d[i] >= n) {
			cout << -1 << endl;
			return 0;
		}
		c[d[i]].push_back(i);
	}
	int start = -1;
	for (int i = 1; i <= n; i++) {
		if (d[i] == 0) {
			if (start != -1) {
				cout << -1 << endl;
				return 0;
			}
			start = i;
		}
	}
	if (start == -1) {
		cout << -1 << endl;
		return 0;
	}
	dfs(start);
	c[0].pop_back();
	for (int i = 0; i < MAXN; i++) {
		if (c[i].size()) {
			cout << -1 << endl;
			return 0;
		}
	}
	cout << e.size() << endl;
	for (auto [x, y] : e) {
		cout << x << ' ' << y << endl;
	}
}
