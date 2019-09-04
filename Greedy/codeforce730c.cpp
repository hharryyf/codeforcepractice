#include <bits/stdc++.h>
#define MAX_CITY 5011
#define MAX_TIME 10000000

using namespace std;

vector<int> graph[MAX_CITY];

typedef struct store {
	int city;
	long long price;
	long long quantity;
} Store;

int n;

vector<Store> stores;

vector<int> BFS(int src);

static bool cmp(const Store &a, const Store &b) {
	if (a.price != b.price) return a.price < b.price;
	return a.quantity < b.quantity;
}

bool valid(int time, vector<int> &dist, long long weight, long long maxmoney);

int main(int argc, char *argv[]) {
	int m, i;
	scanf("%d%d", &n, &m);
	for (i = 0; i < m; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
	}
	
	scanf("%d", &m);
	for (i = 0 ; i < m; i++) {
		int c;
		long long k, q;
		scanf("%d%lld%lld", &c, &k, &q);
		stores.push_back(Store{c, q, k});
	}
	
	sort(stores.begin(), stores.end(), cmp);
	
	scanf("%d", &m);
	while (m > 0) {
		long long tolquantity;
		int targetcity;
		long long maxmoney;
		scanf("%d%lld%lld", &targetcity, &tolquantity, &maxmoney);
		vector<int> dist = BFS(targetcity);
		// sort the cities according to the distance
		int low = 0, high = n + 1;
		int ans = MAX_TIME;
		while (low <= high) {
			// mid is the time attempted
			int mid = low + (high - low) / 2;
			if (valid(mid, dist, tolquantity, maxmoney)) {
				ans = min(ans, mid);
				high = mid - 1;
			} else {
				low = mid + 1;
			}
		}
		
		if (ans != MAX_TIME) {
			printf("%d\n", ans);
		} else {
			printf("-1\n");
		}
		m--;
	}
	return 0;
}

// the maximum time allowed and the distance array
bool valid(int time, vector<int> &dist, long long weight, long long maxmoney) {
	int i;
	for (i = 0 ; i < (int) stores.size(); i++) {
		if (dist[stores[i].city] != -1 && dist[stores[i].city] <= time) {
			if (weight <= stores[i].quantity) {
				maxmoney -= weight * stores[i].price;
				weight = 0;
			} else {
				weight = weight - stores[i].quantity;
				maxmoney -= stores[i].quantity * stores[i].price;
			}
			
			if (maxmoney < 0) return false;
		}
	}
	
	return (weight <= 0 && maxmoney >= 0);
}

// return vector<int>
// which ret[i] is the distance from i to src

vector<int> BFS(int src) {
	vector<int> ret = vector<int>(n + 1, -1);
	unordered_set<int> visited;
	queue<pair<int, int> > q;
	
	q.push(pair<int, int>(src, 0));
	visited.insert(src);
	ret[src] = 0;
	
	while (!q.empty()) {
		pair<int, int> curr = q.front();
		q.pop();
		for (auto next : graph[curr.first]) {
			if (visited.find(next) == visited.end()) {
				q.push(pair<int, int>(next, curr.second + 1));
				ret[next] = curr.second + 1;
				visited.insert(next);
			}
		}
	}
	
	return ret;
}
