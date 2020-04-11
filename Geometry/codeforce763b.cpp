#include <bits/stdc++.h>

using namespace std;

int main() {
	int x1, y1, x2, y2, n;
	scanf("%d", &n);
	printf("YES\n");
	while (n > 0) {
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		x1 = abs(x1), y1 = abs(y1);
		if (x1 % 2 == 0 && y1 % 2 == 0) {
			printf("1\n");
		} else if (x1 % 2 == 0 && y1 % 2 == 1) {
			printf("2\n");
		} else if (x1 % 2 == 1 && y1 % 2 == 0) {
			printf("3\n");
		} else {
			printf("4\n");
		}
		--n;
	}
	return 0;
}