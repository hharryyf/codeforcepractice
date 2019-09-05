#include <bits/stdc++.h>

typedef long long Long;

using namespace std;

vector<Long> pile;

bool valid(Long t, int m);

int main(int argc, char *argv[]) {
	int n, m, i;
	Long tol = 0ll;
	scanf("%d%d", &n, &m);
	pile.push_back(0);
	for (i = 0 ; i < n; i++) {
		Long v;
		scanf("%lld", &v);
		pile.push_back(v);
		tol += v;
	}
	
	Long low = 0ll, high = tol + n;
	Long ans = tol + (Long) n + 1;
	while (low <= high) {
		Long mid = low + ((high - low) >> 1);
		if (valid(mid, m)) {
			ans = min(ans, mid);
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}
	
	printf("%lld\n", ans);
	
	return 0;
}

// return whether it is possible to use m students to remove all in t seconds
bool valid(Long t, int m) {
	vector<Long> arr = pile;
	int i = (int) pile.size() - 1;
	Long currrem = t;
	while (i > 0) {
		if (arr[i] != 0) {
			if (m <= 0) return false;
			if (currrem == t) {
				if (t < (Long) i) return false;
				currrem = currrem - i;
			} else {
				if (currrem < arr[i]) {
					arr[i] = arr[i] - currrem;
					currrem = t;
					m--;
				} else {
					currrem -= arr[i];
					arr[i] = 0;
				}
			}
		} else {
			i--;
		}
	}
	
	return true;
}
