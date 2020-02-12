#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 5003
using namespace std;

bool conn[MAX_SIZE << 1][MAX_SIZE << 1];
vector<int> g[MAX_SIZE << 1];
char s1[MAX_SIZE][22], s2[MAX_SIZE][22];
unordered_map<string, int> h;
int ans[MAX_SIZE << 1];

int main() {
    int i, m, j;
    scanf("%d", &m);
    for (i = 1; i <= m; i++) {
        scanf("%s%s", s1[i], s2[i]);
        string s = string(s1[i]);
        h[s] = 0;
        s = string(s2[i]);
        h[s] = 0;
    }
    
    auto iter = h.begin();
    int cnt = 1;
    while (iter != h.end()) {
        iter->second = cnt++;
        iter++;
    }
    
    int n = h.size();
    printf("%d\n", n);
    for (i = 1 ; i <= m; i++) {
        int idx1 = h[s1[i]], idx2 = h[s2[i]];
        g[idx1].push_back(idx2);
        g[idx2].push_back(idx1);
        conn[idx1][idx2] = true;
        conn[idx2][idx1] = true;
    }
    
    for (i = 1; i <= n; i++) {
        cnt = 0;
        int mx = 0;
        for (j = 1; j <= n; j++) {
            if (conn[i][j] || j == i) continue;
            int tol = 0;
            for (auto v : g[j]) {
                if (conn[i][v]) {
                    tol++;
                }
            }
            
            if (tol > mx) {
                cnt = 1;
                mx = tol;
            } else if (tol == mx) {
                cnt++;
            }
        }
        
        
        ans[i] = cnt;
    }
    
    iter = h.begin();
    while (iter != h.end()) {
        printf("%s %d\n", iter->first.data(), ans[iter->second]);
        iter++;
    }
    return 0;
}
