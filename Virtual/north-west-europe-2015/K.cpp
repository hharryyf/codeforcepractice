#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll inf = 1e18;
int bad[79][79];
int tol[1011];
vector<int> occ[79];
int N, R, S, M, D;

bool mul(ll v1, ll v2) {
    if (v1 == 0 || v2 == 0) return true;
    return v1 <= inf / v2;
}

int main() {
    int i, j, k;
    scanf("%d%d%d%d%d", &R, &S, &M, &D, &N);
    for (i = 1; i <= R; ++i) scanf("%d", &tol[i]);
    for (i = 1; i <= S + M + D; ++i) {
        int p;
        scanf("%d", &p);
        while (p-- > 0) {
            int v;
            scanf("%d", &v);
            occ[i].push_back(v);
        }
    }

    for (i = 0 ; i < N; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        bad[u][v] = bad[v][u] = 1;
    }

    ll ans = 0;
    for (i = 1; i <= S; ++i) {
        for (j = 1; j <= M; ++j) {
            for (k = 1; k <= D; ++k) {
                int id1 = i, id2 = j + S, id3 = M + S + k;
                if (bad[id1][id2] || bad[id2][id3] || bad[id1][id3]) continue;
                set<int> useful;
                ll curr = 1;
                for (auto v : occ[id1]) useful.insert(v);
                for (auto v : occ[id2]) useful.insert(v);
                for (auto v : occ[id3]) useful.insert(v); 
                for (auto iter : useful) {
                    if (!mul(curr, tol[iter])) {
                        ans = inf + 1;
                        break;
                    } else {
                        curr = curr * tol[iter]; 
                    }
                }
                ans = ans + curr;
                if (ans > inf) break;
            }
        }
    }
    if (ans <= inf) {
        cout << ans << endl;
    } else {
        cout << "too many" << endl;
    }
    return 0;
}