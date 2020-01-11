#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include<iostream>  
#include<sstream>
#define INF 90000000 
#define MAX_SIZE 55
using namespace std;

struct edge {
    int from, to;
    int wt;
    vector<int> cst;
};

vector<edge> edg;
int n;
int dist[MAX_SIZE];

void init() {
    int i;
    edg.clear();
    for (i = 0 ; i < MAX_SIZE; i++) {
        dist[i] = INF;
    }
}

void bellmanford(int s) {
    dist[s] = 0;
    int i, j, k;
    for (i = 0 ; i < n; i++) {
        for (k = 0; k < edg.size(); k++) {
        	edge e = edg[k];
            for (j = 0 ; j < e.cst.size(); j += 2) {
                int curr = max(e.cst[j], dist[e.from]) + e.wt;
                if (curr <= e.cst[j+1]) {
                    dist[e.to] = min(dist[e.to], curr);
                }
            }
        }
    }
}

char st[MAX_SIZE * 4];

int main() {
    int i, m, s, t;
    while(scanf("%d", &n) != EOF) {
    	
    	if (n == 0) break;
    	scanf("%d%d%d", &m, &s, &t);
        init();
        fgets(st, MAX_SIZE * 4, stdin);
        for (i = 0 ; i < m; i++) {
            edge e;
            e.cst.clear();
            e.cst.push_back(0);
            int cnt = 1;
            fgets(st, MAX_SIZE * 4, stdin);
            string str = st;
			istringstream ss(str);
			while (ss >> str) {
				if (cnt == 1) {
				    e.from = atoi(str.c_str());
				} else if (cnt == 2) {
				    e.to = atoi(str.c_str());
				} else if (cnt == 3) {
					e.wt = atoi(str.c_str());
				} else {
				    e.cst.push_back(atoi(str.c_str()));
				}
				cnt++;
			}
			
			if (e.cst.size() % 2 == 1) {
			    e.cst.push_back(INF);
			}
			
			edg.push_back(e);
			swap(e.from, e.to);
			edg.push_back(e);
        }
        bellmanford(s);
		int ret = dist[t];
		if (ret < INF) {
  		    printf("%d\n", dist[t]);
		} else {
            printf("*\n");
		}
    }
    return 0;
}
