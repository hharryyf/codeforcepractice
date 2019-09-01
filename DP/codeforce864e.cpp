#include <bits/stdc++.h>

using namespace std;

// dp[i][j] refers to the maximum profit of saving upto the first i items
// using j amount of time d[i] > j means the jth item could be saved,
// otherwise, the item cannot be saved
int dp[103][2011];
int ans = 0;
typedef struct itm {
	int t;
	int d;
	int p;
	int id;
} Item;

Item arr[2011];

static bool cmp(Item &it1, Item &it2) {
	return it1.d < it2.d;
}

int main(int argc, char *argv[]) {
	int n, i, j;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		scanf("%d%d%d", &arr[i].t, &arr[i].d, &arr[i].p);
		arr[i].id = i;
	}
	
	sort(arr + 1, arr + 1 + n, cmp);
	
	for (i = 1; i <= n; i++) {
		for (j = 0; j < arr[i].d; j++) {
			if (j >= arr[i].t) {
				dp[i][j] = max(dp[i-1][j], dp[i-1][j - arr[i].t] + arr[i].p);
			} else {
				dp[i][j] = dp[i-1][j];
			}
			
			if (i == n) {
				ans = max(dp[i][j], ans);
			}
		}
	}
	
	printf("%d\n", ans);
	vector<int> ret = vector<int>();
	i = n, j = arr[n].d - 1;
	while (i >= 1 && j >= 0) {
		// cout << "(" << i << " ," << j << ")" << " " << dp[i][j] << " ans= " << ans << endl;
		if (j >= arr[i].d) {
			j--;
		} else {
			if (j >= arr[i].t && ans == dp[i-1][j - arr[i].t] + arr[i].p) {
				ans = ans - arr[i].p;
				ret.push_back(arr[i].id);
				j = j - arr[i].t;
				i--;
			} else if (dp[i-1][j] == ans) {
				i--;
			} else {
				j--;
			}
		}
	}
	
	printf("%d\n", (int) ret.size());
	for (i = (int) ret.size() - 1; i >= 0; i--) {
		printf("%d ", ret[i]);
	}
	
	printf("\n");
	return 0;
}
