#include <bits/stdc++.h>
#define MAX_SIZE 1000011
using namespace std;

int prefix[MAX_SIZE];
vector<int> g[MAX_SIZE >> 1];
int n;

int main() {
	int n, c, i;
	scanf("%d%d", &n, &c);
	
	for (i = 1; i <= n; ++i) {
		int l, v;
		scanf("%d", &l);
		while (l > 0) {
			scanf("%d", &v);
			g[i].push_back(v);
			--l;
		}
	}
	
	for (i = 1; i < n; ++i) {
		// compare vector i and vector i+1
		// if i is longer than i+1 and no different element found, print -1 exit
		int j = 0, sz1 = (int) g[i].size(), sz2 = (int) g[i+1].size();
		int pos = -1;
		for (j = 0 ; j < sz1 && j < sz2; ++j) {
			if (g[i][j] != g[i+1][j]) {
				pos = j;
				break;
			}
		}
		
		if (pos == -1) {
			if (sz1 > sz2) {
				printf("-1\n");
				return 0;
			} 
			// we don't need prefix[c]--, because we only care about pre[0, c-1]
			prefix[0]++;
		} else {
			if (g[i][pos] < g[i+1][pos]) {
				prefix[0]++;
				prefix[c - g[i+1][pos] + 1]--;
				prefix[c - g[i][pos] + 1]++;
			} else {
				prefix[c - g[i][pos] + 1]++;
				prefix[c - g[i+1][pos] + 1]--;
			}
		}
	}
	
	for (i = 0; i < c; ++i) {
		if (i > 0) {
			prefix[i] = prefix[i-1] + prefix[i];
		}
		// cout << prefix[i] << " ";
	}
	// cout << endl;
	for (i = 0; i < c; ++i) {
		if (prefix[i] == n - 1) {
			printf("%d\n", i);
			return 0;
		}
	}
	
	printf("-1\n");
	return 0;
}