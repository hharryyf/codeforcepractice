#pragma GCC optimize(3)
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int h, q;
// the answer interval init with the longtest interval
pair<ll, ll> ans;
// we want ok to be a disjointed set of intervals
set<pair<ll, ll>> ok;
// rm to be a disjointed set of intervals
set<pair<ll, ll>> rm;
pair<ll, ll> crt(int level, ll L, ll R) {
    return make_pair(L * (1ll << (h - level)), (R + 1) * (1ll << (h - level)) - 1);
}

// add p to the rm set, after this function is called, rm must be 
// a disjointed set of intervals
void add(pair<ll, ll> p) {
    if (rm.empty()) {
        rm.insert(p);
    } else {
        auto iter = rm.lower_bound(make_pair(p.first, 0));
        if (iter != rm.begin()) {
            auto pp = *prev(iter);
            if (pp.second >= p.first) {
                rm.erase(pp);
                p.first = min(p.first, pp.first);
                p.second = max(pp.second, p.second);
            }
        } 
        
        iter = rm.lower_bound(make_pair(p.first, 0));
        while (iter != rm.end() && iter->first <= p.second) {
            auto it = iter;
            iter++;
            p.second = max(p.second, it->second);
            rm.erase(it);
        }
        rm.insert(p);
    }
}


void addn(ll L, ll R) {
    if (L <= R) ok.insert(make_pair(L, R));
}
// delete the "interval" p from the ok set
// note that p doesn't have to be in the ok set, just eliminate part of the interval
void del(pair<ll, ll> p) {
    if (ok.empty()) return;
    auto iter = ok.lower_bound(make_pair(p.first, 0));
    if (iter != ok.begin()) {
        auto curr = *prev(iter);
        if (curr.second >= p.first) {
            ok.erase(curr);
            addn(curr.first, p.first - 1);
            addn(p.second + 1, curr.second);
        }
    }
    
    iter = ok.lower_bound(make_pair(p.first, 0));
    bool flag = false;
    pair<ll, ll> lst = p;
    while (iter != ok.end() && iter->first <= p.second) {
        if (iter->second <= p.second) {
            auto it = iter;
            iter++;
            ok.erase(it);
        } else {
            flag = true;
            lst = *iter;
            break;
        }
    }
    
    if (flag) {
        ok.erase(lst);
        addn(p.second + 1, lst.second);
    }
}
// ans becomes the intersection of p and ans, if ans is empty
// return false, otherwise return true
bool join(pair<ll, ll> p) {
    ans.first = max(ans.first, p.first);
    ans.second = min(ans.second, p.second);
    return ans.first <= ans.second;     
}

int main() {
    scanf("%d%d", &h, &q);
    ans = crt(1, 1, 1);
    while (q > 0) {
        int level;
        ll L, R;
        int val;
        scanf("%d%lld%lld%d", &level, &L, &R, &val);
        if (val == 1) {
            if (!join(crt(level, L, R))) {
                printf("Game cheated!\n");
                return 0;
            }
        } else {
            add(crt(level, L, R));
        }
        q--;
    }
    
    ok.insert(ans);
    for (auto p : rm) {
        del(p);
    }
    
    if (ok.empty()) {
        printf("Game cheated!\n");
        return 0;
    } else if (ok.size() == 1) {
        auto p = *ok.begin();
        if (p.first == p.second) {
            printf("%lld\n", p.first);
            return 0;
        }
    }
    
    printf("Data not sufficient!\n");
    return 0;
}
