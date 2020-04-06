#include <bits/stdc++.h>
using namespace std;

unordered_map<int, int> mp;
int h;

int left(int index) {
	return index << 1;
}

int right(int index) {
	return index << 1 | 1;
}

int parent(int index) {
	return index >> 1;
}

void add(int v, int index) {
	while (index > 0) {
		mp[index] += v;
		index = parent(index);
	}
}

int numleaf(int dep) {
	return 1 << (h - dep);
}

double query(int dep, int index, int mx) {
	int val = mp[index];
	if (dep == h) return max(1.0 * mx, 1.0 * val);
	// cout << mx << " " << dep << " " << index << endl;
	if (mx >= mp[index]) return 1.0 * mx * numleaf(dep);
	int l = mp[left(index)], r = mp[right(index)];
	return query(dep + 1, left(index), max(mx, val - l)) 
	     + query(dep + 1, right(index), max(mx, val - r));
}

char st[7];

int main() {
	int q;
	scanf("%d%d", &h, &q);
	int len = 1 << h;
	
	while (q > 0) {
		scanf("%s", st);
		if (st[0] == 'a') {
			int v, val;
			scanf("%d%d", &v, &val);
			add(val, v);
		} else {
			printf("%.8lf\n", query(0, 1, 0) / (1.0 * len));
		}
		q--;
	}
	return 0;
}

/*
3 6
add 2 101
add 6 830
add 11 899
add 2 421
decay
decay
*/