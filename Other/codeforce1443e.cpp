#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define MAX_SIZE 200011
typedef long long ll;
using namespace std;
using namespace __gnu_pbds ;
typedef tree <int , null_type , less <int>, rb_tree_tag ,
tree_order_statistics_node_update> ordered_set ;

ordered_set st;
ll pre[MAX_SIZE], ord = 0, fac[17];
int a[MAX_SIZE], p[MAX_SIZE], used[17];
int N, M, Q;

void permute() {	
	int i;
    ll x = ord;
    st.clear();
    for (i = 1; i <= M; ++i) st.insert(i);
    for(i = 1; i <= M; ++i) {
		int t = x / fac[M-i] + 1;
        int k = *st.find_by_order(t - 1);
		st.erase(k);
        p[i] = k;
		x %= fac[M-i];
	}
}

int main() {
    int i;
    scanf("%d%d", &N, &Q);
    for (i = 1; i <= N; ++i) {
        pre[i] = pre[i-1] + i;
    }

    M = min(15, N);
    fac[0] = 1;
    for (i = 1; i <= 15; ++i) fac[i] = fac[i-1] * i;
    while (Q-- > 0) {
        int tp;
        scanf("%d", &tp);
        if (tp == 1) {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%I64d\n", pre[r] - pre[l-1]);
        } else {
            int x;
            scanf("%d", &x);
            ord = ord + x;
            permute();
            for (i = 1; i <= M; ++i) {
                a[i + N - M] = p[i];
                pre[i + N - M] = pre[i + N - M - 1] + p[i];
            }
        }
    }
    return 0;
}