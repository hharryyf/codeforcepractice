#include <bits/stdc++.h>

using namespace std;

int main() {
	srand(time(NULL));
	int n = 55;
	cout << n << endl;
	int i;
	for (i = 0 ; i < n; i++) {
		cout << (-500 + rand() % 1000) << " " << (1 + rand() % 25) << endl;
	}
	return 0;
}
