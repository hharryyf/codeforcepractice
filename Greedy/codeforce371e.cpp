#include <bits/stdc++.h>
#define MAX_SIZE 300011
typedef long long ll;
using namespace std;


pair<int, int> station[MAX_SIZE];
int n, k;

deque<int> q;

int main() {
	int i, idx = -1;
	ll prefix = 0, curr = 0, ans = 7e18;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		scanf("%d", &station[i].first);
		station[i].second = i;
	}
	scanf("%d", &k);
	sort(station + 1, station + 1 + n);
	
	for (i = 1; i <= n; ++i) {
		if (i == 1) {
			prefix += station[i].first;
			q.push_back(station[i].first);
		} else {
			curr += 1ll * station[i].first * (int) q.size() - prefix;
			prefix += station[i].first;
			q.push_back(station[i].first);
		}
		
		if (i > k) {
			prefix -= q.front();
			q.pop_front();
			curr -= prefix - 1ll * station[i-k].first * k;
		} 
		
		if (i >= k) {
			if (ans > curr) {
				idx = i;
				ans = curr;
			}
		}
		// cout << prefix << " " << curr << endl;
	}
	
	for (i = idx; i > idx - k; --i) {
		printf("%d ", station[i].second);
	}
	printf("\n");
	return 0;
}