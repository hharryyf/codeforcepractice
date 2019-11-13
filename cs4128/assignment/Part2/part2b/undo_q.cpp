#include <bits/stdc++.h>
#define MAX_SIZE 262192

using namespace std;

struct edge {
	int v1, v2;
	int start, end;
};

edge queries[MAX_SIZE >> 1];

vector<pair<int, int> > tree[MAX_SIZE];
stack<int> f[MAX_SIZE >> 1];
stack<int> subsz[MAX_SIZE >> 1];
stack<pair<int, int> > conn;

int n, q;
int ans[MAX_SIZE >> 1];
pair<int, int> qr[MAX_SIZE >> 1];

int find(int x) {
	if (f[x].top() == x) {
		return x;
	}	
	
	return find(f[x].top());
}

void unionset(int a, int b) {
	int x = find(a), y = find(b);
	if (subsz[x].top() < subsz[y].top()) {
		if (x != y) {
			subsz[y].push(subsz[x].top() + subsz[y].top());
			subsz[y].push(subsz[y].top());
		}
		f[x].push(y);	
		// x has a parent of y
		conn.push(make_pair(x, y));
	} else {
		if (x != y) {
			subsz[x].push(subsz[x].top() + subsz[y].top());
		} else {
			subsz[x].push(subsz[x].top());
		}
		// y has a parent of x
		f[y].push(x);
		
		conn.push(make_pair(y, x));
	}
}

void disconnect() {
	if (!conn.empty()) {
		auto p = conn.top();
		conn.pop();
		f[p.first].pop();
		subsz[p.second].pop();
	}
}

void preprocess() {
	int i;
	for (i = 1; i <= n; i++) {
		f[i].push(i);
		subsz[i].push(1);
	}
}

void dfs(int l, int r, int index) {
	// cout << index << endl;
	if (l > r) return;
	int cnt = 0;
	for (auto p : tree[index]) {
		unionset(p.first, p.second);
		cnt++;
	}
	
	if (l == r) {
		if (qr[l].first > 0 && qr[l].second > 0) {
			ans[l] = (find(qr[l].first) == find(qr[l].second));
		}
		
		while (cnt > 0) {
			disconnect();
			cnt--;
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	dfs(l, mid, index * 2);
	dfs(mid + 1, r, index * 2 + 1);
	while (cnt > 0) {
		disconnect();
		cnt--;
	}
}

void insert(int start, int end, int l, int r, int index, pair<int, int> p) {
	if (start > end || l > r || start > r || l > end) {
		return;
	}
	
	if (start <= l && r <= end) {
		tree[index].push_back(p);
		return;
	}
	
	int mid = l + (r - l) / 2;
	insert(start, end, l, mid, index * 2, p);
	insert(start, end, mid + 1, r, index * 2 + 1, p);
}

char op[4];

int main() {
	scanf("%d%d", &n, &q);
	preprocess();
	int i;
	for (i = 1; i <= q; i++) {
		int v1, v2;
		scanf("%s", op);
		if (op[0] == 'A') {
			scanf("%d%d", &v1, &v2);
			queries[i] = edge{v1, v2, i, q};
		} else if (op[0] == 'D') {
			int qq;
			scanf("%d", &qq);
			queries[qq].end = i;
		} else {
			scanf("%d%d", &v1, &v2);
			qr[i] = make_pair(v1, v2);
		}
	}
	
	for (i = 1; i <= q; i++) {
		if (queries[i].v1 != 0) {
			insert(queries[i].start, queries[i].end, 1, q, 1, make_pair(queries[i].v1, queries[i].v2));
		}
	}
	
	// cout << "ehllo" << endl;
	dfs(1, q, 1);
	
	for (i = 1; i <= q; i++) {
		if (qr[i].first) {
			printf("%d\n", ans[i]);
		}
	}
	return 0;
}
