#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 1001111
typedef long long ll;
using namespace std;

char p[MAX_SIZE];
int nxt[MAX_SIZE];
int m;

void calnext() {
	 int j = 0, k = -1;
	 nxt[0] = -1;
	 while (j  <= m - 1) {
	 	   if (k == -1 || p[j] == p[k]) {
			  j++, k++;
			  nxt[j] = k;    
           } else {
		   	   k = nxt[k];
		   }   
	 }
}

void print() {
	 int i;
	 for (i = 1; i <= m; i++) {
	 	 int prd = i - nxt[i];
	 	 if (i != prd && i % prd == 0) {
		  	printf("%d %d\n", i, i / prd);
		 }
	 }	 
}

int main(){
	int i, T;
	scanf("%d", &T);
	for (i = 1; i <= T; i++) {
		scanf("%d", &m);
		scanf("%s", p);
		printf("Test case #%d\n", i);
		calnext();
		print();		
		printf("\n");
	}
	return 0;
}
