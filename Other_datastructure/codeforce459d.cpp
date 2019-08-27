#include <bits/stdc++.h>
#define MAX_LEN 1048592

typedef long long Long;
using namespace std;

// the binary indexed tree that counts the total number of unique elements 
//that has occured k times
Long tree[MAX_LEN];

unordered_map<int, int> hashing, sliding;

int n, value[MAX_LEN];

void update(int pos, Long delta);

Long query(int pos);

int main(int argc, char *argv[]) {
	cin >> n;
	int i;
	Long ans = 0;
	for (i = 0 ; i < n; i++) {
		cin >> value[i];
	}
	
	for (i = n - 1; i >= 0; i--) {
		hashing[value[i]]++;
		update(hashing[value[i]], 1);	
	}
	
	for (i = 0 ; i < n; i++) {
		sliding[value[i]]++;
		update(hashing[value[i]], -1);
		hashing[value[i]]--;
		ans += query(sliding[value[i]] - 1);
	}
	cout << ans << endl;
	return 0;
}

int shift(int pos) {
	return pos & (-pos);
}

void update(int pos, Long delta) {
	if (pos <= 0) return;
	while (pos <= n) {
		tree[pos] += delta;
		pos += shift(pos);
	}
}

Long query(int pos) {
	Long res = 0;
	while (pos > 0) {
		res += tree[pos];
		pos = pos - shift(pos);
	}
	return res;
}
