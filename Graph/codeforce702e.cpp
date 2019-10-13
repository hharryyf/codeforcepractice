#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 100011

using namespace std;

ll sm[MAX_SIZE][35];
int f[MAX_SIZE][35];
ll rm[MAX_SIZE][35];
int n;
ll k;

int main() {
	scanf("%d%lld", &n, &k);
	int i, j;
	for (i = 0 ; i < n; i++) {
		scanf("%d", &f[i][0]);
	}
	
	for (i = 0 ; i < n; i++) {
		scanf("%lld", &sm[i][0]);
		rm[i][0] = sm[i][0];
	}
	
	for (i = 1; i <= 34; i++) {
		for (j = 0 ; j < n; j++) {
			f[j][i] = f[f[j][i-1]][i-1];
			sm[j][i] = sm[j][i-1] + sm[f[j][i-1]][i-1];
			rm[j][i] = min(rm[j][i-1], rm[f[j][i-1]][i-1]);
		}
	}
	
	for (i = 0 ; i < n; i++) {
		ll tmp = k;
		ll rmin = rm[i][0], rsum = 0ll;
		int v = i;
		for (j = 34; j >= 0 && tmp > 0; j--) {
			ll stp = (1ll << j);
			if (stp <= tmp) {
				rsum = rsum + sm[v][j];
				rmin = min(rmin, rm[v][j]); 
				v = f[v][j];
				tmp = tmp - stp;
			}
		}
		
		printf("%lld %lld\n", rsum, rmin);
	}
	return 0;
}
