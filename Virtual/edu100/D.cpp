#include <bits/stdc++.h>
#define MAX_SIZE 200011
typedef long long ll;
using namespace std;
int a[MAX_SIZE];
int N;

int main() {
	int T;
	scanf("%d", &T);
	while (T-- > 0) {
		set<int> st;
		int i, R = 0, L = 0;
		scanf("%d", &N);
		for (i = 1; i <= 2 * N; ++i) st.insert(i);
		for (i = 1; i <= N; ++i) {
			scanf("%d", &a[i]);
			st.erase(a[i]);
		}
		
		for (i = 1; i <= N; ++i) {
			if (*st.rbegin() > a[i]) {
				R++;
				st.erase(*st.lower_bound(a[i]));
			} else {
				st.erase(*st.begin());
			}
		}

		for (i = 1; i <= 2 * N; ++i) st.insert(i);
		for (i = 1; i <= N; ++i) st.erase(a[i]);
		// cout << "ok" << endl;
		for (i = N; i >= 1; --i) {
			if (*st.begin() > a[i]) {
				st.erase(*st.rbegin());
				L++;
			} else {
				auto iter = st.lower_bound(a[i]);
				iter = prev(iter);
				st.erase(*iter);
			}
		}
		
		// cout << L << " -- " << R << endl;
		printf("%d\n", R - L + 1);
	}
	return 0;
}