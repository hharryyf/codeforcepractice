#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 1007
typedef long long ll;
using namespace std;

struct BIT {
	   ll a[2][2][MAX_SIZE][MAX_SIZE];
	   int n;
	   void init(int n=1) {
	       this->n = n;
	   }
	   
	   int shift(int x) {
	   	   return x & (-x);
	   }
	   
	   void add(int x, int y, ll val) {
           int i, j;
           for (i = x; i <= n; i += shift(i)) {
		   	   for (j = y; j <= n; j += shift(j)) {
		       	   a[x & 1][y & 1][i][j] ^= val;
			   }
		   }
	   }
	   
	   void update(int x1, int y1, int x2, int y2, ll val) {
	   		add(x1, y1, val);
	   		add(x2+1, y2+1, val);
	   		add(x2+1, y1, val);
	   		add(x1, y2+1, val);
	   }
	   
	   ll getans(int x, int y) {
 	   	  int i, j;
 	   	  ll ret = 0;
 	   	  for (i = x; i > 0; i -= shift(i)) {
		  	  for (j = y; j > 0; j -= shift(j)) {
			      ret ^= a[x & 1][y & 1][i][j];	
              }
		  }
		  
		  return ret;
	   }
	   
	   ll query(int x1, int y1, int x2, int y2) {
 	       return getans(x2, y2) ^ getans(x1-1, y2) ^ getans(x2, y1-1) ^ getans(x1-1, y1-1);
	   }
	   
	   void print() {
	   		int i, j;
	   		for (i = 1; i <= n; i++) {
	        	for (j = 1; j <= n; j++) {
					printf("%lld ", getans(i, j));
				}
				printf("\n");
			}
			cout << endl;
	   }
};

BIT t;

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	t.init(n);
	while (m > 0) {
		int tp;
		int x1, y1, x2, y2;
		ll val;
		scanf("%d", &tp);
		if (tp == 1) {
		   scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		   printf("%lld\n", t.query(x1, y1, x2, y2));
		} else {
		   scanf("%d%d%d%d%lld", &x1, &y1, &x2, &y2, &val);
		   t.update(x1, y1, x2, y2, val);
		}  
		
		#ifdef DEBUG
		t.print();
		#endif
    m--;
	}
	return 0;
}
