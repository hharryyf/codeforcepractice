#include <bits/stdc++.h>
#define MAX_SIZE 1024

using namespace std;

int a[MAX_SIZE], b[MAX_SIZE];

pair<int, int> pt[MAX_SIZE];

int main() {
	srand(time(NULL));
	int n = 12 + rand() % 1000, q = max(n, 100 + rand() % 1000);
	cout << n << " " << q << endl;
	for (int i = 1; i <= n; i++) {
		a[i] = b[i] = i;
	}	
	
	for (int i = 1; i <= 4 * n; i++) {
		int idx1 = 1 + rand() % n, idx2 = 1 + rand() % n;
		swap(a[idx1], a[idx2]);
	}
	
	
	for (int i = 1; i <= 4 * n; i++) {
		int idx1 = 1 + rand() % n, idx2 = 1 + rand() % n;
		swap(b[idx1], b[idx2]);
	}
	
	for (int i = 1; i <= n; i++) {
		pt[a[i]].first = i;
		pt[b[i]].second = i;
	}
	
	for (int i = 1; i <= n; i++) {
		cout << pt[i].first << " " << pt[i].second << endl;
	}
	
	
	for (int i = 1; i <= q; i++) {
		int l, r, dn, up;
		l = 1 + rand() % n, r = 1 + rand() % n, dn = 1 + rand() % n, up = 1 + rand() % n;
		if (dn > up) {
			swap(dn, up);
		}
		
		if (l > r) {
			swap(l, r);
		}
		
		cout << l << " " << r << " " << dn << " " << up << endl;
	}
	return 0;
}
