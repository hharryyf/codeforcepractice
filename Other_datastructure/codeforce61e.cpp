#include <iostream>
#include <unordered_map>
#include <cstdio>
#include <algorithm>
#define MAX_SIZE 1048591

using namespace std;

// the larger value that occurs before the current value
long long large[MAX_SIZE];
// the smaller value that occurs after the current value
long long small[MAX_SIZE];
// number of elements
long long n;
// the original arr and a duplicate one for sorting
long long arr[MAX_SIZE], d[MAX_SIZE];

int shift(int x);
void update(long long arr[], int pos, int delta);
long long query(long long arr[], int start, int end);
long long queryUtil(long long array[], int upto);
long long ans;

int main(int argc, char *argv[]) {
	unordered_map<int, int> place = unordered_map<int, int>();
	cin >> n;
	int i;
	ans = 0;
	for (i = 1; i <= n; i++) {
		cin >> arr[i];
		d[i] = arr[i];
	}
	
	sort(d + 1, d + 1 + n);
	for (i = 1; i <= n; i++) {
		place[d[i]] = i;
		update(small, i, 1);
	}
	
	for (i = 1; i <= n; i++) {
		int ranking = place[arr[i]];
		ans += query(large, ranking + 1, n) * query(small, 1, ranking - 1);
		update(small, ranking, -1);
		update(large, ranking, 1);
	}
	
	cout << ans << endl;
	return 0;
}

int shift(int x) {
	return x & (-x);
}

void update(long long array[], int pos, int delta) {
	while (pos <= 1048576) {
		array[pos] += delta;
		pos += shift(pos);
	}
}

long long query(long long array[], int start, int end) {
	if (start > end) return 0;
	return queryUtil(array, end) - queryUtil(array, start - 1);
}

long long queryUtil(long long array[], int upto) {
	long long t = 0;
	while (upto > 0) {
		t += array[upto];
		upto -= shift(upto);
	}
	
	return t;
}

