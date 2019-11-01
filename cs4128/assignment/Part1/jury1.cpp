#include <bits/stdc++.h>
#define MAX_SIZE 1024

using namespace std;

int a[MAX_SIZE + 1];

int main() {
	int n, q;
	scanf("%d%d", &n, &q);
	int i;
	for (i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	
	while (q > 0) {
		int l, r;
		scanf("%d%d", &l, &r);
		set<int> st;
		for (i = l; i <= r; i++) {
			st.insert(a[i]);
		}
		
		cout << st.size() << endl;
		q--;
	}
	return 0;
}
