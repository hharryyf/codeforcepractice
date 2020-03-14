#pragma GCC optimize(3)
#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#define MAX_SIZE 4011
#define INF 700000000
using namespace std;

int u[MAX_SIZE][MAX_SIZE];
int dp[MAX_SIZE][811];

// the sum of the subrectangle / 2
int cost(int l, int r) {
	return (u[r][r] + u[l-1][l-1] - u[l-1][r] - u[r][l-1]) >> 1;
}

inline int read(){
    int x=0; char ch=getchar();
    for(;ch<'0'||ch>'9';ch=getchar());
    for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x;
}

void divc(int start, int end, int l, int r, int k) {
	if (l > r) return;
	int pos = -1;
	int mid = (l + r) >> 1;
	dp[mid][k] = INF;
	for (int i = start; i <= min(mid - 1, end); i++) {
		int newcost = dp[i][k-1] + cost(i+1, mid);
		if (newcost < dp[mid][k]) {
			pos = i;
			dp[mid][k] = newcost;
		}
	}
	divc(start, pos, l, mid - 1, k);
	divc(pos, end, mid + 1, r, k);
}

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	int i, j;
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= n; ++j) {
			u[i][j] = read();
			u[i][j] += u[i][j-1] + u[i-1][j] - u[i-1][j-1];
		}
	}
	
	for (i = 1; i <= n; ++i) {
		dp[i][1] = cost(1, i);
	}
	
	for (i = 2; i <= k; ++i) {
		divc(0, n, 1, n, i);
	}
	
	printf("%d\n", dp[n][k]);
	return 0;
}