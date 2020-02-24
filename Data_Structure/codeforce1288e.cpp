#pragma GCC optimize(3) 
#include <bits/stdc++.h>
#define MAX_SIZE 300011
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds ;
using namespace std ;
typedef pair<int, int> TP;
typedef tree <TP , null_type , less <TP>, rb_tree_tag ,
tree_order_statistics_node_update> ordered_set ;

ordered_set st;
int a[MAX_SIZE];
int mn[MAX_SIZE], mx[MAX_SIZE];
int n, m;

int main() {
    int i;
    scanf("%d%d", &n, &m);
    if (n == 1) {
        printf("1 1\n");
        return 0;
    }
    for (i = 1; i <= n; i++) {
        a[i] = i;
        mn[i] = mx[i] = i;
        st.insert(make_pair(i, i));
    }
    while (m > 0) {
        int v;
        scanf("%d", &v);
        mn[v] = 1;
        mx[v] = max(mx[v], 1 + (int) st.order_of_key(make_pair(a[v], v)));
        st.erase(make_pair(a[v], v));
        auto p = *st.begin();
        a[v] = p.first - 1;
        st.insert(make_pair(a[v], v));
        m--;
    }
    
    i = 1;
    auto iter = st.begin();
    while (iter != st.end()) {
        mn[iter->second] = min(mn[iter->second], i);
        mx[iter->second] = max(mx[iter->second], i);
        i++;
        iter++;
    }
    
    for (i = 1; i <= n; i++) {
        printf("%d %d\n", mn[i], mx[i]);
    }
    return 0;
}

