#include <bits/stdc++.h>
#define MAX_SIZE 500011
using namespace std;

vector<int> ret;
int l, r, N;
int pre[MAX_SIZE];
char st[MAX_SIZE];

int cost(int L, int R) {
	if (L != 0) {
		return pre[R] - pre[L - 1] + (R - L);
	}
	return pre[R] + (R - L);
}

int solve(int x) {
	int i = 0, cnt = 0, tol = 0;
	while (i < N) {
		int low = i, high = N - 1, r = i;
		while (low <= high) {
			int mid = (low + high) / 2;
			if (cost(i, mid) <= x) {
				r = mid;
				low = mid + 1;
			} else {
				high = mid - 1;
			}
		}

		tol += ret[i];
		cnt++;
		// cout << i << " ";
		i = r + 1;
	}

	// cout << endl;
	return tol + (cnt - 1);
}

int main() {
	char curr;
	int cnt = 0, i;
	while ((curr = getchar()) != '\n') {
		if (curr == ' ') {
			if (cnt != 0) {
				ret.push_back(cnt);
			}
			cnt = 0;
		} else {
			cnt++;
		}
	}

	if (cnt != 0) ret.push_back(cnt);
	N = ret.size();
	for (i = 0 ; i < N; ++i) {
		pre[i] = ret[i];
		if (i != 0) pre[i] = pre[i] + pre[i-1]; 
	}

	scanf("%d%d", &l, &r);
	for (i = l; i <= r; ++i) {
		printf("%d\n", solve(i));
	}
	return 0;
}