#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;
typedef long long ll;
int a[MAX_SIZE], b[MAX_SIZE];
int score[MAX_SIZE];

int main() {
	int n, i;
	scanf("%d", &n);	
	for (i = 0 ; i < n; ++i) {
		scanf("%d", &a[i]);
	}

	for (i = 0 ; i < n; ++i) {
		scanf("%d", &b[i]);
	}

	for (i = 0 ; i < n; ++i) {
		if (b[i] == 1) {
			score[i] = 1;
		}
	}

	int A = 0, B = 0;
	for (i = 0 ; i < n; ++i) {
		if (a[i] == 1) A += score[i] * a[i];
		if (b[i] == 1) B += score[i] * b[i];
	}

	int cnt = 0;
	for (i = 0 ; i < n; ++i) {
		if (a[i] == 1 && b[i] == 0) {
			++cnt;
		}
	}

	if (cnt == 0 && A <= B) {
		printf("-1\n"); 
		return 0;
	}

	if (A > B) A = B;
	printf("%d\n", (B - A) / cnt + 1);
	return 0;
}
