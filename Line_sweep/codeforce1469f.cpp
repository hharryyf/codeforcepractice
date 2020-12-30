#include <bits/stdc++.h>
const int maxn = 800011;
using namespace std;

int cnt[maxn << 1], l[maxn];
int N, K;


int main() {
	int i, j, tol = 0;
	scanf("%d%d", &N, &K);
	for (i = 1; i <= N; ++i) scanf("%d", &l[i]);
	sort(l + 1, l + 1 + N, greater<int>());
	cnt[0] = 1, cnt[1] = -1;
	for (i = 0, j = 1; i < maxn; ++i) {
		tol = tol + cnt[i];
		cnt[i + 1] += cnt[i];
		if (tol + cnt[i + 1] >= K) {
			printf("%d\n", i + 1);
			return 0;
		}

		while (j <= N && cnt[i] > 0) {
			cnt[i]--;
			int L = l[j] / 2, R = (l[j] - 1) / 2;
			cnt[i + 2]++, cnt[L + 2 + i]--;
			cnt[i + 2]++, cnt[R + 2 + i]--;
			j++;
			tol--;
		}
	}

	printf("-1\n");
	return 0;
}