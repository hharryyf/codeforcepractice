#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 129
using namespace std;

struct BIT {
	   int a[MAX_SIZE][MAX_SIZE];
	   int n, m;
	   BIT(int n=0, int m=0) {
	   		   this->n = n, this->m = m;
	   }
	   
	   void init() {
	   		int i, j;
	   		for (i = 0 ; i < MAX_SIZE; i++) {
				for (j = 0 ; j < MAX_SIZE; j++) {
					a[i][j] = 0;
				}   
	        }
	   }
	   
	   int shift(int x) {
	   	   return x & (-x);
	   }
	   
	   void update(int x, int y, int val) {
	   		while (x <= n) {
	   			  int y1 = y;
	   			  while (y1 <= m) {
			      		a[x][y1] += val;
			      		y1 += shift(y1);
				  }
				  x += shift(x);
	   		}
	   }
	   
	   int getans(int x, int y) {
	   	   int ret = 0;
	   	   while (x > 0) {
		   		 int y1 = y;
		   		 while (y1 > 0) {
				 	   ret += a[x][y1];
				       y1 -= shift(y1);	
				 }
				 x -= shift(x);
		   }
		   return ret;
	   }
	   
	   int query(int x1, int y1, int x2, int y2) {
	   	   return getans(x2,y2) + getans(x1-1, y1-1) - getans(x2, y1-1) - getans(x1-1, y2);
	   }
};

int a[MAX_SIZE][MAX_SIZE];
BIT t;

int getans(int x1, int y1, int x2, int y2) {
	int i, j;
	int ret = 0;
	for (i = x1; i <= x2; i++) {
		for (j = y1; j <= y2; j++) {
			ret += a[i][j];
		}
	}
	return ret;
}

void init() {
	 int i, j;
	 for (i = 0; i < MAX_SIZE; i++) {
	 	 for (j = 0; j < MAX_SIZE; j++) {
         	 a[i][j] = 0;
		 }
	 }
	 t.init();
}

void run_test() {
	 srand(time(NULL));
	 int T = 2000, i = 0;
	 for (i = 1 ; i <= T; i++) {
	 	 int n = rand() % 100 + 10, m = rand() % 100 + 10;
	 	 init();
	 	 t = BIT(n, m);
	 	 int q = 1500;
	 	 bool valid = true;
	 	 while (q > 0) {
	         int tp = rand() % 2;
	         if (tp == 1) {
	         	int x = rand() % n + 1, y = rand() % m + 1;
	         	int val = rand() % 1000 - 500;
	         	a[x][y] += val;
	         	t.update(x, y, val);
			 } else {
			     int x1 = rand() % n + 1, x2 = rand() % n + 1, y1 = rand() % m + 1, y2 = rand() % m + 1;
			     if (x1 > x2) swap(x1, x2);
			     if (y1 > y2) swap(y1, y2);
				 if (t.query(x1, y1, x2, y2) != getans(x1, y1, x2, y2)) {
				 	printf("wrong answer on test case %d\n", i);
				 	valid = false;
				 	break;
				 }
			 }
			 q--;
		 }
		 if (!valid) break;
	 }
	 
	 if (i == T + 1) {
	 	printf("accepted!\n");
	 }
}

int main() {
    run_test();
    return 0;
}
