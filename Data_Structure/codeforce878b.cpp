#pragma GCC optimize(3)
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
int n, k, m;
list<pair<int, int>> s;
ll ans = 0;

int main() {
    int i, v;
    scanf("%d%d%d", &n, &k, &m);
    for (i = 1; i <= n; i++) {
        scanf("%d", &v);
        if (s.empty()) {
            s.push_back(make_pair(v, 1));
        } else {
            pair<int, int> p = s.back();
            if (p.first == v) {
                s.push_back(make_pair(v, p.second + 1));
            } else {
                s.push_back(make_pair(v, 1));
            }
        }
        
        if (s.back().second == k) {
            while (!s.empty() && s.back().first == v) {
                s.pop_back();
            }
            ans++;
        }
    }
    
    ll tol = 1ll * (ll) n * (ll) m;
    ans = ans * ((ll) m) * ((ll) k);
    if (s.empty()) {
        printf("%lld\n", tol - ans);
        return 0;
    }
    // there are 2 cases that would increment the final answer
    // case 1
    // the size of the stack is less than k and all the elements
    // remaining in the set is unique, then the answer would increment
    // be incremented by s.size() * m / k
    if (s.size() < k) {
        if (s.back().second == s.size()) {
            ans += (1ll * s.size() * m / (1ll * k)) * ((ll) k);
        }
    } else {
        // case 2, we count the matched pairs of the front and back elements
        ll cnt = 0;
        bool flag = true;
        while (s.size() >= k) {
            bool match = true;
            v = s.front().first;
            auto it1 = s.begin();
            auto it2 = s.rbegin();
            for (i = 0 ; i < k; i++) {
                if (it1->first == v) {
                    it1++;
                } else if (it2->first == v) {
                    it2++;
                } else {
                    match = false;
                    break;
                }
            }
            
            if (!match) break;
            for (i = 0 ; i < k; i++) {
                if (v == s.front().first) {
                    s.pop_front();
                } else {
                    s.pop_back();
                }
            }
            
            cnt++;
        }
        
        ans += cnt * ((ll) (m-1)) * (ll) k;
        if (!s.empty()) {
            v = s.front().first;
            for (auto vl : s) {
                if (vl.first != v) {
                    flag = false;
                    break;
                }
            }
            
            if (flag) {
                ans += (1ll * (ll) s.size() * (ll) m / ((ll) k)) * ((ll) k);
                if ((1ll * (ll) s.size() * (ll) m) % ((ll) k) == 0) {
                    ans += 1ll * cnt * k;  
                }
            }
            
        }
        
    }
    
    printf("%lld\n", tol - ans);
    return 0;
}
