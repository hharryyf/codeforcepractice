#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define MAX_SIZE 524292

int arr[MAX_SIZE], tmp[MAX_SIZE];

ll divc(int l, int r) {
	if (l == r) return 0ll;
	if (l > r) return 0ll;
	int mid = l + (r - l) / 2;
	ll L = divc(l, mid), R = divc(mid + 1, r);
	int i = l, j = mid + 1, k = l;
	ll cross = 0ll;
	while (i <= mid && j <= r) {
		if (arr[i] <= arr[j]) {
			tmp[k++] = arr[i++];
		} else {
			tmp[k++] = arr[j++];
			cross += (ll) (mid - i + 1);
		}
	}
	
	while (i <= mid) tmp[k++] = arr[i++];
	while(j <= r) tmp[k++] = arr[j++];
	for (i = l; i <= r; i++) arr[i] = tmp[i];
	return L + R + cross;
}

int main() {
	int n;
	while (scanf("%d", &n)) {
		if (n == 0) break;
		int v;
		for(int i = 0; i < n; i++) {
			cin >> v;
			arr[i] = v;
		}
		cout << divc(0,n-1) << endl;
	}
	return 0;
}
