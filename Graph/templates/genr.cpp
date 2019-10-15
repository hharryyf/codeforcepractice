#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

int main() {
	int n, m, s;
	srand(time(NULL));
	n = rand() % 1000 + 500, m = n + (rand() % 1000) + 200, s = rand() % n + 1;
	cout << n << " " << m << " " << s << endl;
	for (int i = 0 ; i < m; i++) {
		int v1 = rand() % n + 1, v2 = rand() % n + 1;
		int w = rand() % 1000000;
		cout << v1 << " " << v2 << " " << w << endl;
	}
	return 0;
}
