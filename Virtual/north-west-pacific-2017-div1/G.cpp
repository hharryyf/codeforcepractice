#include <bits/stdc++.h>
#define MAX_SIZE 5011
using namespace std;


int visited[MAX_SIZE];
pair<int, int> edg[MAX_SIZE];
vector<pair<int, int>> g[MAX_SIZE];
vector<int> disc;
vector<int> tmp;
int N, M, K;
int S, T;

void init() {
	for (int i = 1; i <= N; ++i) visited[i] = 0;
}

void dfs(int v, int l, int r) {
	visited[v] = 1;
	for (auto nv : g[v]) {
		int eid = nv.second;
		if (!visited[nv.first] && edg[eid].first <= l && edg[eid].second >= r) {
			dfs(nv.first, l, r);
		}
	}
}

int main() {
	int i;
	scanf("%d%d%d", &N, &M, &K);	
	scanf("%d%d", &S, &T);
	for (i = 1; i <= M; ++i) {
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		g[a].emplace_back(b, i);
		edg[i].first = c, edg[i].second = d;
		tmp.push_back(c);
		tmp.push_back(d);
	}

	tmp.push_back(1);
	tmp.push_back(K);
	sort(tmp.begin(), tmp.end());
	for (i = 0 ; i < (int) tmp.size(); ++i) {
		if (i == 0 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
	}

	int sz = disc.size(), ans = 0;
	for (i = 0 ; i < sz; ++i) {
		init();
		dfs(S, disc[i], disc[i]);
		if (visited[T]) {
			ans++;
		}
		if (i != 0 && disc[i] - disc[i-1] > 1) {
			init();
			dfs(S, disc[i-1] + 1, disc[i] - 1);
			if (visited[T]) {
				ans = ans + disc[i] - disc[i-1] - 1;
			}
		}
	}

	printf("%d\n", ans);
	return 0;
}