#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define MAX_SIZE 500011
using namespace __gnu_pbds ;
using namespace std ;
typedef long long ll;
typedef tree <int , null_type , less <int>, rb_tree_tag ,
tree_order_statistics_node_update> ordered_set ;

ordered_set myset;

pair<ll, int> a[MAX_SIZE];
pair<ll, int> q[MAX_SIZE];
int ans[MAX_SIZE];

int main() {
    int i, j, n, m, Q;
    scanf("%d%d%d", &n, &m, &Q);
    for (i = 1; i <= n; ++i) {
        int v;
        scanf("%d", &v);
        a[v].first++;
    }

    for (i = 1; i <= m; ++i) {
        a[i].second = i;
    }

    sort(a + 1, a + 1 + m);

    for (i = 1; i <= Q; ++i) {
        scanf("%I64d", &q[i].first);
        q[i].first--;
        q[i].second = i;
    }

    sort(q + 1, q + 1 + Q);

    a[m + 1].first = 2e18 / m;
    ll tol = n;
    myset.insert(a[1].second);
    for (i = 1, j = 1; i <= Q; ++i) {
        // cout << "query i= " << i << " tol= " << tol << endl;
        while (j <= m && a[j].first == a[j+1].first) {
            myset.insert(a[++j].second);
            //cout << "query i= " << i << " insert " << a[j].second << endl;
        }

        while (j <= m && tol + (a[j+1].first - a[j].first) * (int) myset.size() <= q[i].first) {
            tol += (a[j+1].first - a[j].first) * (int) myset.size();
            myset.insert(a[++j].second);
            // cout << "query i= " << i << " insert " << a[j].second << endl;
        }

        int ord = (q[i].first - tol) % (int) myset.size();
        ans[q[i].second] = *myset.find_by_order(ord);
    }

    for (i = 1; i <= Q; ++i) {
        printf("%d\n", ans[i]);
    }

    return 0;
}