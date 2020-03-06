#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 111
typedef long long ll;
using namespace std;

int g[MAX_SIZE][MAX_SIZE];
int seq[MAX_SIZE * MAX_SIZE];
int ans[MAX_SIZE * MAX_SIZE];
bool ok;
int n, m;

bool dfs(int v, int dep, bool limit) {
	 ans[dep] = v;
	 if (ok) return true;
	 if (dep == m && ans[m] == ans[0] && !limit) {
	 	ok = true; 
	    return true;
     }
	 //if (dep == m) return false;
	 int low = limit ? seq[dep+1] : 1, i;
	 for (i = low; i <= n; i++) {
	 	 if (g[v][i]) {
		  	g[v][i]--, g[i][v]--;
		  	if (dfs(i, dep + 1, limit && i == seq[dep+1])) {
			  ok = true; 
			  return true;
		    }
		  	g[v][i]++, g[i][v]++;
         }
	 }
	 return false;
}

int main() {
	scanf("%d%d", &n, &m);
	int i;
	for (i = 0 ; i <= m; i++) {
		scanf("%d", &seq[i]);
		if (i != 0) {
		   g[seq[i]][seq[i-1]] = g[seq[i-1]][seq[i]] = 1;
		}
	}
	
	dfs(seq[0], 0, true);
	
	if (!ok) {
	   printf("No solution\n");
	} else {
	   for (i = 0 ; i <= m; i++) printf("%d ", ans[i]);
	   printf("\n");
	}
	return 0;
}

