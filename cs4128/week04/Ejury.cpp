#include <bits/stdc++.h>
#define MAX_SIZE 100001

using namespace std;

struct wms {
	int x;
	int r;
};


wms warms[MAX_SIZE];

int activate[MAX_SIZE];

int visited[MAX_SIZE];

int n;

int main() {
	int i, j;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		scanf("%d%d", &warms[i].x, &warms[i].r);
	}	
	
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			activate[j] = 0;	
		}
		
		activate[i] = 1;
		int change = 1;
		while (change) {
			change = 0;
			for (j = 1; j <= n; j++) {
				if (activate[j] == 1) {
					for (int k = 1; k <= n; k++) {
						if (warms[j].x + warms[j].r >= warms[k].x && warms[j].x - warms[j].r <= warms[k].x && activate[k] == 0) {
							activate[k] = 1;
							change = 1;
						}
					}
				}
			}	
		}
		int cnt = 0;
		for (j = 1; j <= n; j++) {
			if (activate[j] == 1) cnt++;
		}
		cout << cnt << endl;
	}
	cout << endl;
	return 0;
}
