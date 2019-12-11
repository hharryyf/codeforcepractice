#include <bits/stdc++.h>
typedef long long ll;
#define MOD 1000000007
#define MAX_SIZE 1000011
using namespace std;

ll A[MAX_SIZE], B[MAX_SIZE];

int main() {
	int n;
	scanf("%d", &n);
	A[0] = 0, B[0] = 1;
	for (int i = 1; i <= n; i++) {
		A[i] = B[i-1] % MOD;
		B[i] = (B[i-1] + A[i-1]) % MOD;
	}
	
	cout << (A[n] + B[n]) % MOD << endl;
	return 0;
}
