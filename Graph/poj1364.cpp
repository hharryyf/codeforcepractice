#include <cstring>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#define MAX_SIZE 111
#define INF 2000000000
typedef long long ll;
using namespace std;

ll dist[MAX_SIZE];
vector<int> g[MAX_SIZE];
struct edge {
    int from, to;
    ll wt;
};

vector<edge> edg;
int n, m;

void init() {
    edg.clear();
    int i;
    for (i = 0 ; i < MAX_SIZE; i++) {
        g[i].clear();
    }
}

bool bellmanford() {
    int i, j;
    for (i = 0 ; i < MAX_SIZE; i++) {
        dist[i] = INF;
    }
    
    dist[0] = 0;
    
    for (i = 0 ; i <= n + 1; i++) {
        for (j = 0 ; j < (int) edg.size(); j++) {
            dist[edg[j].to] = min(dist[edg[j].to], dist[edg[j].from] + edg[j].wt);
        }
    }
    
    for (j = 0 ; j < (int) edg.size(); j++) {
        if (dist[edg[j].to] > dist[edg[j].from] + edg[j].wt) return false;
    }
    return true;
}

char st[4];

void addedge(int a, int b, ll w) {
    edge e;
    e.from = a + 1, e.to = b + 1, e.wt = w;
    edg.push_back(e);
}

int main() {
    while (scanf("%d", &n) != EOF) {
        if (n == 0) break;
        init();
        scanf("%d", &m);
        int i;
        for (i = 0 ; i < m; i++) {
            int a, b;
            ll w;
            scanf("%d%d%s%lld", &a, &b,st,&w);
            if (st[0] == 'g') {
                addedge(b+a, a - 1, -w - 1);
            } else {
                addedge(a - 1, a+b, w - 1);
            }
        } 
        
        for (i = 0 ; i <= n-1; i++) {
            addedge(-1, i, 0);
        }
        
        if (!bellmanford()) {
            printf("successful conspiracy\n");
        } else {
            printf("lamentable kingdom\n");
        }
    }
    return 0;
}
