#include <bits/stdc++.h>
#define MAX_SIZE 101001

using namespace std;

int prefix[MAX_SIZE];
int arr[MAX_SIZE];
int count3[MAX_SIZE];


int main(int argc, char *argv[]) {
	int i, n;
	scanf("%d", &n);
	for (i = 1 ; i <= n; i++) {
		scanf("%d", &arr[i]);
		prefix[i] = prefix[i-1] + arr[i];
	}
	
	if (prefix[n] % 3 != 0) {
		printf("0\n");
		return 0;
	}
	
	
	for (i = 1; i <= n; i++) {
		if (prefix[i] * 3 == prefix[n]) {
			count3[i] = count3[i-1] + 1;	
		} else {
			count3[i] = count3[i-1];
		}
	}
	
	long long ans = 0ll;
	for (i = n; i > 2; i--) {
		if ((prefix[n] - prefix[i-1]) * 3 == prefix[n]) {
			ans += count3[i - 2];
		}
	}
	
	cout << ans << endl;
	return 0;
}
