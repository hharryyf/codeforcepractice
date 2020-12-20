#include <bits/stdc++.h>
#define MAX_SIZE 55
typedef long long ll;
using namespace std;

int a[MAX_SIZE];
int N;

int main() {
	int T;
	scanf("%d", &T);
	while (T-- > 0) {
		int N, i;
		scanf("%d", &N);
		for (i = 1; i <= N; ++i) scanf("%d", &a[i]);
		int idx = 0;
		for (int j = 1; j <= N; ++j) {
			for (i = 0; i <= 29; ++i) {
				if (abs((1 << i) - a[j]) <= abs((1 << idx) - a[j])) {
					idx = i;
				}
			}
			printf("%d ", 1 << idx);
		}
		printf("\n");
	}
	return 0;
}