#include <bits/stdc++.h>
#define INF (1 << 29)
#define MAX_SIZE 311
typedef long long ll;
using namespace std;

struct Matrix {
	   int n;
	   int a[MAX_SIZE][MAX_SIZE];	   
	   
	   void init(int n) {
	   		int i, j;
	   		this->n = n;
	   		for (i = 0 ; i <= n; i++) {
				for (j = 0 ; j <= n; j++) {
					a[i][j] = -INF;
				}   
	        }
	   }
	   
	   Matrix operator * (Matrix &other) const {
	   		Matrix ret;
	   		ret.n = n;
	   		int i, j, k;
	   		for (i = 1; i <= n; i++) {
	        	for (j = 1; j <= n; j++) {
					ret.a[i][j] = max(a[i][j], other.a[i][j]);
					for (k = 1; k <= n; k++) {
						ret.a[i][j] = max(ret.a[i][j], a[i][k] + other.a[k][j]);
					}
				}
			}
	   		return ret;
	   }
};

Matrix f[10];

bool valid(int mid) {
	 Matrix d;
	 int i;
	 d.init(f[0].n);
	 for (i = 9; i >= 0; i--) {
	 	 if (mid >= (1 << i)) d = d * f[i], mid -= (1 << i);
	 }
	 
	 for (i = 1; i <= d.n; i++) {
	 	 if (d.a[i][i] > 0) return true;
	 }
	 return false;
}

int main() {
	int n, m, i;
	scanf("%d%d", &n, &m);
	for (i = 0 ; i < 10; i++) f[i].init(n);
	for (i = 0 ; i < m; i++) {
		int v1, v2, c1, c2;
		scanf("%d%d%d%d", &v1, &v2, &c1, &c2);
		f[0].a[v1][v2] = c1, f[0].a[v2][v1] = c2;
	}
	
	for (i = 1; i < 10; i++) f[i] = f[i-1] * f[i-1];
	int low = 1, high = n + 1, ans = n + 2;
	while (low <= high) {
		  int mid = (low + high) >> 1;
		  if (valid(mid)) {
		  	 high = mid - 1, ans = mid;
		  } else {
		  	 low = mid + 1;
		  }
	}
	
	printf("%d\n", ans < n + 2 ? ans : 0);
	return 0;
}

