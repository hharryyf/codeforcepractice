#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

int l[MAX_SIZE], r[MAX_SIZE], t[MAX_SIZE];
vector<pair<int, pair<int, int>>> evt;
int n;
set<pair<int, int>> g[2];

int main() {
    int i, ans = 0;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d%d%d", &l[i], &r[i], &t[i]);
        --t[i];
        evt.push_back(make_pair(l[i], make_pair(0, i)));
        evt.push_back(make_pair(r[i], make_pair(1, i)));
    }

    sort(evt.begin(), evt.end());

    for (auto &e : evt) {
        if (e.second.first == 1) {
            int tp = t[e.second.second];
            int other = tp ^ 1;
            if (g[tp].find(make_pair(r[e.second.second], e.second.second)) != g[tp].end() 
               && !g[other].empty()) {
                   g[other].erase(g[other].begin());
                   ans++;
            } 

            g[tp].erase(make_pair(r[e.second.second], e.second.second));
        } else {
            g[t[e.second.second]].insert(make_pair(r[e.second.second], e.second.second));
        }
    }

    printf("%d\n", n - ans);
    return 0;
}