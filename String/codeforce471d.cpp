#include <bits/stdc++.h>
#define MAX_SIZE 524292
using namespace std;
int n, w;
int a[MAX_SIZE >> 1], b[MAX_SIZE >> 1];
vector<int> s;
int nxt[MAX_SIZE];

int cal_next() {
	int ret = 0, sz = (int) s.size();
	int i, j;
	for (i = 1; i < sz; ++i) {
		j = nxt[i-1];
		while (j > 0 && s[i] != s[j]) {
			j = nxt[j-1];
		}
		
		if (s[i] == s[j]) j++;
		nxt[i] = j;
		// increment the counter since there's a match
		if (nxt[i] == w - 1) ret++;
	}
	
	return ret;
}

int main() {
	int i;
	scanf("%d%d", &n, &w);
	for (i = 0 ; i < n; ++i) scanf("%d", &a[i]);
	for (i = 0 ; i < w; ++i) scanf("%d", &b[i]);
	
	if (n < w) {
		printf("0\n");
		return 0;
	}
	
	if (n == 1) {
		printf("1\n");
		return 0;
	}
	
	if (w == 1) {
		printf("%d\n", n);
		return 0;
	}
	
	for (i = 1; i < w; ++i) {
		s.push_back(b[i] - b[i-1]);
	}
	s.push_back(2000000011);
	for (i = 1; i < n; ++i) {
		s.push_back(a[i] - a[i-1]);
	}
	
	int ret = cal_next();
	
	printf("%d\n", ret);
	return 0;
}