#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 200111
typedef long long ll;
using namespace std;

int table[MAX_SIZE][19];
int a[MAX_SIZE];
int n;
int mx[MAX_SIZE];
int ans[MAX_SIZE];
int logs[MAX_SIZE];
void build() {
	 int i, j;
	 for (i = 2; i < MAX_SIZE; i++) logs[i] = logs[i/2] + 1;
	 for (i = 1; i <= n; i++) table[i][0] = a[i];
	 for (j = 1; j <= 18; j++) {
	 	 int prevp2 = 1 << (j-1);
	 	 for (i = 1; i <= n; i++) {
		 	 int intEnd = i + prevp2;
			 if (intEnd <= n) {
			 	table[i][j] = min(table[i][j-1], table[intEnd][j-1]);
			 } else {
			    table[i][j] = table[i][j-1];
			 }	  	 
         }
	 }
}

int rmq(int l, int r) {
	 int l2 = logs[r - l + 1];
     int res = min(table[l][l2], table[r- (1 << l2) + 1][l2]);
	 return res;
}
// find the leftmost index such that all numbers from 
// index to idx is no less than a[idx]
int findL(int idx) {
	int low = 1, high = idx;
	int ret = idx;
	while (low <= high) {
		  int mid = low + (high - low) / 2;
		  if (rmq(mid, idx) >= a[idx]) {
		  	 ret = mid;
		  	 high = mid - 1;
		  } else {
		  	 low = mid + 1;
		  }
	}
	
	return ret;
}

int findR(int idx) {
	int low = idx, high = n;
	int ret = idx;
	while (low <= high) {
		  int mid = low + (high - low) / 2;
		  if (rmq(idx, mid) >= a[idx]) {
		  	 ret = mid;
		  	 low = mid + 1;
		  } else {
		  	 high = mid - 1;
		  }
	}
	
	return ret;
}


int main() {
	scanf("%d", &n);
	int i, L, R, j;
	for (i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	
	build();
	
	for (i = 1; i <= n; i++) {
		L = findL(i), R = findR(i);
		mx[R - L + 1] = max(mx[R - L + 1], a[i]);
	}
	
	vector<int> s;
	for (i = 1; i <= n; i++) {
		if (!mx[i]) continue;
		if (s.empty()) {
		   s.push_back(i);
		} else {
		   while (!s.empty() && mx[i] >= mx[s.back()]) {
               s.pop_back();
		   }
		   s.push_back(i);
		}
	}
	
	for (i = 0, j = 1; i < (int) s.size(); i++) {
		while (j <= n && j <= s[i]) {
			  ans[j] = mx[s[i]];
			  j++;
		}
	}
	
	for (i = 1; i <= n; i++) {
		printf("%d ", ans[i]);
	}
	printf("\n");
	return 0;
}
