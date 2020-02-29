#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 200011
typedef long long ll;
using namespace std;

ll p[MAX_SIZE], a[MAX_SIZE];
int n, m;
ll T;
// check whether it is possible to do 'mid' number of tasks with difficulty
// d, using no less than T
bool valid(int mid, ll d) {
	 int i, cnt = 0, chunk = 0;
	 ll t = 0, chunkt = 0;
	 for (i = 1; i <= n; i++) {
	 	if (p[i] > d) continue;
	    if (t > T) break;
 	    t += p[i];
	    chunkt += p[i];
 	    chunk++;
        if (t > T) break;
 	    cnt++;
 	    if (chunk == m) {
		   t += chunkt;
		   chunk = 0;
		   chunkt = 0; 
	    }
	 }
	 
	 return cnt >= mid;
}

int main() {
	int c;
	scanf("%d", &c);
	while (c > 0) {
		  scanf("%d%d%lld", &n, &m, &T);
		  int i;
		  for (i = 1; i <= n; i++) {
		  	  scanf("%lld", &p[i]);
		  	  a[i] = p[i];
		  }
		  
		  sort(a+1, a+n+1);
		  
		  int low = 1, high = n, ans = 0;
		  
		  while (low <= high) {
		  		int mid = (low + high) >> 1;
				if (valid(mid, a[mid])) {
				   ans = mid;
				   low = mid + 1;   
				} else {
				   high = mid - 1;
				}		
		  }
		  
		  printf("%d %lld\n", ans, a[ans] > 0 ? a[ans] : 1);
		  c--;
	}
	return 0;
}
