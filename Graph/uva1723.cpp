#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 50011
#define INF 10000000
using namespace std;

vector<pair<int, int>> g[MAX_SIZE];
int dist[MAX_SIZE];
bool visited[MAX_SIZE];
int relax[MAX_SIZE];
int n;
int m;

void init() {
    int i;
    for (i = 0 ; i < MAX_SIZE; i++) {
        g[i].clear();    
    }
}

void SPFA(int ma) {
    int i;
    for (i = 0; i < MAX_SIZE; i++) {
        dist[i] = -INF;
    }
    
    memset(visited, false, sizeof(visited));
    memset(relax, 0, sizeof(relax));
	queue<int> q;
	dist[0] = 0;
	visited[0] = true;
	relax[0] = 1;
	q.push(0);
	while (!q.empty()) {
		auto pr = q.front();
		q.pop();
		visited[pr] = false;
		if (relax[pr] > MAX_SIZE) {
		    printf("wrong answer!\n");
		    return;
		}
		for (auto nextp : g[pr]) {
			if (nextp.second + dist[pr] > dist[nextp.first]) {
				dist[nextp.first] = nextp.second + dist[pr];
				if (!visited[nextp.first]) {
					visited[nextp.first] = true;
					q.push(nextp.first);
					relax[nextp.first]++;
				}
			}
		}
	}	
	
	printf("%d\n", dist[ma+4]);
}

int high = 0;

void addedge(int a, int b, int c) {
    g[a + 4].emplace_back(b + 4, c);
}

int main() {
    int T, i;
    scanf("%d", &T);
    while (T > 0) {
        init();
        unordered_set<int> h;
        scanf("%d", &n);
        for (i = 0; i < n; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            high = max(high, a-1);
            high = max(high, b);
            addedge(a-1, b, c);
        }
        
        for (i = -3; i <= high; i++) {
            addedge(i, i-1, -1);
            addedge(i-1, i, 0);
        }
        SPFA(high);
        T--;
        if (T > 0) {
            printf("\n");
        }
    }
    return 0;
}
