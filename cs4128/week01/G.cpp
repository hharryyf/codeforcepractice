#include <vector>
#include <cstdio>
#include <iostream>
#include <algorithm>
#define MAX_SIZE (500000 + 11)
using namespace std;

int n, k;

long long ans = 0ll;

char a[MAX_SIZE], b[MAX_SIZE];

int main() {
	int i;
	scanf("%d%d", &n, &k);
	scanf("%s", a);
	scanf("%s", b);
	long long curr = 0ll;
	for (i = 0 ; i < n; i++) {
		if (curr >= (long long) k) {
			ans += k;			
		} else {  
			curr = curr * 2 + (long long) (b[i] - a[i]);
			ans += min(curr + 1, (long long) k);
		}		
	}
	cout << ans << endl;
	return 0;
}
