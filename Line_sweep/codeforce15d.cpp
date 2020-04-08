#include <bits/stdc++.h>
#define MAX_SIZE 1011
typedef long long ll;
using namespace std;

ll rsum[MAX_SIZE][MAX_SIZE];
int rmin[MAX_SIZE][MAX_SIZE];
int tmp[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];
int city[MAX_SIZE][MAX_SIZE];
struct candidate {
	int x, y;
	ll val;
	bool operator < (candidate other) const {
		if (val != other.val) return val < other.val;
		if (x != other.x) return x < other.x;
		return y < other.y;
	}
};

candidate can[MAX_SIZE * MAX_SIZE];
int n, m, a, b;

int main() {
	int i, j, k;
	scanf("%d%d%d%d", &n, &m, &a, &b);
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= m; ++j) {
			scanf("%d", &city[i][j]);
			rsum[i][j] = rsum[i][j] + city[i][j] + rsum[i-1][j] + rsum[i][j-1] - rsum[i-1][j-1];
		}
	}
	
	for (i = 1; i <= n; ++i) {
		deque<int> q;
		for (j = 1; j <= m; ++j) {
			while (!q.empty() && q.front() <= j - b) q.pop_front();
			while (!q.empty() && city[i][q.back()] >= city[i][j]) q.pop_back();
			q.push_back(j);
			tmp[i][j] = city[i][q.front()];
			// cout << i << " " << j << " row " << tmp[i][j] << endl;
		}
	}
	
	for (j = 1; j <= m; ++j) {
		deque<int> q;
		for (i = 1; i <= n; ++i) {
			while (!q.empty() && q.front() <= i - a) q.pop_front();
			while (!q.empty() && tmp[q.back()][j] >= tmp[i][j]) q.pop_back();
			q.push_back(i);
			rmin[i][j] = tmp[q.front()][j];
		}
	}
	
	int cnt = 0;
	for (i = a; i <= n; ++i) {
		for (j = b; j <= m; ++j) {
			can[cnt].x = i, can[cnt].y = j;
			can[cnt].val = rsum[i][j] - rsum[i][j-b] -rsum[i-a][j] 
			             + rsum[i-a][j-b] - 1ll * a * b * rmin[i][j];
			// cout << i << " " << j << ": " << rmin[i][j] << " " << can[cnt].val << endl;
			cnt++;
		}
	}
	
	sort(can, can + cnt);
	
	vector<candidate> ret;
	for (i = 0; i < cnt; ++i) {
		if (visited[can[i].x][can[i].y]) continue;
		ret.push_back(can[i]);
		for (j = min(can[i].x + a - 1, n); j > can[i].x - a; --j) {
			for (k = min(can[i].y + b - 1, m); k > can[i].y - b; --k) {
				visited[j][k] = true;
				// cout << "visited " << j << " " << k << endl;
			}
		}
	}
	
	printf("%d\n", (int) ret.size());
	for (auto v : ret) {
		printf("%d %d %I64d\n", v.x - a + 1, v.y - b + 1, v.val);
	}
	return 0;
}