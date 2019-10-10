#include <bits/stdc++.h>
#define MAX_SIZE 524292
typedef long long ll;
using namespace std;

struct wms {
	ll x;
	ll r;
	int id;
};

wms warms[MAX_SIZE >> 1];

vector<int> g1[MAX_SIZE];

unordered_set<int> g2[MAX_SIZE];

// the maximum left and right for each component 
vector<pair<int, int> > rmax = vector<pair<int, int> >(MAX_SIZE, make_pair(MAX_SIZE, -MAX_SIZE));
vector<pair<int, int> > pmax = vector<pair<int, int> >(MAX_SIZE, make_pair(MAX_SIZE, -MAX_SIZE));
// each vertex's componentid
// final answer would be rmax[cmpid[i]].second - rmax[cmpid[i]].first + 1 
int cmpid[MAX_SIZE];
int visited[MAX_SIZE];
int visited2[MAX_SIZE];
int low[MAX_SIZE];
int instack[MAX_SIZE];
stack<int> s;
int ans[MAX_SIZE];
// original vertex's map 0 as default
int vmap[MAX_SIZE];

int n;
int k = -1;
int cnt = 1;
int ord = 1;

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		k = max(k, index);
		vmap[l] = index;
		return;
	} 
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	g1[index].push_back(index * 2);
	g1[index].push_back(index * 2 + 1);
}

void update(int start, int end, int l, int r, int index, int v) {
	if (start > end || l > r || start > r || l > end) return;
	if (start <= l && r <= end) {
		g1[v].push_back(index);
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, index * 2, v);
	update(start, end, mid + 1, r, index * 2 + 1, v);
}

void tarjan(int v) {
	visited[v] = cnt;
	low[v] = cnt++;
	instack[v] = 1;
	s.push(v);
	for (auto nextv : g1[v]) {
		if (!visited[nextv]) {
			tarjan(nextv);
			low[v] = min(low[v], low[nextv]);
		} else if (instack[nextv] == 1) {
			low[v] = min(visited[nextv], low[v]);
		}
	}
	
	if (low[v] == visited[v]) {
		while (s.top() != v) {
			cmpid[s.top()] = ord;
			instack[s.top()] = 0;
			s.pop();
		}
		
		instack[s.top()] = 0;
		cmpid[s.top()] = ord;
		s.pop(); 
		ord++;
	}
}

void dfs(int v) {
	visited2[v] = 1;
	for (auto nextv : g2[v]) {
		if (!visited2[nextv]) {
			dfs(nextv);
		}
		pmax[v].first = min(pmax[v].first, pmax[nextv].first);
		pmax[v].second = max(pmax[v].second, pmax[nextv].second);
	}
}

static bool cmp(const wms &a, const wms &b) {
	return a.x < b.x;
}

int getlow(ll val) {
	int l = 1, r = n;
	int ret = n + 1;
	while (l <= r) {
		int mid = l + (r - l) / 2;
		if (warms[mid].x >= val) {
			ret = min(ret, mid);
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	
	return ret;
}

int gethigh(ll val) {
	int l = 1, r = n;
	int ret = 0;
	while (l <= r) {
		int mid = l + (r - l) / 2;
		if (warms[mid].x <= val) {
			ret = max(ret, mid);
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	
	return ret;
}

int main() {
	int i;
	
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		scanf("%lld%lld", &warms[i].x, &warms[i].r);
		warms[i].id = i;
	}
	
	sort(warms + 1, warms + 1 + n, cmp);
	
	build(1, n, 1);
	 
	for (i = 1; i <= n; i++) {
		rmax[vmap[i]].first = getlow(warms[i].x - warms[i].r);
		rmax[vmap[i]].second = gethigh(warms[i].x + warms[i].r);
		update(rmax[vmap[i]].first, rmax[vmap[i]].second, 1, n, 1, vmap[i]);
	}
	
	for (i = 1; i <= k; i++) {
		if (!visited[i]) {
			tarjan(i);
		}
	}
	
	for (i = 1; i <= k; i++) {
		pmax[cmpid[i]].first = min(rmax[i].first, pmax[cmpid[i]].first);
		pmax[cmpid[i]].second = max(rmax[i].second, pmax[cmpid[i]].second);
		//if (pmax[cmpid[i]].first == 0) cout << i << "!!!!!!!!" << endl;
		//cout << pmax[cmpid[i]].first << "------" <<  pmax[cmpid[i]].second << endl;
	}
	
	for (i = 1; i <= k; i++) {
		for (auto nextv : g1[i]) {
			 if (cmpid[i] != cmpid[nextv]) {
				g2[cmpid[i]].insert(cmpid[nextv]);
			 }
		}
	}
	
	for (i = 1; i < ord; i++) {
		if (!visited2[i]) {
			dfs(i);
		}
	}
	
	for (i = 1; i <= n; i++) {
		// cout << pmax[cmpid[vmap[i]]].second << " " <<  pmax[cmpid[vmap[i]]].first << endl;
		ans[warms[i].id] = pmax[cmpid[vmap[i]]].second - pmax[cmpid[vmap[i]]].first + 1;
	}
	
	for (i = 1; i <= n; i++) {
		printf("%d ", ans[i]);
	}
	printf("\n");
	return 0;
}
