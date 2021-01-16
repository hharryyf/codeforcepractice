#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 2011
using namespace std;

struct line {
    ll m, b;
    int id;
};
	
double intersect ( line a, line b) {
    return 1.0 * (b.b - a.b) /  (a.m - b.m);
}

struct Convex {
	vector<line> cht;
	void insert(line l) {
		auto n = cht.size();
		while ((n >= 1 &&  l.m == cht[n-1].m && l.b <= cht[n-1].b) 
		|| (n >= 2 && intersect(cht[n-1], cht[n-2]) > intersect(cht[n-1], l)) ||
        (n == 1 && intersect(cht[n-1], l) < 0)) {
			cht.pop_back();
			n = cht.size();
		}
		cht.push_back(l);
	}
};

Convex cht;
int ok[MAX_SIZE], visited[MAX_SIZE][MAX_SIZE], N;
const ll inf = 1e16;
ll dp[MAX_SIZE][MAX_SIZE];
vector<pair<int, ll>> g[MAX_SIZE];

void dfs(int v, int step) {
    ok[v] = 1;
    if (step <= 0 || visited[v][step]) return; 
    visited[v][step] = 1;
    for (auto np : g[v]) {
        int nv = np.first;
        ll w = np.second;
        if (dp[step - 1][nv] + w == dp[step][v]) dfs(nv, step - 1);
    }
}

int main() {
    int M, i, j;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= M; ++i) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        g[u].emplace_back(v, c);
        g[v].emplace_back(u, c);
    }

    for (i = 0; i <= N; ++i) {
        for (j = 0 ; j <= N; ++j) {
            dp[i][j] = inf;
        }
    }

    dp[0][1] = 0;
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            for (auto np : g[j]) {
                int nv = np.first;
                ll w = np.second;
                dp[i][nv] = min(dp[i-1][j] + w, dp[i][nv]);
            }
        }
    } 

    for (i = N; i >= 1; --i) {
        if (dp[i][N] >= inf) continue;
        cht.insert(line{i, dp[i][N], i});
        // cout << i << " " << dp[i][N] << endl;
    }

    vector<int> candidate;
    while (!cht.cht.empty()) {
        candidate.push_back(cht.cht.back().id);
        // printf("ok %d\n", candidate.back());
        cht.cht.pop_back();
    }

    for (auto v : candidate) {
        dfs(N, v);
    }

    candidate.clear();
    
    for (i = 1; i <= N; ++i) {
        if (ok[i] == 0) candidate.push_back(i);
    }

    printf("%d\n", (int) candidate.size());
    for (auto v : candidate) {
        printf("%d ", v);
    }
    printf("\n");
    return 0;
}