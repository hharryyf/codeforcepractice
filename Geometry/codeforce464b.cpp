#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct point {
	ll x[3];
};

bool ok = false;
int g[6][3] = {{0, 1, 2}, 
               {0, 2, 1}, 
			   {1, 0, 2}, 
			   {1, 2, 0}, 
			   {2, 0, 1}, 
			   {2, 1, 0}};
point pt[8];
point tmp[8];
int visited[8], ans[8][3];

ll dist(point p1, point p2) {
	ll ret = 0;
	int i;
	for (i = 0 ; i < 3; ++i) {
		ret += (p1.x[i] - p2.x[i]) * (p1.x[i] - p2.x[i]);
	}
	return ret;
}

bool check() {
	int i, j;
	map<ll, int> cnt;
	for (i = 0 ; i < 8; ++i) {
		for (j = i + 1; j < 8; ++j) {
			cnt[dist(tmp[i], tmp[j])]++;
		}
	}
	
	if ((int) cnt.size() != 3) return false; 
	ll v[3];
	int c[3];
	i = 0;
	auto iter = cnt.begin();
	while (iter != cnt.end()) {
		v[i] = iter->first;
		c[i] = iter->second;
		iter++;
		i++;
	}
	
	return v[0] * 2 == v[1] && v[0] * 3 == v[2] && c[0] == 12 && c[1] == 12;
}

void dfs(int v) {
	int i, j;
	if (v > 7 || ok) return;
	if (v >= 7) {
		if (check()) {
			for (i = 0 ; i < 8; ++i) {
				for (j = 0 ; j < 3; ++j) {
					ans[i][j] = tmp[i].x[j];
				}
			}
			ok = true;
			return;
		}
	}
	
	for (i = 0 ; i < 6; ++i) {
		for (j = 0 ; j < 3; ++j) {
			tmp[v].x[j] = pt[v].x[g[i][j]];
		}
		dfs(v + 1);
	}
}

int main() {
	int i, j;
	for (i = 0 ; i < 8; ++i) {
		scanf("%I64d%I64d%I64d", &pt[i].x[0], &pt[i].x[1], &pt[i].x[2]);
	}
	
	for (i = 0; i < 3; ++i) {
		ans[7][i] = tmp[7].x[i] = pt[7].x[i];
	}
	
	dfs(0);
	
	if (!ok) {
		printf("NO\n");
	} else {
		printf("YES\n");
		for (i = 0 ; i < 8; ++i) {
			for (j = 0 ; j < 3; ++j) {
				printf("%d ", ans[i][j]);
			}
			printf("\n");
		}
	}
	return 0;
}