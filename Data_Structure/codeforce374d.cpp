#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 2097312
typedef long long ll;
using namespace std;

int n;
int rsum[MAX_SIZE];
char value[MAX_SIZE];
int a[MAX_SIZE];

int getmax(int l, int r, int index) {
	if (l > r) return 0;
	if (l == r) {
	   return l;
	}
	
	int mid = (l + r) >> 1;
	if (rsum[index * 2 + 1]) return getmax(mid + 1, r, index * 2 + 1);
	return getmax(l, mid, index * 2);
}

void add(int pos, int l, int r, int index, int v) {
	 if (l > r) return;
	 int mid = (l + r) >> 1;
	 if (l == r && l == pos) {
	 	rsum[index] = 1;
	 	value[index] = v + '0';
	 	// cout << "insert at index " << l << endl;
	 	return;
	 }
	 
	 if (pos <= mid) {
	 	add(pos, l, mid, index * 2, v);
	 } else {
	    add(pos, mid + 1, r, index * 2 + 1, v);
	 }
	 rsum[index] = rsum[index * 2] + rsum[index * 2 + 1];
} 

void del(int l, int r, int index, int k) {
	 if (l > r || rsum[index] < k) return;
	 if (l == r) {
	 	rsum[index] = 0, value[index] = '0';
	 	// cout << "delete at index " << l << endl;
	 	return;
	 }
	 
	 int mid = (l + r) >> 1;
	 if (rsum[index * 2] >= k) {
	 	del(l, mid, index * 2, k);
	 } else {
	    del(mid + 1, r, index * 2 + 1, k - rsum[index * 2]);
	 }
	 rsum[index] = rsum[index * 2] + rsum[index * 2 + 1];
}

void print(int l, int r, int index) {
	 if (l == 1 && r == n && !rsum[index]) {
	 	printf("Poor stack!");
	 	return;
	 }
	 if (l > r || !rsum[index]) return;
	 if (l == r) {
	 	 if (rsum[index] != 0) putchar(value[index]);
	 	 return;
	 }
	 
	 int mid = (l + r) >> 1;
	 print(l, mid, index * 2);
	 print(mid + 1, r, index * 2 + 1);
}

int main() {
	int m, i, j;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= m; i++) {
		scanf("%d", &a[i]);
	}	
	
	for (i = 1; i <= n; i++) {
		int v;
		scanf("%d", &v);
		if (v == -1) {
		   for (j = 1; j <= m; j++) {
		   	   if (rsum[1] < a[j] - (j-1)) break;
		   	   del(1, n, 1, a[j] - (j - 1));
		   }
		} else {
		   int pos = 0;
		   if (rsum[1] == 0) {
		   	  pos = 1;
		   } else {
		      pos = getmax(1, n, 1) + 1;
		   } 
		   add(pos, 1, n, 1, v);
		}
	}
	
	print(1, n, 1);
	printf("\n");
	return 0;
}

