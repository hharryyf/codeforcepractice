#include <bits/stdc++.h>
#define MAX_SIZE 3011
using namespace std;

struct candidate {
	int id, v;
	bool operator < (candidate other) const {
		return v > other.v;
	}
};

int table[MAX_SIZE][13];
int pos[MAX_SIZE][13];
candidate val[MAX_SIZE];
int logs[MAX_SIZE];
int n;


void build() {
	int i, j;
	for (i = 2; i < MAX_SIZE; ++i) logs[i] = logs[i/2] + 1;
	
	sort(val + 1, val + 1 + n);
	// val[n+1].v = val[n].v;
	for (i = 1; i <= n; ++i) {
		table[i][0] = -val[i+1].v + val[i].v;
		pos[i][0] = i;
	}
	
	for (j = 1; j < 13; ++j) {
		int prel = (1 << (j - 1));
		for (i = 1; i <= n; ++i) {
			if (i + prel <= n) {
				table[i][j] = max(table[i][j-1], table[i+prel][j-1]);
				if (table[i][j-1] >= table[i+prel][j-1]) {
					pos[i][j] = pos[i][j-1];
				} else {
					pos[i][j] = pos[i+prel][j-1];
				}
			} else {
				table[i][j] = table[i][j-1];
				pos[i][j] = pos[i][j-1];
			}
		}
	}
}

int rmq(int l, int r) {
	int len = r - l + 1;
    if (table[l][logs[len]] >= table[r - (1 << logs[len]) + 1][logs[len]]) {
		return pos[l][logs[len]];
	} 
	
	return pos[r - (1 << logs[len]) + 1][logs[len]];
}

// return the range that can be made by the class 3
pair<int, int> getrange(int c1, int c2) {
	int l = 1, r = n - c1 - c2;
	r = min(r, 2 * c1);
	r = min(r, 2 * c2);
	l = max(l, (c2 + 1) / 2);
	l = max(l, (c1 + 1) / 2);
	return make_pair(l, r);
}

int ans[MAX_SIZE];

int main() {
	int i, j;
	int opt1 = -1, opt2 = -1, opt3 = -1;
	int c1 = 0, c2 = 0, c3 = 0;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		scanf("%d", &val[i].v);
		val[i].id = i;
	}
	
	build();
	/*
	for (i = 1; i <= n; ++i) cout << val[i].v << " ";
	cout << endl;
	*/
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= n - i; ++j) {
			if (i <= 2 * j && j <= 2 * i && i + j < n) {
				// remaining is maximum k
				auto p = getrange(i, j);
				if (p.first <= p.second) {
					int k1 = rmq(i + j + p.first, i + j + p.second);
					// cout << "rmq " << i + j + p.first << " " << i + j + p.second << endl;
					// cout << k1 << endl;
					if (opt1 < val[i].v - val[i+1].v || (opt2 < val[i+j].v - val[i+j+1].v && opt1 == val[i].v - val[i+1].v) || 
					(opt3 <= val[k1].v - val[k1+1].v && opt2 == val[i+j].v - val[i+j+1].v && opt1 == val[i].v - val[i+1].v)) {
						c1 = i, c2 = j, c3 = k1 - i - j;
						opt1 = val[i].v - val[i+1].v;
						opt2 = val[i+j].v - val[i+j+1].v;
						opt3 = val[k1].v - val[k1+1].v;
					}
				}
			}
		}
	}
	
	for (i = 1; i <= c1; ++i) {
		ans[val[i].id] = 1;
	}
	
	for (i = c1 + 1; i <= c1 + c2; ++i) {
		ans[val[i].id] = 2;
	}
	
	for (i = c2 + c1 + 1; i <= c2 + c1 + c3; ++i) {
		ans[val[i].id] = 3;
	}
	
	for (i = c1 + c2 + c3 + 1; i <= n; ++i) {
		ans[val[i].id] = -1;
	}
	
	for (i = 1; i <= n; ++i) printf("%d ", ans[i]);
	printf("\n");
	return 0;
}