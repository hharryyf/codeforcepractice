#include <bits/stdc++.h>
#define MAX_SIZE 100011

using namespace std;

stack<int> f[MAX_SIZE];
stack<int> subsz[MAX_SIZE];

stack<pair<int, int> > conn;


int n;

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

char op[4];

int main() {
	scanf("%d", &n);
	int q, i;
	scanf("%d", &q);
	preprocess();
	for (i = 0 ; i < q; i++) {
		scanf("%s", op);
		if (op[0] == 'A') {
			int a, b;
			scanf("%d%d", &a, &b);
			unionset(a, b);
		} else if (op[0] == 'D') {
			disconnect();
		} else {
			int a, b;
			scanf("%d%d", &a, &b);
			printf("%d\n", find(a) == find(b));
		}
	}
	return 0;
}
