#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 10011
using namespace std;

int luckynum[30] = {4, 7, 44, 47, 74, 77, 
                    444, 447, 474, 477, 744, 747, 
					774, 777, 4444, 4447, 4474, 4477, 
                    4744, 4747, 4774, 4777, 7444, 7447,
					7474, 7477, 7744, 7747, 7774, 7777};

int good[MAX_SIZE];
int lucky(int num) {
	return binary_search(luckynum, luckynum + 30, num);
}

int bid[MAX_SIZE * 10];

struct sqrtdecomp {
	   int n;
	   struct block {
	   		  int cnt[MAX_SIZE];
	   		  int inc;
	   };
	   block b[318];
	   int bsz;
	   int a[MAX_SIZE * 10];
	   void build() {
	   		int i;
			for (i = 0 ; i < n; i++) {
				++b[bid[i]].cnt[a[i]];
			}		
	   }
	   
	   void update(int l, int r, int val) {
	   		int i;
			int bL = bid[l], bR = bid[r];
			for (i = bL + 1; i <= bR - 1; i++) b[i].inc += val;
			
			if (bL != bR) {
				for (i = bL * bsz; i < min((bL + 1) * bsz, n); ++i) {
					b[bL].cnt[a[i]] = 0, a[i] += b[bL].inc;
				}
				for (i = bR * bsz; i < min((bR + 1) * bsz, n); ++i) {
					b[bR].cnt[a[i]] = 0, a[i] += b[bR].inc;
				}
				for (i = bL * bsz; i < min((bL + 1) * bsz, n); ++i) {
					if (i >= l) a[i] += val; 
		   			++b[bL].cnt[a[i]];
				}
				
				for (i = bR * bsz; i < min((bR + 1) * bsz, n); ++i) {
					if (i <= r) a[i] += val;
					++b[bR].cnt[a[i]];
				}
			} else {
			    for (i = bL * bsz; i < min((bL + 1) * bsz, n); ++i) {
					b[bL].cnt[a[i]] = 0, a[i] += b[bL].inc;
				}
				
				for (i = bL * bsz; i < min((bL + 1) * bsz, n); ++i) {
					if (l <= i && i <= r) a[i] += val;
					++b[bL].cnt[a[i]];
				}
			}
			
			b[bL].inc = b[bR].inc = 0;
	   }
	   
	   int query(int l, int r) {
	   	   int i, j;
		   int ret = 0;
		   int bL = bid[l], bR = bid[r];
		   
		   if (bL == bR) {
		   	  for (i = l; i <= r; i++) {
			  	  ret += good[a[i] + b[bL].inc];
			  }
			  return ret;
		   }
		   
		   for (i = bL + 1; i <= bR - 1; i++) {
		   	   int dwn = lower_bound(luckynum, luckynum + 30, b[i].inc) - luckynum;
		   	   for (j = dwn ; j < 30; j++) {
			   	   ret += b[i].cnt[luckynum[j] - b[i].inc];	  
			   }
		   }
		   
		   for (i = l; i < (bL + 1) * bsz; i++) {
		   	   ret += good[a[i] + b[bL].inc];
		   }
		   
		   for (i = bR * bsz; i <= r; i++) {
		   	   ret += good[a[i] + b[bR].inc];
		   }
		   return ret;	   	   	   
	   }
};

sqrtdecomp s;
char st[8];

int main() {
	int q;
	scanf("%d%d", &s.n, &q);
	int i, j;
	for (i = 0 ; i < MAX_SIZE; i++) {
		if (lucky(i)) good[i] = 1;
	}
	for (i = 0; i < s.n; i++) {
		scanf("%d", &s.a[i]);
	}
	s.bsz = sqrt(s.n);
	for (i = 0 ; i < 318; i++) {
		int ed = min(s.n, (i + 1) * s.bsz);
		for (j = i * s.bsz; j < ed; j++) {
			bid[j] = i;
		}
	}
	s.build();
	while (q > 0) {
		  int l, r;
		  scanf("%s%d%d", st, &l, &r);
		  if (st[0] == 'c') {
		  	 printf("%d\n", s.query(l-1, r-1));
		  } else {
		  	 int d;
		  	 scanf("%d", &d);
		  	 s.update(l-1, r-1, d);
		  }
		  --q;
	}
	return 0;
}
