#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

vector<int> g[MAX_SIZE];
double dp[MAX_SIZE];

void preprocess() {
	int i, j;
	for (i = 1; i <= 100000; ++i) {
		for (j = 1; j <= 100000; ++j) {
			if (i * j > 100000) break;
			g[i * j].push_back(i);
		}
		dp[i] = -1.0;
	}
}

double f(int v) {
	if (v == 1) return 0.0;
	if (dp[v] > -0.5) return dp[v];
	int sz = g[v].size();
	double ret = 0.0;
	for (int nv : g[v]) {
		if (nv != 1) {
			ret += f(v/nv) / (1.0 * sz);
		}
	}
	dp[v] = (ret + 1.0) * 1.0 * sz / (1.0 * (sz-1));
	return dp[v];
}

int main() {
	int n, T, t;
	preprocess();
	scanf("%d", &T);
	for (t = 1; t <= T; t++) {
		scanf("%d", &n);
		double ret = f(n);
		printf("Case %d: %.10lf\n", t, ret);
	}
	return 0;
}