#pragma GCC optimize("-Ofast","-funroll-all-loops")
#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 500011
typedef long long ll;
using namespace std;

vector<int> g[MAX_SIZE];
// dfs order of the nodes in in each level
// ascending order, support binary search
// count the number of letters in each level a-z
vector<int> cnt[MAX_SIZE];
vector<int> bt[MAX_SIZE];
int visited[MAX_SIZE], sz[MAX_SIZE];
char s[MAX_SIZE];
int k = 1;

void dfs(int v, int dep) {
	 visited[v] = k++;
	 sz[v] = 1;
	 int curr = s[v] - 'a';
	 int bk = bt[dep].empty() ? 0 : bt[dep].back();
	 cnt[dep].push_back(visited[v]);
	 bt[dep].push_back((1 << curr) ^ bk);
	 for (auto nv : g[v]) {
	 	 if (!visited[nv]) {
         	dfs(nv, dep + 1);
		 	sz[v] += sz[nv];
		 }
	 }	 	 
}

int query(int v, int h) {
	int tol = 0;
	int L = visited[v], R = visited[v] + sz[v] - 1;
	int l = lower_bound(cnt[h].begin(), cnt[h].end(), L) - cnt[h].begin();
	int r = upper_bound(cnt[h].begin(), cnt[h].end(), R) - cnt[h].begin() - 1;
	if (l > r) return 1;
	int b = bt[h][r] ^ (l > 0 ? bt[h][l-1] : 0);
	tol = __builtin_popcount(b);
	return tol <= 1;
}

int main() {
	int n, m, i;
	scanf("%d%d", &n, &m);
	for (i = 2; i <= n; ++i) {
		int v;
		scanf("%d", &v);
		g[v].push_back(i);
	}
	scanf("%s", s + 1);
	dfs(1, 1);
	while (m > 0) {
		  int v, h;
		  scanf("%d%d", &v, &h);
		  printf("%s\n", query(v, h) ? "Yes" : "No");
		  m--;
	}
	return 0;
}

