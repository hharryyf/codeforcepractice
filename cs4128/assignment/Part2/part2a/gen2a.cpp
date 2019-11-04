#include <bits/stdc++.h>

using namespace std;

int main() {
	srand(time(NULL));
	int n = 12 + rand() % 100;
	int q = 10 * n + rand() % n;
	cout << n << " " << q << endl;
	int hasedge = 0;
	while (q > 0) {
		int op;
		
		if (hasedge > 0) {
		   op = 1 + rand() % 3;
		} else {
			op = 2 * (rand() % 2) + 1;
		}
		
		if (op == 1) {
			cout << op << " " << (1 + rand() % n) << " " << (1 + rand() % n) << endl;
			hasedge++;	
		} else if (op == 2) {
			cout << op << endl;
			hasedge--;
		} else {
			cout << op << " " << (1 + rand() % n) << " " << (1 + rand() % n) << endl;
		}
		q--;
	}
	return 0;
}
