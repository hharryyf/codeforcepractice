#include <bits/stdc++.h>
#define MAX_SIZE 500111
using namespace std;

pair<int, int> edg[MAX_SIZE];
int visited[MAX_SIZE];
int ans[MAX_SIZE];
int main() {
	int T;
	scanf("%d", &T);
	while (T > 0) {
		int n, m, i;
		scanf("%d%d", &n, &m);
		for (i = 1; i <= 3 * n; ++i) {
			visited[i] = 0;
		}
		
		for (i = 1; i <= m; ++i) scanf("%d%d", &edg[i].first, &edg[i].second);
		
		int cnt = 0;
		for (i = 1; i <= m; ++i) {
			if (!visited[edg[i].first] && !visited[edg[i].second]) {
				cnt++;
				ans[cnt] = i;
				visited[edg[i].first] = visited[edg[i].second] = 1;
			}
			
			if (cnt >= n) break;
		}
		
		if (cnt >= n) {
			printf("Matching\n");
			for (i = 1; i <= cnt; ++i) {
				printf("%d ", ans[i]);
			}
			printf("\n");
		} else {
			printf("IndSet\n");
			for (i = 1, cnt = 1; i <= 3 * n && cnt <= n; ++i) {
				if (!visited[i]) {
					printf("%d ", i);
					cnt++;
				}
			}
			printf("\n");
		}
		T--;
	}
	return 0;
}