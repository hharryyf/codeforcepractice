#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;

ll s;
int n;
vector<int> g[MAX_SIZE];
int p[MAX_SIZE];
// check whether it is possible use a branching no greater
// than d and construct a tree with n vertices
int valid(int d) {
	ll rem = s;
	int cnt = 1, i, j;
	// let's say the current level contribution is v
	// and current level has u nodes
	// next level's total contribution would be (v-u)
	// we should try to fill the current level with the greatest amount of nodes
	// without letting the level downwards run out of nodes
	for (i = 0; i < MAX_SIZE; i++) {
		g[i].clear();
	}
	
	int tol = n;
	rem -= 1ll * n;
	g[1].push_back(cnt++);
	// we try to add nodes for level i+1
	for (i = 1; i <= n; i++) {
		rem -= 1ll * (tol - (int) g[i].size());
		tol -= (int) g[i].size();
		for (auto v : g[i]) {
			int flag = 1;
			for (j = 1; j <= d && j <= n-1; j++) {
				if (cnt > n) {
  				    flag = 0;
					break;
				}
				// check whether cnt+1 to n is sufficient 
				int term = n - cnt;
				if (rem <= 1ll * term * (term + 1) / 2) {
				   p[cnt] = v;
				   g[i+1].push_back(cnt++);		
				   		   
				} else {
				   flag = 0;
				   break;
				}
			}
			
			if (!flag) {
			   break;
			}
		}
		if (rem <= 0 || cnt > n) break;
	}
	return rem == 0 && cnt > n;
}

int main() {
	int i;
	scanf("%d%lld", &n, &s);
	if (s < 2 * n - 1 || s > 1ll * n * (n+1) / 2) {
	   printf("No\n");
	   return 0;
	}
	
	int low = 1, high = n - 1;
	int ans = n - 1;
	while (low <= high) {
	    int mid = (low + high) >> 1;
	    if (valid(mid)) {
		   ans = mid;
		   high = mid - 1;
		} else {
		   low = mid + 1;
		}
	}
	
	printf("Yes\n");
	valid(ans);
	for (i = 2; i <= n; i++) printf("%d ", p[i]);
	printf("\n");
	return 0;
}

