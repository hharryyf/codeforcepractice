#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#define MAX_SIZE 27
using namespace std;

set<int> g[MAX_SIZE];
int n;
int visited[MAX_SIZE];
vector<int> l;
bool isvalid = true;
vector<int> ret;

void dfs(int v) {
    visited[v] = 1;
    set<int> :: iterator iter = g[v].begin();
	while (iter != g[v].end()) {
        int nv = *iter;
		if (visited[nv] == 1) {
            isvalid = false;
        }
        if (!visited[nv]) {
            dfs(nv);
        }
        iter++;
    }
    l.push_back(v);
    visited[v] = 2;
}

int topsort() {
    memset(visited, 0, sizeof(visited));
    int i;
    l.clear();
    ret.clear();
    isvalid = true;
    for (i = 0 ; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    
    for (i = 0 ; i < n; i++) {
        ret.push_back(l.back());
        l.pop_back();
    }
    
    if (!isvalid) {
        return -1;
    }
    
    for (i = 0 ; i < n - 1; i++) {
        if (g[ret[i]].find(ret[i+1]) == g[ret[i]].end()) {
            return 0;
        }
    }
    
    return 1;
}

int idx(char ch) {
    return ch - 'A';
}

void init() {
    int i;
    for (i = 0 ; i < MAX_SIZE; i++) g[i].clear();
}

char st[5];

int main() {
    int m;
    while (scanf("%d%d", &n, &m) != EOF) {
        if (n == 0 && m == 0) break;
        init();
        int i = 0;
        int j = -1;
        for (i = 1 ; i <= m; i++) {
            scanf("%s", st);
            g[idx(st[0])].insert(idx(st[2]));
            int rt = topsort();
            if (rt == -1) {
            	if (j == -1) {
                   printf("Inconsistency found after %d relations.\n", i);
				}
                j = i;
            } else if (rt == 1) {
            	if (j == -1) {
	                printf("Sorted sequence determined after %d relations: ", i);
	                for (int k = 0 ; k < (int) ret.size(); k++) {
	                    int r = ret[k];
						printf("%c", r + 'A');
	                }
	                printf(".\n");
				}
                j = i;
            }
        }
        
        if (j == -1) {
            printf("Sorted sequence cannot be determined.\n");
        }
    }
    return 0;
}
