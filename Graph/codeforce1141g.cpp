#include <bits/stdc++.h>
#define MAX_SIZE 200111
using namespace std;

vector<pair<int, int>> g[MAX_SIZE];
int n, k;
int ans[MAX_SIZE];
int deg;

bool valid(int cl) {
	int i, cnt = 0;
	for (i = 1; i <= n; ++i) {
		if ((int) g[i].size() > cl) cnt++;
	}
	return cnt <= k;
}

int color(int idx) {
	return ((idx - 1) % deg) + 1;
}

void dfs(int v, int pre, int pc) {
	int i = 1;
	for (auto np : g[v]) {
		int nv = np.first, id = np.second;
		if (nv != pre) {
			if (i <= deg && i == pc) {
				i++;
			}
			ans[id] = color(i);
			dfs(nv, v, color(i));
			i++;
		}
	}
}

int main() {
	int i;
	scanf("%d%d", &n, &k);
	for (i = 1; i < n; ++i) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].emplace_back(v2, i);
		g[v2].emplace_back(v1, i);
	}
	
	int low = 1, high = n - 1;
	deg = n - 1;
	while (low <= high) {
		int mid = (low + high) >> 1;
		if (!valid(mid)) {
			low = mid + 1;
		} else {
			deg = mid;
			high = mid - 1;
		}
	}
	
	dfs(1, 0, 0);
	
	printf("%d\n", deg);
	for (i = 1; i < n; ++i) {
		printf("%d ", ans[i]);
	}
	printf("\n");
	return 0;
}