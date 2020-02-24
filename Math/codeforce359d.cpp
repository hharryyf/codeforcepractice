#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 300011
typedef long long ll;
using namespace std;

int table[MAX_SIZE][20];
int logs[MAX_SIZE];
int n;
int gcd(int a, int b) {
  	return b ? gcd(b, a % b) : a;
}

void build() {
	int i, j;
	for (i = 1; i <= n; i++) scanf("%d", &table[i][0]);
	for (i = 2; i < MAX_SIZE; i++) logs[i] = logs[i / 2] + 1;
	for (j = 1; j <= 19; j++) {
		int prev2 = 1 << (j-1);
		for (i = 1; i <= n; i++) {
			int intEnd = i + prev2;
			if (intEnd <= n) table[i][j] = gcd(table[i][j-1], table[intEnd][j-1]);
			else {
				 table[i][j] = table[i][j-1];
			}
		}
	} 	 
}

int query(int l, int r) {
	int len = r - l + 1;
	int l2 = logs[len];
	return gcd(table[l][l2], table[r + 1 - (1 << l2)][l2]);
}

int getL(int idx) {
	int low = 1, high = idx;
	int ret = idx;
	while (low <= high) {
		  int mid = low + (high - low) / 2;
		  if (query(mid, idx) == table[idx][0]) {
		  	 ret = mid;
		  	 high = mid - 1;
		  } else {
		  	 low = mid + 1;
		  }
	}
	return ret;
}

int getR(int idx) {
	int low = idx, high = n;
	int ret = idx;
	while (low <= high) {
		  int mid = low + (high - low) / 2;
		  if (query(idx, mid) == table[idx][0]) {
		  	 ret = mid;
		  	 low = mid + 1;
		  } else {
		  	 high = mid - 1;
		  }
	}
	return ret;
}

int main() {
	int ans = 0;
	vector<int> st;
	int i;
	scanf("%d", &n);
	build();
	for (i = 1; i <= n; i++) {
		int L = getL(i), R = getR(i);
		if (R - L > ans) {
		   ans = R - L;
		   st.clear();
		   st.push_back(L);
		} else if (R - L == ans) {
		   st.push_back(L);
		}					
	}	
	
	sort(st.begin(), st.end());
	vector<int> disc;
	for (i = 0 ; i < (int) st.size(); i++) {
		if (i == 0 || st[i] != st[i-1]) disc.push_back(st[i]);
	}
	printf("%d %d\n", (int) disc.size(), ans);
	for (auto v : disc) {
		printf("%d ", v);
	}
	printf("\n");
	return 0;
}

