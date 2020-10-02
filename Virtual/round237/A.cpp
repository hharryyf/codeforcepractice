#include <bits/stdc++.h>
#define MAXN 305
using namespace std;

int n;
string s[MAXN];
char c1, c2;

bool check() {
	for (int r = 0; r < n; r++) {
		if (s[r][r] != c1) return false;
		if (s[n-1-r][r] != c1) return false;
		for (int c = 0; c < n; c++) {
			if (r == c) continue;
			if (n-1-r == c) continue;
			if (s[r][c] != c2) return false;
		}
	}
	return true;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) cin >> s[i];
	c1 = s[0][0];
	c2 = s[0][1];
	if (c1 == c2) {
		cout << "NO" << endl;
	} else {
		if (check()) {
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
	}
}