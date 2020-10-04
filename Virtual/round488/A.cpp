// Tom solved this problem

#include <bits/stdc++.h>
#define MAXN 20
using namespace std;

int n, m;
int x[MAXN];
int y[MAXN];
int exists[MAXN];
int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> x[i];
	for (int i = 0; i < m; i++) {
		cin >> y[i];
		exists[y[i]] = true;
	}
	for (int i = 0; i < n; i++) {
		if (exists[x[i]]) cout << x[i] << ' ';
	}
	cout << endl;
}
