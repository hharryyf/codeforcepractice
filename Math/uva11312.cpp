#include <bits/stdc++.h>
#define MOD 1000000007
typedef long long ll;
using namespace std;

/*
   extended euclidian algrithm would find 1 solution to the equation
   a * x + b * y = gcd(a, b) while finding gcd(a, b)
*/ 

int gcd(int a, int b, int &x, int &y) {
	// base case, when a == 0, gcd = b and solution to this equation is (0, 1)
	if (a == 0) {
       x = 0; y = 1;
       return b;
    }
  	
    int x1, y1;
    // general case, try to construct a*x + b*y = d from (b%a) * x1 +  a * y1 = d
  	int d = gcd(b % a, a, x1, y1);
  	// use the property b%a = b - b/a * a would easily derive the result
  	x = y1 - (b / a) * x1;
  	y = x1;
  	return d;
}

int n, l, r, t;

bool valid(int x, int y, int dist) {
    if (x == 0 && y == 0) return true;
    int rem = n - dist;
    int k = min(x, rem / r);
    if (k > 0 && dist + r <= n) return valid(x - k, y, dist + k * r);
    k = min(y, dist / l);
    if (k > 0) {
	   return valid(x, y - k, dist - k * l);
	}
    return false;
}


int main(){
	int T;
	scanf("%d", &T);
	while (T > 0) {
		  scanf("%d%d%d%d", &n, &l, &r, &t);
		  if (t == 1) {
		  	 printf("0\n");
		  } else {
		  	 t--;
		  	 n--;
		  	 int x = 0, y = 0;
		  	 int d = gcd(r, l, x, y);
             // first failure case
  	 		 if (t % d != 0) {
			 	printf("uh-oh!\n");	
	         } else {
			    // we need to find the minimum x such that y is non-positive 
				int N = ceil(max(-1.0 * x * t / l ,1.0 * y * t / r));
         		x = (x * t + l * N) / d;
				y = (y * t - r * N) / d;
				if (valid(x, -y, 0)) {
				   printf("%d\n", x - y);
				} else {
				   printf("uh-oh!\n");
				}
			 }
		  }
		  T--;
	}	
	return 0;
}

