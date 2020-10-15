#include <bits/stdc++.h>
#define MAX_SIZE 1025
using namespace std;

int n;
int mn[MAX_SIZE];
set<int> s;
vector<int> query(int pos, int bt) {
    vector<int> ret = vector<int>(n+1, 1000000011);
    vector<int> qs;
    s.clear();
    int i;
    for (i = 1; i <= n; ++i) {
        int curr = (i >> pos) & 1;
        if (curr == bt) {
            s.insert(i);
            qs.push_back(i);
        }
    }
    // cout << "ok " << " " <<  << endl;
    if (qs.empty()) return ret;
    cout << qs.size() << endl;
    for (auto v : qs) {
        cout << v << " ";
    }
    cout << endl;
    fflush(stdout);
    for (i = 1; i <= n; ++i) {
        int v;
        scanf("%d", &v);
        ret[i] = v;
    }
    return ret;
}

int main() {
    int i, j, k;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) mn[i] = 1000000011;
    for (i = 0 ; i <= 9; ++i) {
        for (j = 0 ; j <= 1; ++j) {
            vector<int> ret = query(i, j);
            for (k = 1; k <= n; ++k) {
                if (s.find(k) == s.end()) {
                    mn[k]= min(mn[k], ret[k]);
                }
            }
        }
    }

    printf("-1\n");
    for (i = 1; i <= n; ++i) printf("%d ", mn[i]);
    fflush(stdout);
    return 0;
}