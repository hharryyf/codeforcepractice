#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 200111
using namespace std;

bool visited[MAX_SIZE];
bool join[MAX_SIZE];
int f[MAX_SIZE];
vector<int> g[MAX_SIZE];
vector<int> can;
vector<pair<int, int>> ret;
int D, n, m;

void preprocess() {
    int i;
    for (i = 0 ; i < MAX_SIZE; i++) f[i] = i;
}

int find(int x) {
    if (x == f[x]) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    f[a] = b;
}

int main() {
    int i;
    preprocess();
    scanf("%d%d%d", &n, &m, &D);
    for (i = 0 ; i < m; i++) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        if (v1 == 1 || v2 == 1) {
            can.push_back(v1 + v2 - 1);
        } else {
            if (find(v1) != find(v2)) {
                unionset(v1, v2);
            }
            g[v1].push_back(v2), g[v2].push_back(v1);
        }
    }
    
    int tol = 0;
    for (i = 2; i <= n; i++) {
        if (find(i) == i) tol++; 
    }
    
    for (auto c : can) {
        if (!visited[find(c)]) {
            join[c] = true;
            visited[find(c)] = true;
            tol--;
            D--;
        }
    }
    
    if (D < 0 || tol > 0) {
        printf("NO\n");
        return 0;
    }
    
    for (auto c : can) {
        if (!join[c] && D > 0) {
            join[c] = true;
            D--;
        }
    }
    
    if (D != 0) {
        printf("NO\n");
        return 0;
    }
    
    preprocess();
    for (i = 1; i <= n; i++) {
        if (join[i]) {
            ret.emplace_back(1, i);
            unionset(1, i);
        }
    }
    
    for (i = 2; i <= n; i++) {
        for (auto v : g[i]) {
            if (find(i) != find(v)) {
                ret.emplace_back(i, v);
                unionset(i, v);
            }
        }
    }
    
    printf("YES\n");
    for (auto r : ret) printf("%d %d\n", r.first, r.second);
    return 0;
}
