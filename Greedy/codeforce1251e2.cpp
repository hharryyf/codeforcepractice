#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 200011
typedef long long ll;
using namespace std;
vector<int> g[MAX_SIZE];
priority_queue<int, vector<int>, greater<int> > q;

int main() {
	int t, i;
	scanf("%d", &t);
	while (t > 0) {
		  int n;
		  while (!q.empty()) q.pop();
		  scanf("%d", &n);
		  for (i = 0 ; i <= n; i++) g[i].clear();
		  // we iterate i from n-1 to 0, which i refers to we secured
		  // all voters with mi <= i
		  for (i = 0 ; i < n; i++) {
		  	  int mi, pi;
		  	  scanf("%d%d", &mi, &pi);
		  	  g[mi].push_back(pi);
		  }
		  
		  int tol = n, cnt = 0;
		  ll ans = 0;
		  for (i = n - 1; i >= 0; i--) {
		  	  tol -= g[i].size();
		  	  int req = i - tol;
		  	  for (auto v : g[i]) q.push(v);
		  	  while (cnt < req) {
			  		cnt++;
					ans += q.top();
					q.pop();	
	          }
		  }
		  printf("%lld\n", ans);
		  t--;
	}	
	return 0;
}

