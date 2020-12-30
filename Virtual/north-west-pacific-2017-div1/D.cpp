#include <bits/stdc++.h>
#define MAX_SIZE 50011
typedef long long ll;
using namespace std;

vector<pair<int, int>> g[MAX_SIZE];
int tag[MAX_SIZE], N, sm[MAX_SIZE];

void dfs1(int v, int pre) {
	map<int, vector<int>> cnt;
	for (auto nv : g[v]) {
		cnt[nv.second].push_back(nv.first);
	}

	for (auto iter : cnt) {
		if ((int) iter.second.size() > 1) {
			bool find_parent = false;
			for (auto it : iter.second) {
				if (it == pre) {
					find_parent = true;
				} else {
					tag[it] += 1;
				}
			}

			if (find_parent) {
				tag[1] += 1;
				tag[v] -= 1;
			}
		}
	}

	for (auto nv : g[v]) {
		if (nv.first != pre) {
			dfs1(nv.first, v);
		}
	}
}

void dfs2(int v, int pre) {
	sm[v] = sm[pre];
	sm[v] += tag[v];
	for (auto nv : g[v]) {
		if (nv.first != pre) {
			dfs2(nv.first, v);
		}
	}
}

int main() {
	int i;
	scanf("%d", &N);	
	for (i = 0 ; i < N - 1; ++i) {
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		g[u].emplace_back(v, c);
		g[v].emplace_back(u, c);
	}

	dfs1(1, 0);
	dfs2(1, 0);
	vector<int> ret;
	for (i = 1; i <= N; ++i) {
		if (sm[i] == 0) {
			ret.push_back(i);
		}
	}

	printf("%d\n", (int) ret.size());
	for (auto v : ret) {
		printf("%d\n", v);
	}
	return 0;
}