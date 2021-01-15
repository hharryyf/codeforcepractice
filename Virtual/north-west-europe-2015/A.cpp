#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int N, i, ans = 0;
    ll M;
    scanf("%d%I64d", &N, &M);
    ans = N;
    priority_queue<ll, vector<ll>, greater<ll>> q;
    vector<pair<ll, ll>> curr;
    for (i = 0 ; i < N; ++i) {
        ll u, v;
        scanf("%I64d%I64d", &u, &v);
        curr.emplace_back(u, u + v);
    }    

    sort(curr.begin(), curr.end());
    for (auto p : curr) {
        while (!q.empty() && q.top() + M < p.first) {
            //cout << q.top() << " -> " << M << " " << p.first << endl;
            //cout << "out1 " << q.top() << endl;
            q.pop();
        }

        if (!q.empty() && q.top() <= p.first && q.top() + M >= p.first) {
            //cout << "get out " << q.top() << endl;
            q.pop();
        } else {
            ans--;
        }
        q.push(p.second);
    }

    printf("%d\n", ans);
    return 0;
}