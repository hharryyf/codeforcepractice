#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 35011
typedef long long ll;
using namespace std;

int a[MAX_SIZE];
int dp[MAX_SIZE][52];

struct twopt {
	int curr = 0;
	int cnt[MAX_SIZE];
	int L = 1;
	int R = 0;
	void add(int idx) {
		 int v = a[idx];
		 ++cnt[v];
		 if (cnt[v] == 1) curr++;
	}
	
	void del(int idx) {
		 int v = a[idx];
		 --cnt[v];
		 if (cnt[v] == 0) curr--;
	}
	
	int cost(int l, int r) {
		while (L < l) del(L++);
		while (L > l) add(--L);
		while (R > r) del(R--);
		while (R < r) add(++R);
		return curr;
	}
};

twopt s;
int n, q;

void divc(int start, int end, int l, int r, int k) {
	if (l > r) return;
	int pos = -1;
	int mid = l + (r - l) / 2;
	dp[mid][k] = 0;
	for (int i = start; i <= min(mid - 1, end); i++) {
		int newcost = dp[i][k-1] + s.cost(i+1, mid);
		if (newcost > dp[mid][k]) {
			pos = i;
			dp[mid][k] = newcost;
		}
	}
	divc(start, pos, l, mid - 1, k);
	divc(pos, end, mid + 1, r, k);
}

int main() {
	scanf("%d%d", &n, &q);
	int i;
	for (i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (i = 1; i <= n; i++) dp[i][1] = s.cost(1, i);
	for (i = 2; i <= q; i++) {
		divc(0, n, 1, n, i);
	} 
	
	printf("%d\n", dp[n][q]);
	return 0;
}
