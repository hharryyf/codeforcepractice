#include <bits/stdc++.h>
#define MAX_SIZE 2111 
#define INF 1000000000000000ll
using namespace std;
typedef long long ll;
ll dp[MAX_SIZE][MAX_SIZE];

int n, k;

ll x[MAX_SIZE];

ll dist[MAX_SIZE];
ll dist2[MAX_SIZE];

ll cost(int i, int j) {
	if (i + 1 >= j) return 0;
	int mid = i+1 + (j - i-1) / 2;
	
	ll ret = dist[mid] - dist[i+1] - (x[mid] - x[i+1]) * i + dist2[mid] - dist2[j] - (x[j] - x[mid]) * (n - j); 
	//  << "cost " << i << " " << j << " is " << ret << endl;
	return ret;
}

void divc(int start, int end, int l, int r, int k) {
	if (l > r) return;
	int pos = -1;
	int mid = l + (r - l) / 2;
	int i;
	dp[mid][k] = INF;
	/* bestpos is between start and end */
	for (i = start; i <= min(mid - 1, end); i++) {
		ll ncost = dp[i][k-1] + cost(i, mid);
		if (ncost < dp[mid][k]) {
			dp[mid][k] = ncost;
			pos = i;
		}
	}
	
	divc(start, pos, l, mid - 1, k);
	divc(pos, end, mid + 1, r, k);
}


int main() {
	scanf("%d%d", &n, &k);
	int i;
	for (i = 1; i <= n; i++) {
		scanf("%lld", &x[i]);
	}
	
	for (i = 2; i <= n; i++) {
		dist[i] = (x[i] - x[i-1]) * (i-1) + dist[i-1];
	}
	
	for (i = n - 1; i >= 1; i--) {
		dist2[i] = (x[i+1] - x[i]) * (n - i) + dist2[i+1];
	}
	/*
	for (i = 1; i <= n; i++) cout << dist[i] << " ";
	cout << endl;
	
	for (i = 1; i <= n; i++) cout << dist2[i] << " ";
	cout << endl;
	*/
	for (i = 1; i <= n; i++) {
		dp[i][1] = cost(0, i);
	}	
	
	for (i = 2; i <= k; i++) {
		divc(0, n, 1, n, i);
	}
	
	cout << dp[n][k] << endl;
	return 0;
}
