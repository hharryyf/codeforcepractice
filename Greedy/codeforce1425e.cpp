#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 100011
using namespace std;

int N, K;
ll D[MAX_SIZE], A[MAX_SIZE];
ll suf[MAX_SIZE];
ll pre[MAX_SIZE];
// disconnect i -> i + 1 connect i to 1, i > 1 and i < N
ll solve_1() {
    multiset<ll> st;
    ll ans = 0, mn = D[1];
    int i;
    for (i = 2; i <= N; ++i) st.insert(-D[i] + suf[i]);
    for (i = 2; i <= N - 1; ++i) {
        mn = min(D[i], mn);
        st.erase(st.find(-D[i] + suf[i]));
        ll cost1 = max(0ll, -mn + pre[i]);
        ll cost2 = max(0ll, *st.rbegin());
        ans = max(ans, cost1 + cost2);
    }

    return ans;
}

ll solve_2() {
    int i;
    ll ans = 0;
    multiset<ll> st, st2;
    for (i = 3; i <= N; ++i) {
        st2.insert(-D[i] + suf[i]);
    }

    for (i = 1; i <= N - 2; ++i) {
        st.insert(suf[i] - D[i]);
        ll cost1 = max(0ll, *st.rbegin() - A[i+1]);
        cost1 = max(cost1, *st2.rbegin());
        st2.erase(st2.find(suf[i+2] - D[i+2]));
        ans = max(ans, cost1 + max(0ll, A[i+1] - D[i+1]));
    }

    return ans;
}

ll solve_3() {
    ll ans = 0;
    int i;
    for (i = 2; i <= N; ++i) {
        ans = max(ans, -D[i] + suf[i]);
    }
    ans += max(0ll, -D[1] + A[1]);
    ans = max(ans, -D[1] + A[1] + A[N]);
    return ans;
}


int main() {
    int i;
    ll ans = 0;
    scanf("%d%d", &N, &K);
    for (i = 1; i <= N; ++i) {
        scanf("%I64d", &A[i]);
        pre[i] = pre[i-1] + A[i];
    }
    for (i = 1; i <= N; ++i) scanf("%I64d", &D[i]);
    for (i = N; i >= 1; --i) suf[i] = suf[i+1] + A[i];
    if (K == 0) {
        for (i = 1; i <= N; ++i) {
            ans = max(ans, -D[i] + suf[i]);
        }
    } else if (K >= 2) {
        for (i = 1; i <= N - 1; ++i) {
            ans = max(ans, -D[i] + suf[1]);
        }
        ans = max(ans, -D[N] + A[N]);
    } else {
        ans = max(ans, solve_1());
        ans = max(ans, solve_2());
        ans = max(ans, solve_3());
    }
    printf("%I64d\n", ans);
    return 0;
}