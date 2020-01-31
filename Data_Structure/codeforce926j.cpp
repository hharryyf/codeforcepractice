#pragma GCC optimize(3)
#include <bits/stdc++.h>

using namespace std;

set<pair<int, int>> s;

void add(int l, int r) {
    if (s.empty()) {
        s.insert(make_pair(l, r));
    } else {
        set<pair<int, int>> :: iterator iter = s.lower_bound(make_pair(l, 0));
        if (iter != s.begin()) {
            iter = prev(iter);
            if (iter->second >= l) {
                l = min(iter->first, l), r = max(iter->second, r);
                s.erase(iter);
            }
        } 
        
        iter = s.lower_bound(make_pair(l, 0));
        while (iter != s.end() && iter->first <= r) {
            auto it = iter;
            iter++;
            r = max(it->second, r);
            s.erase(it);
        }
        s.insert(make_pair(l, r));
    }
}

int main() {
    int i, n;
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        add(l, r);
        printf("%d ", s.size());
    }
    printf("\n");
    return 0;
}
