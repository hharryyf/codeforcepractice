#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 500011
using namespace std;

int sz[MAX_SIZE];
int use[MAX_SIZE];
vector<int> g[MAX_SIZE];
vector<int> block[MAX_SIZE];
int ans[MAX_SIZE];
// delete the x from all blocks it occurs
void del(int x) {
	use[x] = 1;
	for (auto v : block[x]) {
		sz[v]--;
	}
}

int main() {
	int n, i, j;
	scanf("%d", &n);
	for (i = 1; i <= n/2; ++i) {
		for (j = 1; j <= n; ++j) {
			if (i * j > n) break;
			g[i].push_back(i * j);
			sz[i]++;
			block[i * j].push_back(i);
		}
	}
	
	j = n;
	for (i = n/2; i >= 1; ) {
		if (sz[i] >= 2) {
			ans[j] = i;
			int v;
			while (use[g[i].back()]) {
				g[i].pop_back();
			}
			v = g[i].back();
			del(v);
			--j;
		} else {
			--i;
		}
	}
	
	for (i = 2; i <= n; ++i) printf("%d ", ans[i]);
	printf("\n");
	return 0;
}