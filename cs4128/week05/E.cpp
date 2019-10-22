#include <bits/stdc++.h>
#define MAX_SIZE 20
#define INF 99999999
using namespace std;

int dp[1 << MAX_SIZE];

int weight[MAX_SIZE + 1][MAX_SIZE + 1];

char str[1 << 17];

/* 
	https://codeforces.com/problemset/problem/1238/E
	
	The first problem in the course that destroyed me completely.
	
	A subset dp problem. 
	Let dp[i] represents the minimum cost that is represented by state i
	In order to do state transition and eliminate the effect of the current
	state on previous states, we tried to append the jth letter, which hasn't 
	been added to the state to our current sequence.
	Note that the jth letter's contribution would be
	sum((pos[j] - pos[i]) * c[j][i], pos[i] < pos[j]) + sum((pos[j] - pos[i]) * c[j][i], pos[i] > pos[j]) 
	However, this would not eliminate the effect of the current state on previous state completely.
	Consider the bit count functionality, we could minum bitcount(i) * c[j][i] to the state afterwards
	and add it back when we reach that point. A technique used in "on changing tree". 
*/

int main() {
	int i, n, m, j, k;
	scanf("%d%d", &n, &m);
	scanf("%s", str);
	for (i = 1 ; i < n; i++) {
		if (str[i] != str[i-1]) {
			weight[str[i] - 'a'][str[i-1] - 'a']++;
			weight[str[i-1] - 'a'][str[i] - 'a']++;
		}
	}
	
	for (i = 1; i < (1 << m); i++) {
		dp[i] = INF; 
	}
	
	dp[0] = 0;
	
	for (i = 0; i < (1 << m); i++) {
		int bc = __builtin_popcount(i);
		for (j = 0; j < m; j++) {
			if (!(i & (1 << j))) {
				int tmp = dp[i];
				for (k = 0; k < m; k++) {
					if (i & (1 << k)) {
						tmp = tmp + bc * weight[j][k];
					} else {
						tmp = tmp - bc * weight[j][k];
					}
				}
				
				dp[i | (1 << j)] = min(dp[i | (1 << j)], tmp);
			}
		}
	}
	
	cout << dp[(1 << m) - 1] << endl;
	return 0;
}
