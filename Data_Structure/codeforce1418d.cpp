#include <bits/stdc++.h>
using namespace std;

multiset<int> diff;
set<int> pos;

void insert(int x) {
    if (pos.empty()) {
        pos.insert(x);
        return;
    }

    if (x > *pos.rbegin()) {
        diff.insert(x - *pos.rbegin());
        pos.insert(x);
    } else if (x < *pos.begin()) {
        diff.insert(*pos.begin() - x);
        pos.insert(x);
    } else {
        auto iter = pos.upper_bound(x);
        auto it = prev(iter);
        diff.erase(diff.find(*iter - *it));
        diff.insert(*iter - x);
        diff.insert(x - *it);
        pos.insert(x);
    }
}

void remove(int x) {
    if ((int) pos.size() <= 1) {
        pos.erase(x);
        return;
    }

    if (x == *pos.begin()) {
        auto iter = pos.upper_bound(x);
        diff.erase(diff.find(*iter - x));
        pos.erase(x);
    } else if (x == *pos.rbegin()) {
        auto iter = pos.find(x);
        iter = prev(iter);
        diff.erase(diff.find(x - *iter));
        pos.erase(x);
    } else {
        auto iter = pos.upper_bound(x);
        auto it = prev(pos.find(x));
        diff.erase(diff.find(x - *it));
        diff.erase(diff.find(*iter - x));
        diff.insert(*iter - *it);
        pos.erase(x);
    }
}

void query() {
    if ((int) pos.size() <= 2) {
        printf("0\n");
    } else {
        printf("%d\n", *pos.rbegin() - *pos.begin() - *diff.rbegin());
    }
}

int main() {
    int i, n, q;
    scanf("%d%d", &n, &q);
    for (i = 1; i <= n; ++i) {
        int v;
        scanf("%d", &v);
        insert(v);
    }

    query();
    while (q-- > 0) {
        int tp, x;
        scanf("%d%d", &tp, &x);
        if (tp == 0) {
            remove(x);
        } else {
            insert(x);
        }

        query();
    }
    return 0;
}