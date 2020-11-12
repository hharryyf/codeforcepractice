#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct carrot {
    int cut, len; 
    ll cost;
    bool operator < (carrot other) const {
        return cost < other.cost;
    }
};
// full means the cut == len
vector<carrot> full;


ll getcost(carrot c) {
    // cout << "getcost " << c.len << " " << c.cut << " ";
    // we cut c.cut many times
    int rem = c.len % c.cut, other = c.cut - rem;
    int base = c.len / c.cut;
    // cout <<1ll * other * base * base + 1ll * rem * (base + 1) * (base + 1) << endl; 
    return 1ll * other * base * base + 1ll * rem * (base + 1) * (base + 1);
}

ll calc_nxt(carrot c) {
    carrot c1 = {c.cut + 1, c.len, c.cost};
    ll ret =  getcost(c) - getcost(c1);
    // cout << "mergecost= " << ret << endl;
    return ret;
}


int main() {
    int n, k, i;
    priority_queue<carrot> q;
    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; ++i) {
        int v;
        scanf("%d", &v);
        if (v == 1) {
            full.push_back(carrot{1, 1, 1});
        } else {
            carrot t;
            t.len = v, t.cut = 1;
            t.cost = calc_nxt(t);
            q.push(t);
        }
    }

    for (i = n; i < k; ++i) {
        auto p = q.top();
        q.pop();
        p.cut++;
        if (p.cut < p.len) {
            p.cost = calc_nxt(p);
            q.push(p);
        } else {
            full.push_back(p);
        }
    }

    ll ans = 0;
    while (!q.empty()) {
        auto p = q.top();
        ans += getcost(p);
        q.pop();
    }

    for (auto p : full) {
        ans += getcost(p);
    }

    cout << ans << endl;
    return 0;
}