#include <bits/stdc++.h>
#define MAX_SIZE 10111
#define REP(i,a,b) for(i=a;i<=b;++i)
#define RREP(i,a,b) for(i=a;i>=b;--i)
#define rin(a) scanf("%d",&a)
using namespace std;

vector<int> g[MAX_SIZE];

bool check(int id1, int id2) {
    int i = 0, j = 0, sz1 = g[id1].size(), sz2 = g[id2].size();
    while (i < sz1 && j < sz2) {
        if (g[id1][i] == g[id2][j]) return true;
        if (g[id1][i] < g[id2][j]) {
            ++i;
        } else {
            ++j;
        }
    }

    return false;
}

int main() {
    int k, i, v, j, m, n;
    rin(m), rin(n);
    REP(i,1,m) {
        scanf("%d", &k);
        while (k--) {
            rin(v);
            g[i].push_back(v);
        }

        sort(g[i].begin(), g[i].end());
    }

    REP(i, 1, m) {
        REP(j, 1, i-1) {
            if (!check(i, j)) {
                cout << "impossible" << endl;
                return 0;
            }
        }
    }

    cout << "possible" << endl;
    return 0;
}