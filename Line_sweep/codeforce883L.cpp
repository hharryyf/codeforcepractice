#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 200011
typedef long long ll;
using namespace std;
// this is a set that supports queries on all the position that has a taxi
set<int> st;  
// this is a map that stores the available taxi at each position
// (start waiting time, taxi id)
set<pair<ll, int>> bus[MAX_SIZE];
// (start waiting time -> (stop position, taxi id) for each taxi that's in use
map<ll, set<pair<int, int>>> q;

int n, k, m;

int main() {
    int i;
    scanf("%d%d%d", &n, &k, &m);
    for (i = 1; i <= k; ++i) {
        int xi;
        scanf("%d", &xi);
        st.insert(xi);
        bus[xi].insert(make_pair(0, i));
    }

    while (m-- > 0) {
        ll ti;
        int a, b;
        scanf("%I64d%d%d", &ti, &a, &b);
        while (!q.empty()) {
            auto iter = q.begin();
            if (iter->first > ti) break;
            for (auto p : iter->second) {
                st.insert(p.first);
                bus[p.first].insert(make_pair(iter->first, p.second));
            }
            q.erase(iter->first);
        }

        if (!st.empty()) {
            // case when there is an available car at ti
            auto iter = st.upper_bound(a);
            pair<int, pair<ll, int>> car = make_pair(1e6, make_pair(1e14, 1e6));
            bool ok = false;
            if (iter != st.end()) {
                car.first = *iter;
                car.second = *bus[car.first].begin();
                ok = true;
            }

            if (iter != st.begin()) {
                iter = prev(iter);
                if (ok) {
                    int pos = *iter;
                    if ((abs(pos - a) < abs(car.first - a)) 
                    || (abs(pos - a) == abs(car.first - a) && car.second > *bus[pos].begin())) {
                        car.first = pos;
                        car.second = *bus[pos].begin();
                    }
                } else {
                    car.first = *iter;
                    car.second = *bus[car.first].begin();
                }
            }

            printf("%d %d\n", car.second.second, abs(car.first - a));
            bus[car.first].erase(car.second);
            if (bus[car.first].empty()) st.erase(car.first);
            ll finish = ti + abs(car.first - a) + abs(b - a);
            q[finish].insert(make_pair(b, car.second.second));
        } else {
            // case when there's no such car
            // look into the q begin set
            // pick the best car
            ll t = q.begin()->first;
            auto iter = q[t].upper_bound(make_pair(a, 0));
            pair<int, int> car = make_pair(0, 0);
            if (iter != q[t].end()) {
                car = *iter;
            }

            if (iter != q[t].begin()) {
                iter = prev(iter);
                iter = q[t].upper_bound(make_pair(iter->first, 0));
                if (car.first != 0) {
                    if ((abs(car.first - a) > abs(iter->first - a)) 
                    || ((abs(car.first - a) == abs(iter->first - a)) && car.second > iter->second)) {
                        car = *iter;
                    }
                } else {
                    car = *iter;
                }
            }
            printf("%d %I64d\n", car.second, abs(t - ti) + abs(car.first - a));
            q[t].erase(car);
            if (q[t].empty()) q.erase(t);
            q[t + abs(car.first - a) + abs(b - a)].insert(make_pair(b, car.second));
        }
    }
    return 0;
}