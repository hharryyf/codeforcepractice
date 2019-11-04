#include <bits/stdc++.h>

using namespace std;

int main() {
	srand(time(NULL));
	int n, q;
	
	vector<int> upd;
	vector<pair<int, int> > qr;
	n = 12 + rand() % 10;
	q = 4 * n + rand() % 100;
	cout << n << " " << q << endl;
	int i;
	for (i = 1; i <= q; i++) {
		int op;
		if ((int) upd.size() == 0) {
			op = 2 * (rand() % 2) + 1;
		} else {
			op = 1 + rand() % 3;
		}
		
		int v1 = 1 + rand() % n, v2 = 1 + rand() % n;
		if (op == 1) {
			cout << op << " " <<v1 << " " << v2 << endl;
			upd.push_back(i);
		} else if (op == 2) {
			int index = rand() % ((int) upd.size());
			cout << op << " " << upd[index] << endl;
			int tmp = upd[index];
			upd[index] = upd[(int) upd.size() - 1];
			upd[(int) upd.size() - 1] = tmp;
			upd.pop_back();
		} else {
			cout << op << " " << v1 << " " << v2 << endl;
		}
	}
	return 0;
}
