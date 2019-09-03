#include <bits/stdc++.h>
#define MAX_SIZE 262192

typedef long long Long;

using namespace std;

typedef struct oil {
	int x;
	Long money;
} Oil;

static bool cmp(const Oil &a, const Oil &b) {
	if (a.x != b.x) return a.x < b.x;
	return a.money < b.money;
}

struct qcmp {
	bool operator()(const Oil &a, const Oil &b) {
		if (a.money != b.money) return a.money > b.money;
		return a.x > b.x;
	}
};

vector<Oil> arr;

int max_index(vector<Oil> &arr, int V, int pos);

priority_queue<Oil, vector<Oil>, qcmp> q = priority_queue<Oil, vector<Oil>, qcmp>();

int main(int argc, char *argv[]) {
	int d, n, m, i;
	Oil ol;
	scanf("%d%d%d", &d, &n, &m);
	arr.push_back(Oil{0,0});
	for (i = 0 ; i < m; i++) {
		scanf("%d%lld", &ol.x, &ol.money);
		arr.push_back(ol);
	}	
	
	ol = {d, 0ll};
	arr.push_back(ol);
	sort(arr.begin(), arr.end(), cmp);
	
	ol = {0, 0};
	
	q.push(ol);
	Long ans = 0;
	
	for (i = 0 ; i < (int) arr.size() - 1; i++) {
		int curr = arr[i].x;
		int dist = arr[i+1].x - arr[i].x;
		if (dist > n) {
			cout << -1 << endl;
			return 0;
		}
		
		while (dist > 0) {
			while (!q.empty() && (q.top().x + n <= curr)) {
				q.pop();
			}
			
			ol = q.top();
			int d = min(dist, n - (curr - ol.x));
			dist = dist - d;
			ans += (Long) d * ol.money;
			curr += d;
			// cout << "dist " << dist << endl;
		}
		q.push(arr[i+1]);
		// cout << i << endl;
	}
	
	cout << ans << endl;
	return 0;
}
