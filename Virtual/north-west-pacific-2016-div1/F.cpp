#include <bits/stdc++.h>
#define MAX_SIZE 2011
typedef long long ll;
#define INF 100000000000
using namespace std;
vector<int> g[MAX_SIZE];
int N, L, R;
int x[MAX_SIZE], y[MAX_SIZE];
int cmpid[MAX_SIZE], low[MAX_SIZE], visited[MAX_SIZE], instack[MAX_SIZE];
stack<int> st;
int cnt = 0;

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


int pos(int v) {
	return v * 2;
}

int neg(int v) {
	return v * 2 - 1;
}



int main() {
	int i, j;
	scanf("%d%d%d", &N, &R, &L);
	for (i = 1; i <= L; ++i) {
		scanf("%d%d", &x[i], &y[i]);
	}	
	// positive term * 2, negative term * 2 - 1
	for (i = 1; i <= L; ++i) {
		for (j = i + 1; j <= L; ++j) {
			if (x[i] == x[j]) {
				int l1 = max(y[i] - R, 1), r1 = min(y[i] + R, N);
				int l2 = max(y[j] - R, 1), r2 = min(y[j] + R, N);
				int itc = max(min(r2, r1) - max(l1, l2) + 1, 0);
				if (itc > 0) {
					g[pos(i)].push_back(neg(j));
					g[pos(j)].push_back(neg(i));
				}
			}

			if (y[i] == y[j]) {
				int l1 = max(x[i] - R, 1), r1 = min(x[i] + R, N);
				int l2 = max(x[j] - R, 1), r2 = min(x[j] + R, N);
				int itc = max(min(r2, r1) - max(l1, l2) + 1, 0);
				if (itc > 0) {
					g[neg(i)].push_back(pos(j));
					g[neg(j)].push_back(pos(i));
				}
			}
		}
	}

	for (i = 1; i <= 2 * L; ++i) {
		if (!visited[i]) {
			tarjan(i);
		}
	}

	for (i = 1; i <= L; ++i) {
		if (cmpid[pos(i)] == cmpid[neg(i)]) {
			printf("NO\n");
			return 0;
		}
	}

	printf("YES\n");
	return 0;
}
