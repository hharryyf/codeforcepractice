#include <bits/stdc++.h>
#define MAX_BLOCK 1011
using namespace std;

int block_sz = 1;
struct node {
	int x, y, id;
	bool operator < (node other) const {
		int id1 = x / block_sz, id2 = other.x / block_sz;
		return id1 == id2 ? y < other.y : id1 < id2;
	}
};

vector<node> g[MAX_BLOCK];
int n;
int ans[MAX_BLOCK * MAX_BLOCK];

int main() {
	int i, cnt = 0, j;
	scanf("%d", &n);
	block_sz = 1000;
	for (i = 1; i <= n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		g[y / block_sz].push_back(node{x, y, i});
	}
	
	bool lr = true;
	for (i = 0; i < MAX_BLOCK; ++i) {
		if (!g[i].empty()) {
			sort(g[i].begin(), g[i].end());
			if (lr) {
				for (auto nd : g[i]) {
					ans[++cnt] = nd.id;
				}
				lr = false;
			} else {
				for (j = (int) g[i].size() - 1; j >= 0; --j) {
					ans[++cnt] = g[i][j].id;
				}
				lr = true;
			}
		}
	}
	
	for (i = 1; i <= cnt; ++i) {
		printf("%d ", ans[i]);
	}
	printf("\n");
	return 0;
}