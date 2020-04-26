#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 2097312
typedef long long ll;
using namespace std;

vector<int> hp[MAX_SIZE];
int val[MAX_SIZE];
int rem[MAX_SIZE];

void merge(int idx) {
	int i = 0, j = 0, sz1 = hp[idx * 2].size(), sz2 = hp[idx * 2 + 1].size();
	while (i < sz1 && j < sz2) {
		if (hp[idx * 2][i] < hp[idx * 2 + 1][j]) {
			hp[idx].push_back(hp[idx * 2][i++]);
		} else {
			hp[idx].push_back(hp[idx * 2 + 1][j++]);
		}
	}
	
	while (i < sz1) {
		hp[idx].push_back(hp[idx * 2][i++]);
	}
	
	while (j < sz2) {
		hp[idx].push_back(hp[idx * 2 + 1][j++]);
	}
	hp[idx].push_back(val[idx]);
}

int main() {
	int T;
	scanf("%d", &T);
	while (T > 0) {
		int i, n, h, g, j;
		ll ans = 0;
		scanf("%d%d", &h, &g);
		set<int> st;
		n = (1 << h) - 1;
		for (i = 1; i <= n; ++i) {
			scanf("%d", &val[i]);
			hp[i].clear();
		}
		
		for (i = (1 << (h-1)); i < (1 << h); ++i) {
			hp[i].push_back(val[i]);
		}
		
		for (i = (1 << (h-1)) - 1; i >= 1; --i) {
			merge(i);
		}
		
		for (i = (1 << g) - 1; i >= (1 << (g-1)); --i) {
			rem[i] = hp[i][0];
			ans += rem[i];
			st.insert(rem[i]);
		}
		
		for (i = (1 << (g-1)) - 1; i >= 1; --i) {
			for (j = 0 ; j < (int) hp[i].size(); ++j) {
				if (hp[i][j] > rem[i * 2] && hp[i][j] > rem[i * 2 + 1]) {
					rem[i] = hp[i][j];
					ans += hp[i][j];
					st.insert(hp[i][j]);
					break;
				}
			}
		}
		
		printf("%I64d\n", ans);
		for (i = (1 << h) - 1; i >= 1; --i) {
			if (st.find(val[i]) == st.end()) {
				printf("%d ", i);
			}
		}
		printf("\n");
		--T;
	}
	return 0;
}