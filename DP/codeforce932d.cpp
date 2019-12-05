#include <bits/stdc++.h>
typedef long long ll;

#define MAX_SIZE 401111

using namespace std;

// record the 1 << i ancestor of the node v
ll f[MAX_SIZE][20];
// weight of node i
ll wt[MAX_SIZE];
// record the cumulative sum of the sequence
ll sm[MAX_SIZE];
// true depth of the node
ll depth[MAX_SIZE];

int cnt = 1;
// we want to find the node that is the first node which wt not less than w
void addedge(int v, ll w) {
	int i;
	wt[++cnt] = w;
	if (wt[v] >= w) {
		f[cnt][0] = v;
	} else {
		// we need to find the ancestor of v such that wt[v'] >= w
		for (i = 19; i >= 0; i--) {
			if (f[v][i]) {
				if (wt[f[v][i]] < w) {
					v = f[v][i];
				}
			}
		}
		
		f[cnt][0] = f[v][0];
	}
	
	sm[cnt] = w + sm[f[cnt][0]];
	depth[cnt] = depth[f[cnt][0]] + 1;
	for (i = 1; i < 20; i++) {
		f[cnt][i] = f[f[cnt][i-1]][i-1];
	}
}

ll getans(int v, ll w) {
	int i;
	ll ans = 0;
	for (i = 19; i >= 0; i--) {
		if (f[v][i]) {
			if (w >= sm[v] - sm[f[v][i]]) {
				ans = ans + depth[v] - depth[f[v][i]]; 
				w = w - (sm[v] - sm[f[v][i]]); 
				v = f[v][i];
			}
		}
	}
	
	if (wt[v] <= w) ans++;
	return ans;
}

int main() {
	int q, t;
	ll lst = 0;
	
	scanf("%d", &q);
	depth[1] = 1;
	while (q > 0) {
		scanf("%d", &t);
		ll a, b;
		scanf("%lld%lld", &a, &b);
		a = a ^ lst;
		b = b ^ lst;
		if (t == 1) {
			addedge((int) a, b);
		} else {
			lst = getans((int) a, b);
			printf("%lld\n", lst);
		}
		q--;
	}
	return 0;
}
