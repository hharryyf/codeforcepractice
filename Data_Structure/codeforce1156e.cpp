#include <bits/stdc++.h>
#define MAX_SIZE 262192
using namespace std;

int L[MAX_SIZE], R[MAX_SIZE];
int val[MAX_SIZE];
int p[MAX_SIZE];
long long ans = 0;

int main() {
	int n, i, j;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		scanf("%d", &val[i]);
		p[val[i]] = i;
	}
	
	stack<int> st;
	for (i = 1; i <= n; ++i) {
		while (!st.empty() && val[st.top()] < val[i]) {
			st.pop();
		}
		
		if (st.empty()) {
			L[i] = 1;
		} else {
			L[i] = st.top() + 1;
		}
		st.push(i);
	}
	
	while (!st.empty()) st.pop();
	
	for (i = n; i >= 1; --i) {
		while (!st.empty() && val[st.top()] < val[i]) {
			st.pop();
		}
		
		if (st.empty()) {
			R[i] = n;
		} else {
			R[i] = st.top() - 1;
		}
		st.push(i);
	}
	
	for (i = 1; i <= n; ++i) {
		// cout << L[i] << " " << R[i] << endl;
		if (i - L[i] > R[i] - i) {
			for (j = i + 1; j <= R[i]; ++j) {
				if (p[val[i] - val[j]] >= L[i] && p[val[i] - val[j]] < i) {
					ans++;
				}
			}
		} else {
			for (j = L[i]; j < i; ++j) {
				if (p[val[i] - val[j]] > i && p[val[i] - val[j]] <= R[i]) {
					ans++;
				}
			}
		}
	}
	
	printf("%I64d\n", ans);
	return 0;
}