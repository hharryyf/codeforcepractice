#include <bits/stdc++.h>
#define MAX_SIZE 300111
using namespace std;

const int mod = 1e9 + 7;
int N, M;
char st[MAX_SIZE];

int main() {
	int i, curr = 0, cnt = 0;
	scanf("%d%d", &N, &M);
	scanf("%s", st + 1);
	for (i = 1; i <= N; ++i) {
		curr = curr * 10 + (st[i] - '0');
		curr %= M;
		if (curr == 0) {
			cnt++;
		}
	}

	if (cnt == 0 || curr != 0) {
		printf("0\n");
		return 0;
	}

	int ans = 1;
	for (i = 1 ; i < cnt; ++i) {
		ans = ans * 2;
		ans %= mod;
	}

	printf("%d\n", ans);
	return 0;
}