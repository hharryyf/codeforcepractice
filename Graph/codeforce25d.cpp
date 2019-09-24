#include <bits/stdc++.h>
#define MAX_SIZE 1025
using namespace std;

int f[MAX_SIZE];

int find(int x) {
	if (f[x] == x) return f[x];
	return f[x] = find(f[x]);
}

void unionset(int a, int b) {
	int x = find(a), y = find(b);
	f[x] = y;
}

int g[MAX_SIZE][MAX_SIZE];
int cnt = 0;
vector<pair<int, int> > ans;

int main() {
	int n, i, j;
	cin >> n;
	for (i = 1; i <= n; i++) f[i] = i;
	
	for (i = 0; i < n - 1; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		if (find(v1) == find(v2)) {
			cnt++;
			ans.push_back(make_pair(v1, v2));
		} else {
			g[v1][v2] = 1;
			g[v2][v1] = 1;
			unionset(v1, v2);
		}
	}
	
	cout << cnt << endl;
	for (i = 1 ; i <= n && cnt > 0; i++) {
		for (j = i + 1; j <= n && cnt > 0; j++) {
			if (g[i][j] == 0 && find(i) != find(j)) {
				cnt--;
				cout << ans[cnt].first << " " << ans[cnt].second << " " << i << " " << j << endl;
				g[i][j] = 1;
				unionset(i, j);
			}
		}
	}
	return 0;
}
