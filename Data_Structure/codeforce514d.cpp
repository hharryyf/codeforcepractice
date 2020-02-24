#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;

int table[5][18][MAX_SIZE];
int logs[MAX_SIZE];
int n, m;
void build() {
	 int i, j, k;
	 for (i = 2; i <= n; i++) logs[i] = logs[i/2] + 1;
	 for (i = 1; i <= n; i++) {
	 	 for (j = 0; j < m; j++) {
		  	 scanf("%d", &table[j][0][i]);
         }
	 }
	 
	 for (i = 1; i <= 17; i++) {
	 	  int prev2 = 1 << (i-1);
		  for (j = 1; j <= n; j++) {
 	         int intEnd = prev2 + j;
		 	 for (k = 0 ; k < m; k++) {
			  	 if (intEnd <= n) table[k][i][j] = max(table[k][i-1][j], table[k][i-1][intEnd]);
		     	 else table[k][i][j] = table[k][i-1][j];
			 } 
          }
	 }
}

int query(int dim, int l, int r) {
	int l2 = logs[r - l + 1];
	return max(table[dim][l2][l], table[dim][l2][r + 1 - (1 << l2)]);
}

int cost(int l, int r) {
	int i, ret = 0;
	for (i = 0 ; i < m; i++) ret += query(i, l, r);
	return ret;
}

int main() {
    int k, i;
    int L = 1, R = 0;
    scanf("%d%d%d", &n, &m, &k);
    build();
    for (i = 1; i <= n; i++) {
		int low = 1, high = i;
		int len = 0;
		while (low <= high) {
			  int mid = low + (high - low) / 2;
			  if (cost(mid, i) <= k) {
			  	 len = i - mid + 1;
			  	 high = mid - 1;
			  } else {
			  	 low = mid + 1;
			  }
		}
		
		if (len > R - L + 1) {
		    R = i, L = i - len + 1;
		}
	}
	
	if (L <= R) {
	   for (i = 0 ; i < m; i++) printf("%d ", query(i, L, R));
	   printf("\n");
	} else {
	    for (i = 0 ; i < m; i++) printf("0 ");
	    printf("\n");
	}
	return 0;
}
