#include <bits/stdc++.h>
#define MAX_SIZE 300011
using namespace std;
typedef long long ll;
const ll inf = 1e13;
map<int, vector<int>> g[MAX_SIZE]; 
map<int, int> cost[MAX_SIZE][2];
int N, D;
int a[MAX_SIZE];
char ss[4];

ll remove_01(vector<int> &dir, ll c) {
    vector<int> curr;
    ll ret = 0;
    for (auto v : dir) {
        if (curr.empty()) {
            curr.push_back(v);
            continue;
        }

        if (v == 1 && curr.back() == 0) {
            curr.pop_back();
            ret += c;
        } else {
            curr.push_back(v);
        }
    }

    dir.clear();
    for (auto v : curr) {
        dir.push_back(v);
    }

    return ret;
}

ll remove_10(vector<int> &dir, ll c) {
    vector<int> curr;
    ll ret = 0;
    for (auto v : dir) {
        if (curr.empty()) {
            curr.push_back(v);
            continue;
        }

        if (v == 0 && curr.back() == 1) {
            curr.pop_back();
            ret += c;
        } else {
            curr.push_back(v);
        }
    }

    dir.clear();
    for (auto v : curr) {
        dir.push_back(v);
    }
    
    return ret;
}

ll remove_0(vector<int> &dir, ll c) {
    vector<int> curr;
    ll ret = 0;
    for (auto v : dir) {
        if (v == 1) {
            curr.push_back(v);
        } else {
            ret += c;
        }
    }

    dir.clear();
    for (auto v : curr) {
        dir.push_back(v);
    }
    
    return ret;
}

ll remove_1(vector<int> &dir, ll c) {
    vector<int> curr;
    ll ret = 0;
    for (auto v : dir) {
        if (v == 0) {
            curr.push_back(v);
        } else {
            ret += c;
        }
    }

    dir.clear();
    for (auto v : curr) {
        dir.push_back(v);
    }
    
    return ret;
}

// x->y forward
ll solve(int x, int y, vector<int> &dir) {
    int i;
    ll ret = 0;
    vector<ll> cst = vector<ll>(4, 0);
    cst[0] = cost[x][0][y];
    cst[1] = cost[y][0][x];
    cst[2] = cost[x][1][y];
    cst[3] = cost[y][1][x];
  
    for (i = 0 ; i < 4; ++i) {
        if (cst[i] == 0) cst[i] = inf;
    }
    // 0->cost 0, 1-> cost 1, 2-> cost 01, 3-> cost 10
    cst[0] = min(cst[0], cst[2]);
    cst[1] = min(cst[1], cst[3]);

    if (cst[3] <= cst[2] && cst[3] < cst[0] + cst[1] && cst[3] != inf) {
        ret += remove_10(dir, cst[3]);
    }

    if (cst[2] < cst[0] + cst[1] && cst[2] != inf) {
        ret += remove_01(dir, cst[2]);
    }

    if (cst[3] < cst[0] + cst[1] && cst[3] != inf) {
        ret += remove_10(dir, cst[3]);
    }

    ret += remove_0(dir, cst[0]);
    ret += remove_1(dir, cst[1]);
    return ret;
}

int main() {    
    int i;
    scanf("%d%d", &N, &D);
    for (i = 1; i <= D; ++i) {
        scanf("%d", &a[i]);
    }

    for (i = 1; i < D; ++i) {
        if (a[i] < a[i+1]) {
            g[a[i]][a[i+1]].push_back(0);
        } else {
            g[a[i+1]][a[i]].push_back(1);
        }
    }

    int M;
    scanf("%d", &M);
    for (i = 1; i <= M; ++i) {
        int u, v, c;
        scanf("%d%d%s%d", &u, &v, ss, &c);
        if (ss[0] == 'O') {
            if (cost[u][0][v] == 0) {
                cost[u][0][v] = c;
            } else {
                cost[u][0][v] = min(cost[u][0][v], c);
            }                       
        } else {
            if (cost[u][1][v] == 0) {
                cost[u][1][v] = c;
            } else {
                cost[u][1][v] = min(cost[u][1][v], c);
            }   
        }
    }

    long long ans = 0;
    for (i = 1; i <= N; ++i) {
        if (g[i].empty()) continue;
        for (auto v : g[i]) {
            ans = ans + solve(i, v.first, v.second);
        }
    }

    cout << ans << endl;
    return 0;
}