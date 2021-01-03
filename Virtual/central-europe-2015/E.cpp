#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 300011
using namespace std;

struct qrs {
	int w, id;
	bool operator < (qrs other) const {
		return w > other.w;
	}
};

int visited[MAX_SIZE];
pair<int, int> ans[MAX_SIZE];
int f[MAX_SIZE], sz[MAX_SIZE], deg2[MAX_SIZE];
int d[MAX_SIZE];
qrs q[MAX_SIZE];
vector<pair<int, int>> add[MAX_SIZE];
int N, M;
int V, D, C, E;

int find(int x) {
	if (f[x] == x) return x;
	return f[x] = find(f[x]);
}

void inc(int x) {
	int v = find(x);
	if (d[x] == 2) {
		if (sz[v] == deg2[v]) C--;
		deg2[v]--;
		D--;
	}

	if (d[x] == 0) V++;

	d[x]++;
	if (d[x] == 2) {
		deg2[v]++;
		if (sz[v] == deg2[v]) C++;
		D++;
	}
}

void addedge(int u, int v) {
	inc(u), inc(v);
	E++;
	int a = find(u), b = find(v);
	if (a != b) {
		f[a] = b;
		sz[b] += sz[a];
		deg2[b] += deg2[a];
	}
}

int main() {
	int i, j;
	scanf("%d%d", &N, &M);
	for (i = 1; i <= N; ++i) {
		f[i] = i, sz[i] = 1;
	}

	for (i = 1; i <= M; ++i) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add[w].emplace_back(u, v);
	}

	int Q;
	scanf("%d", &Q);
	for (i = 1; i <= Q; ++i) {
		int w;
		scanf("%d", &w);
		q[i].id = i, q[i].w = w;
	}

	sort(q + 1, q + 1 + Q);
	for (i = 300000, j = 1; i >= 0; --i) {
		for (auto e : add[i]) {
			addedge(e.first, e.second);
		}

		while (j <= Q && q[j].w >= i) {
			ans[q[j].id].first = V - D + C;
			ans[q[j].id].second = E - D + C;
			++j;
		}
	}

	for (i = 1; i <= Q; ++i) {
		printf("%d %d\n", ans[i].first, ans[i].second);
	}


	return 0;
}