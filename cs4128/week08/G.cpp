#include <bits/stdc++.h>
#define MAX_SIZE 100111
#define INF 20000000000ll

typedef long long ll;

using namespace std;

int n, q;

int a[MAX_SIZE];

ll cnt[MAX_SIZE];

ll dp[21][MAX_SIZE];

// the range where the cnt array is currently controlling
int repl, repr;
ll curr = 0;


/* precon*/
ll cost(int ql, int qr) {
	// cout << "query " << ql << " " << qr << " init " << repl << " " << repr << endl;
	while (repr < qr) {
		curr = curr + cnt[a[repr + 1]];
		cnt[a[repr + 1]]++;
		repr++;
	}
	
	while (repr > qr) {
		curr = curr - (cnt[a[repr]]-1);
		cnt[a[repr]]--;
		repr--;
	}
	
	while (repl > ql) {
		curr = curr + cnt[a[repl-1]];
		cnt[a[repl-1]]++;
		repl--;
	}
	
	while (repl < ql) {
		curr = curr - (cnt[a[repl]]-1);
		cnt[a[repl]]--;
		repl++;
	}
	
	// cout << ql << " " << qr << " " << curr << endl;
	return curr;
}

void divc(int start, int end, int l, int r, int k) {
	
	if (l > r) return;
	
	int pos = -1;
	
	int mid = l + (r - l) / 2;
	
	dp[k][mid] = INF;
	
	for (int i = start; i <= min(mid - 1, end); i++) {
		ll newcost = dp[k-1][i] + cost(i+1, mid);
		if (newcost < dp[k][mid]) {
			pos = i;
			dp[k][mid] = newcost;
		}
	}
	divc(start, pos, l, mid - 1, k);
	divc(pos, end, mid + 1, r, k);
}

int main() {
	scanf("%d%d", &n, &q);
	int i;
	for (i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		dp[1][i] = dp[1][i-1] + cnt[a[i]];
		curr = dp[1][i];
		cnt[a[i]]++;
	}
	
	repl = 1;
	repr = n;
	
	for (i = 2; i <= q; i++) {
		divc(0, n, 1, n, i);
	}
	
	cout << dp[q][n] << endl;
	return 0;
}
