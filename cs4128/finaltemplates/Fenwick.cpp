#include <bits/stdc++.h>
#define MAX_SIZE 262192

typedef long long ll;

using namespace std;

ll tree[MAX_SIZE];
int n;

int shift(int x) {
	return x & (-x);
}

ll getans(ll t[], int index) {
	ll ret = 0;
	while (index > 0) {
		ret = ret + t[index];
		index = index - shift(index);
	}
	
	return ret;
}

ll query(ll t[], int start, int end) {
	if (start > end) return 0;
	return getans(t, end) - getans(t, start - 1);
}

void update(ll t[], int index, ll val) {
	while (index <= n) {
		t[index] += val;
		index = index + shift(index);
	}
}
