#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

vector<int> g[MAX_SIZE];
int color[MAX_SIZE];
int visited[MAX_SIZE];
// part 1/2 of the bipartite graph
vector<int> p1, p2;
// mark the node as special
int special[MAX_SIZE];
int ban[MAX_SIZE];
int n, m;
int ans[MAX_SIZE];

void dfs(int v) {
	visited[v] = 1;
	for (auto nv : g[v]) {
		if (!visited[nv]) {
			if (color[v] == 1) {
				color[nv] = 2;
			} else {
				color[nv] = 1;
			}
			dfs(nv);
		}
	}
}

bool solve_3() {
	int sz1 = p1.size(), sz2 = p2.size(), j = 0;
	if (sz1 % 3 != 0 || sz2 % 3 != 0) return false;
	printf("YES\n");
	for (auto v : p1) {
		ans[v] = (j / 3) + 1;
		++j;
	}
	
	for (auto v : p2) {
		ans[v] = (j / 3) + 1;
		++j;
	}
	
	for (j = 1; j <= n; ++j) printf("%d ", ans[j]);
	printf("\n");
	return true;
}

bool solve_12() {
	// we check whether there's a node in p1 such that its degree
	// is less than or equal to sz2 - 2
	int v = -1, sz2 = (int) p2.size();
	for (auto p : p1) {
		int s = g[p].size();
		if (s <= sz2 - 2) {
			v = p;
			break;
		}
	}
		
	if (v == -1) return false;
		
	printf("YES\n");
	for (auto nd : g[v]) {
		ban[nd] = 1;
	}
		
	vector<int> ret;
	ret.push_back(v);
	for (auto p : p2) {
		if (!ban[p]) {
			ret.push_back(p);
		}
		if ((int) ret.size() == 3) break;
	}
	
	int j = 3;
	ans[ret[0]] = 1;
	ans[ret[1]] = 1;
	ans[ret[2]] = 1;
		
	special[ret[0]] = special[ret[1]] = special[ret[2]] = 1;
	
	for (auto p : p1) {
		if (!special[p]) {
			ans[p] = (j / 3) + 1;
			++j;
		}
	}
		
	for (auto p : p2) {
		if (!special[p]) {
			ans[p] = (j / 3) + 1;
			++j;
		}
	}
	
	for (j = 1; j <= n; ++j) printf("%d ", ans[j]);
	printf("\n");
	return true;
}

bool solve_22() {
	int v1 = -1, v2 = -1, sz1 = (int) p1.size();
	for (auto v : p2) {
		int s = g[v].size();
		if (s <= sz1-2) {
			if (v1 == -1) {
				v1 = v;
			} else {
				v2 = v;
				break;
			}
		}
	}
	if (v1 == -1 || v2 == -1) return false;
	printf("YES\n");
	vector<int> ret;
	ret.push_back(v1);
	for (auto v : g[v1]) ban[v] = 1;
	
	for (auto p : p1) {
		if (!ban[p]) {
			ret.push_back(p);
		}
		if ((int) ret.size() == 3) break;
	}
	
	ans[ret[0]] = 1, ans[ret[1]] = 1, ans[ret[2]] = 1;
	special[ret[0]] = special[ret[1]] = special[ret[2]] = 1;
	for (auto v : g[v1]) ban[v] = 0;
	for (auto v : g[v2]) ban[v] = 1;
	// cout << v1 << " " << v2 << endl;
	ret.clear();
	ret.push_back(v2);
	for (auto p : p1) {
		if (!ban[p]) {
			ret.push_back(p);
		}
		if ((int) ret.size() == 3) break;
	}
	
	ans[ret[0]] = ans[ret[1]] = ans[ret[2]] = 2;
	special[ret[0]] = special[ret[1]] = special[ret[2]] = 1;
	
	int j = 6;
	for (auto p : p1) {
		if (!special[p]) {
			ans[p] = j / 3 + 1;
			++j;
		}
	}
		
	for (auto p : p2) {
		if (!special[p]) {
			ans[p] = j / 3 + 1;
			++j;
		}
	}
	
	for (j = 1; j <= n; ++j) printf("%d ", ans[j]);
	printf("\n");
	return true;
}

int main() {
	int i;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= m; ++i) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].push_back(v2);
		g[v2].push_back(v1);
	}
	
	for (i = 1; i <= n; ++i) {
		if (!visited[i]) {
			color[i] = 1;
			dfs(i);
		}
	}
	
	for (i = 1; i <= n; ++i) {
		if (color[i] == 1) {
			p1.push_back(i);
		} else {
			p2.push_back(i);
		}
	}
	
	if (solve_3()) return 0;
	
	
	if ((int) p2.size() % 3 == 1) swap(p1, p2);
	
	if (solve_12()) return 0;
	
	if (!solve_22()) printf("NO\n");
	
	return 0;
}