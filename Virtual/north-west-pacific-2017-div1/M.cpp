#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 4011
typedef long long ll;

vector<int> g[MAX_SIZE];
vector<int> h[MAX_SIZE];
int cmpid[MAX_SIZE], low[MAX_SIZE], visited[MAX_SIZE], instack[MAX_SIZE];
stack<int> st;
int N, M, cnt = 0;

void tarjan(int v) {
    st.push(v);
    instack[v] = 1;
    visited[v] = low[v] = ++cnt;
    for (auto nv : g[v]) {
        if (!visited[nv]) {
            tarjan(nv);
            low[v] = min(low[v], low[nv]);
        } else if (instack[nv]) {
            low[v] = min(low[v], visited[nv]);
        }
    }

    if (low[v] == visited[v]) {
        while (st.top() != v) {
            instack[st.top()] = 0;
            cmpid[st.top()] = v;
            st.pop();
        }

        cmpid[st.top()] = v;
        instack[st.top()] = 0;
        st.pop();

    }
}

int pos(int x) {
	return x * 2 - 1;
}

int neg(int x) {
	return x * 2;
}

void dfs(int v) {
	visited[v] = 1;
	for (auto nv : g[v]) {
		if (!visited[nv]) {
			dfs(nv);
		}
	}
}

void dfs2(int v) {
	visited[v] = 1;
	for (auto nv : h[v]) {
		if (!visited[nv]) {
			dfs2(nv);
		}
	}
}

int main() {
	int i, j;
	scanf("%d%d", &N, &M);
	for (i = 0 ; i < M; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		if (u > 0 && v > 0) {
			g[neg(u)].push_back(pos(v));
			g[neg(v)].push_back(pos(u));
		} else if (u > 0 && v < 0) {
			// u or neg v
			v = -v;
			g[neg(u)].push_back(neg(v));
			g[pos(v)].push_back(pos(u));
		} else if (u < 0 && v < 0) {
			// neg u or neg v
			u = -u, v = -v;
			g[pos(u)].push_back(neg(v));
			g[pos(v)].push_back(neg(u));
		} else if (u < 0 && v > 0) {
			u = -u;
			g[pos(u)].push_back(pos(v));
			g[neg(v)].push_back(neg(u));
		}
	}

	for (i = 1; i <= 2 * N; ++i) {
		for (auto v : g[i]) {
			h[v].push_back(i);
		}
	}

	for (i = 1; i <= 2 * N; ++i) {
		if (!visited[i]) {
			tarjan(i);
		}
	}

	for (i = 1; i <= N; ++i) {
		if (cmpid[pos(i)] == cmpid[neg(i)]) {
			printf("0\n");
			return 0;
		}
	}

	for (i = 1; i <= N; ++i) {
		for (j = 1; j <= 2 * N; ++j) {
			visited[j] = 0;
		}
		dfs(pos(i));
		if (visited[neg(i)]) {
			printf("1\n");
			return 0;
		}
	}

	for (i = 1; i <= N; ++i) {
		int ok = 0;
		for (j = 1; j <= 2 * N; ++j) {
			visited[j] = 0;
		}

		dfs2(neg(i));

		for (j = 1; j <= N; ++j) {
			if (visited[pos(j)]) {
				ok++;
				break;
			}
		}

		for (j = 1; j <= 2 * N; ++j) {
			visited[j] = 0;
		}
		
		dfs(pos(i));

		for (j = 1; j <= N; ++j) {
			if (visited[neg(j)]) {
				ok++;
				break;
			}
		}

		if (ok == 2) {
			printf("2\n");
			return 0;
		}
	}

	printf("-1\n");
	return 0;
}