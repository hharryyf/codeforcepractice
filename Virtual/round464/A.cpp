#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 100000
using namespace std;
int f[MAX_SIZE];
int N;

int main() {
	int i;
	scanf("%d", &N);
	for (i = 1; i <= N; ++i) scanf("%d", &f[i]);
	for (i = 1; i <= N; ++i) {
		// i->f[i]->f[f[i]]->f[f[f[i]]]
		if (f[f[f[i]]] == i) {
			printf("YES\n");
			return 0;
		}
	}
	printf("NO\n");
	return 0;
}
