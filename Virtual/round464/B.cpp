#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;
ll f[MAX_SIZE];
ll tol;
int N;
int main() {
	int i;
	scanf("%I64d%d", &tol, &N);
	ll rem = tol;
	int id = 0;
	ll num = 0;
	for (i = 1; i <= N; ++i) {
		scanf("%I64d", &f[i]);
		if (tol % f[i] <= rem) {
			id = i;
			rem = tol % f[i];
			num = tol / f[i];
		}
	}

	cout << id << " " << num << endl;
	return 0;
}
