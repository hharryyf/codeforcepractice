#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

char st[2011][2011];
int N;

void solve(int num) {
	int i, j, ans = 0, up = 2011, down = 0, left = 2011, right = 0;
	for (i = 1; i <= N; ++i) {
		for (j = 1; j <= N; ++j) {
			if (st[i][j] == num + '0') {
				up = min(up, i);
				down = max(down, i);
				left = min(left, j);
				right = max(right, j);
			}
		}
	}

	// cout << "for " << num << " " << up << " " << down << " " << left << " " << right << endl;

	for (i = 1; i <= N; ++i) {
		int L = 2011, R = 0;
		for (j = 1; j <= N; ++j) {
			if (st[i][j] == num + '0') {
				L = min(L, j), R = max(R, j);
			}
		}

		if (R >= L) {
			ans = max(ans, (i - up) * (N - L));
			ans = max(ans, (down - i) * (N - L));
			ans = max(ans, (i - up) * (R - 1));
			ans = max(ans, (down - i) * (R - 1));
		}

		if (R > L) {
			ans = max(ans, (R - L) * (i - 1));
			ans = max(ans, (R - L) * (N - i));
		}
	}

	for (i = 1; i <= N; ++i) {
		int L = 2011, R = 0;
		for (j = 1; j <= N; ++j) {
			if (st[j][i] == num + '0') {
				L = min(L, j), R = max(R, j);
			}
		}

		if (R >= L) {
			ans = max(ans, (i - left) * (N - L));
			ans = max(ans, (right - i) * (N - L));
			ans = max(ans, (i - left) * (R - 1));
			ans = max(ans, (right - i) * (R - 1));
		}

		if (R > L) {
			ans = max(ans, (R - L) * (i - 1));
			ans = max(ans, (R - L) * (N - i));
		}
	}

	printf("%d ", ans);
}

int main() {
	int T, i;
	scanf("%d", &T);
	while (T-- > 0) {
		scanf("%d", &N);
		for (i = 1; i <= N; ++i) scanf("%s", st[i] + 1);
		for (i = 0 ; i <= 9; ++i) {
			solve(i);
		}				
		printf("\n");
	}
	return 0;
}