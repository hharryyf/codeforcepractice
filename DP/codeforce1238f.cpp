#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 300111
typedef long long ll;
using namespace std;

// deg[v] is the degree of node v
int deg[MAX_SIZE];
vector<int> g[MAX_SIZE];
// p[v] refers to the answer to node v 
// by using the parent node and 1 subtree
// f[v] refers to the answer of using 1 subtrees and attach all the remaining
// children 
int p[MAX_SIZE], cld[MAX_SIZE], f[MAX_SIZE];
int n;
int ans = 0;
void dfs_1(int v, int pre) {
	 int child = deg[v] - (pre != 0);
	 int first = 0, second = 0;
	 f[v] = 1;
	 for (auto nv : g[v]) {
	 	 if (nv != pre) {
	 	 	dfs_1(nv, v);
	 	 	cld[v] = max(cld[v], f[nv]);
         	f[v] = max(f[v], f[nv] + child);
		 	if (first < f[nv]) {
			   second = first, first = f[nv]; 
	        } else if (second < f[nv]) {
			   second = f[nv];
			}
		 }
	 }
	 
	 if (v == 1) {
	 	ans = max(ans, first + second + 1 + max(0, deg[1] - 2));
	 }
}

void dfs_2(int v, int pre) {
	 multiset<int, greater<int> > s;
	 for (auto nv : g[v]) {
	 	 if (nv != pre) {
         	s.insert(f[nv]);
		 }
	 }
	 
	 for (auto nv : g[v]) {
	 	 if (nv != pre) {
		 	s.erase(s.find(f[nv]));
			int mx = p[v];
			if (!s.empty()) mx = max(mx, *s.begin());
			p[nv] = max(p[nv], mx + max(deg[v] - 1, 0));
			ans = max(ans, p[nv] + cld[nv] + 1 + max(0, deg[nv] - 2));
			s.insert(f[nv]); 
         	dfs_2(nv, v);
		 }
	 }
	 
	 
}

int main() {
	int T, i, n;
	scanf("%d", &T);
	while (T > 0) {
		scanf("%d", &n);
		ans = 0;
		for (i = 1; i <= n; i++) {
			g[i].clear();
			deg[i] = p[i] = f[i] = cld[i] = 0;
	    }
		for (i = 0 ; i < n - 1; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			g[x].push_back(y);
			g[y].push_back(x);
			deg[x]++, deg[y]++;
		}  
		
		dfs_1(1, 0);
		dfs_2(1, 0);
		printf("%d\n", ans);
        T--;
	}
	return 0;
}
