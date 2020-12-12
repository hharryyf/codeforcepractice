#include <bits/stdc++.h>
#define MAX_SIZE 5011
typedef long long ll;
using namespace std;

int a[1011];

int main() {
	int T, i;
	scanf("%d", &T);
	while (T-- > 0) {
		int n, m;
		set<int> st;
		scanf("%d%d", &n, &m);
		for (i = 0 ; i < n; ++i) {
			scanf("%d", &a[i]);
		}

		for (i = 0 ; i < m; ++i) {
			int v;
			scanf("%d", &v);
			st.insert(v);
		}

		int cnt = 0;
		for (i = 0 ; i < n; ++i) {
			if (st.find(a[i]) != st.end()) cnt++;
		}

		printf("%d\n", cnt);
	}
	return 0;
}