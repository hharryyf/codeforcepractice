#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, m, r;

set<pair<int, int>> visited;

ll covered(int x, int y) {
    int right = min(y, r), down = min(x, r);
    int left = max(y- (m - r), 1), up = max(x - (n - r), 1);
    return 1ll * (right - left + 1) * (down - up + 1);
}

int main() {
    int k;
    scanf("%d%d%d%d", &n, &m, &r, &k);
    priority_queue<pair<ll, pair<int, int>>> q;
    ll tol = 0;
    int cnt = 0, i;
    int dx[4] = {0,0,1,-1}, dy[4] = {1,-1,0,0};
    q.push(make_pair(covered(r, r), make_pair(r, r)));
    while (!q.empty() && cnt < k) {
        auto p = q.top();
        q.pop();
        if (visited.find(p.second) != visited.end()) continue;
        visited.insert(p.second);
        tol += p.first;
        cnt++;
        for (i = 0 ; i < 4; i++) {
            int tx = p.second.first + dx[i], ty = p.second.second + dy[i];
            if (tx >= 1 && tx <= n && ty >= 1 && ty <= m) {
                if (visited.find(make_pair(tx, ty)) == visited.end()) {
                    q.push(make_pair(covered(tx, ty), make_pair(tx, ty)));
                }
            }
        }
    }
    
    printf("%.10lf\n", 1.0 * tol /(1.0 * (n-r + 1) * (m-r + 1)));
    return 0;
}
