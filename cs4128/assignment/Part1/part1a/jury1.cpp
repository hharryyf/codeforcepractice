#include <bits/stdc++.h>
#define MAX_SIZE 1024

using namespace std;

int a[MAX_SIZE + 1];

int main() {
	int n, q;
	scanf("%d", &n);
	scanf("%d", &q);
	int i;
	for (i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	
	
	while (q > 0) {
		int l, r;
		scanf("%d%d", &l, &r);
		unordered_map<int, int> st;
		int cnt = 0;
		for (i = l; i <= r; i++) {
			st[a[i]]++;
		}
		
		unordered_map<int, int> :: iterator iter = st.begin();
		while (iter != st.end()) {
			if (iter->second == 1) {
				cnt++;
			}
			iter++;
		}
		
		cout << cnt << endl;
		q--;
	}
	return 0;
}
