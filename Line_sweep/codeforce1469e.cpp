#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;

int prefix[MAX_SIZE];
char st[MAX_SIZE], pt[MAX_SIZE];

int main() {
	int T;
	scanf("%d", &T);
	while (T-- > 0) {
		int N, K, up = 20, i, j;
		scanf("%d%d", &N, &K);
		up = min(up, K);
		scanf("%s", st + 1);
		for (i = 1; i <= N; ++i) {
			if (st[i] == '0') {
				pt[i] = '1';
			} else {
				pt[i] = '0';
			}
		}		

		for (i = 1; i <= N; ++i) {
			prefix[i] = prefix[i-1] + st[i] - '0';
		}

		vector<int> bad;
		for (i = 1; i <= N - K + 1; ++i) {
			if (prefix[i + K - up - 1] - prefix[i-1] == K - up) {
				int curr = 0;
				for (j = i + K - up; j <= i + K - 1; ++j) {
					curr = curr * 2 + (pt[j] - '0');
				}
				bad.push_back(curr);
			}
		}

		sort(bad.begin(), bad.end());
		vector<int>::iterator it;
  		it = unique (bad.begin(), bad.end()); 
		bad.resize(distance(bad.begin(),it));
		int ans = 0;
		for (auto v : bad) {
			if (ans != v) break;
			ans = v + 1;
		}

		if (ans >= (1 << up)) {
			printf("NO\n");
		}  else {
			printf("YES\n");
			for (i = 1; i <= K - up; ++i) {
				printf("0");
			}

			for (i = up - 1; i >= 0; --i) {
				if (ans & (1 << i)) {
					printf("1");
				} else {
					printf("0");
				}
			}
			printf("\n");
		}
	}
	return 0;
}