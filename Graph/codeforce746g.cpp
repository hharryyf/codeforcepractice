#include <bits/stdc++.h>
#define MAX_SIZE 200111
using namespace std;

bool leaf[MAX_SIZE];
vector<int> g[MAX_SIZE];
int k, n, t;
int a[MAX_SIZE];
int maxit[MAX_SIZE];

int main() {
    int i;
    a[0] = 1;
    g[0].push_back(1);
    int cnt = 1, j;
    scanf("%d%d%d", &n, &t, &k);
    for (i = 1; i <= t; i++) {
        scanf("%d", &a[i]);
        for (j = 1; j <= a[i]; j++) {
            g[i].push_back(++cnt);
        }
    }
    
    for (i = 0 ; i < g[t].size(); i++) {
        leaf[g[t][i]] = true;
        k--;
    }
    
    for (i = 1; i <= t - 1; i++) {
        if (a[i] > a[i+1]) {
            int d = a[i] - a[i+1];
            for (j = (int) g[i].size() - 1; j >= 0 && d > 0; j--, d--) {
                leaf[g[i][j]] = true;
                k--;
            }
        }
    }
    
    if (k < 0) {
        printf("-1\n");
        return 0;
    }
    
    for (i = t - 1; i > 0; i--) {
        for (j = (int) g[i].size() - 1; j > 0; j--) {
            if (k > 0 && !leaf[g[i][j]]) {
                leaf[g[i][j]] = true, k--;
            }
        }
    }
    
    if (k != 0) {
        printf("-1\n");
        return 0;
    }
    
    printf("%d\n", n);
    for (i = 0 ; i <= t; i++) {
        for (j = 0; j < g[i].size(); j++) {
            if (!leaf[g[i][j]]) maxit[i] = j;
        }
    }
    
    vector<pair<int, int>> ret;
    for (i = 0 ; i < t; i++) {
        for (j = 0; j < maxit[i]; j++) {
            ret.emplace_back(g[i][j], g[i+1][j]);
        }
        
        for (j = maxit[i] ; j < g[i+1].size(); j++) {
            ret.emplace_back(g[i][maxit[i]], g[i+1][j]);
        }
    }
    
    for (auto p : ret) {
        printf("%d %d\n", p.first, p.second);
    }
    return 0;
}
