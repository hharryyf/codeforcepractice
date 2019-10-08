#include <bits/stdc++.h>
#define MAX_SIZE 2011

using namespace std;

vector<int> g[MAX_SIZE];
int cmpord[MAX_SIZE];
int low[MAX_SIZE], dfsord[MAX_SIZE], instack[MAX_SIZE];
stack<int> st;
int k = 1;

void tarjan(int v) {
	dfsord[v] = k++;
	low[v] = dfsord[v];
	instack[v] = 1;
	st.push(v);
	for (auto nextv : g[v]) {
		if (!dfsord[nextv]) {
			tarjan(nextv);
			low[v] = min(low[nextv], low[v]);
		} else if (instack[nextv]) {
			low[v] = min(low[v], dfsord[nextv]);
		}
	}
	
	if (low[v] == dfsord[v]) {
		while (st.top() != v) {
			cmpord[st.top()] = v;
			instack[st.top()] = 0;
			st.pop();
		}
		
		instack[st.top()] = 0;
		cmpord[st.top()] = v;
		st.pop();
	}
}

int main() {
	int n, i, j;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			int v;
			scanf("%d", &v);
			if (v) {
				g[i].push_back(j);
			}
		}
	}
	
	for (i = 1; i <= n; i++) {
		if (!dfsord[i]) {
			tarjan(i);
		}
	}
	
	unordered_set<int> h;
	for (i = 1; i <= n; i++) {
		h.insert(cmpord[i]);
	}
	
	if ((int) h.size() != 1) cout << "NO" << endl;
	else cout << "YES" << endl;
	return 0;
}
