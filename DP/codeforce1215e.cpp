#include <bits/stdc++.h>
#define MOD 1000000007
#define INF 100000000000000ll
typedef long long ll;
using namespace std;

ll g[22][22];
ll dp[1048597];
int visited[22];
int ct[22];
int main() {
	int i, j, k, n, cnt = 0;
	scanf("%d", &n);
	for (i = 0 ; i < 22; ++i) visited[i] = -1;
	for (i = 0; i < n; i++) {
		int v;
		scanf("%d", &v);
		if (visited[v] == -1) {
		   visited[v] = cnt++;
		}
		ct[visited[v]]++;		
		for (j = 0; j < cnt; ++j) {
			if (j != visited[v]) {
  			   g[j][visited[v]] += ct[j];
  		    }
		}
	}
	
	for (i = 1; i < (1 << cnt); ++i) {
		dp[i] = INF;
	}
	
	for (i = 0; i < (1 << cnt); ++i) {
		for (j = 0; j < cnt; ++j) {
			if ((i & (1 << j)) == 0) {
			   int nextstate = i | (1 << j);
			   ll x = 0;
			   for (k = 0; k < cnt; ++k) {
			   	   if (((1 << k) & nextstate) == 0) {
				   	  x += g[j][k];
				   }
			   }
			   dp[nextstate] = min(dp[nextstate], dp[i] + x);
			}
		}
	}
	
	printf("%lld\n", dp[(1 << cnt) - 1]);
	return 0;
}

