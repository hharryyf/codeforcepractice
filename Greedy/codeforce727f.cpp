#include <bits/stdc++.h>
#define MAX_SIZE 752
typedef long long ll;
using namespace std;

ll f[MAX_SIZE], q[MAX_SIZE * MAX_SIZE], a[MAX_SIZE];
int N, Q;

bool check(ll curr, int rmv) {
    priority_queue<ll> st;
    int i, cnt = 0;
    for (i = 1; i <= N; ++i) {
        curr += a[i];
        if (a[i] < 0) st.push(-a[i]);
        if (curr < 0) {
            curr += st.top();
            st.pop(); 
            cnt++;
        }
    }

    return cnt <= rmv;
}
// find the minimum Q such that maximum remove = rmv
ll solve(int rmv) {
    ll low = 0, high = 1e15;
    ll ans = 1e15;
    while (low <= high) {
        ll mid = (low + high) / 2;
        if (check(mid, rmv)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return ans;
}

int main() {
    int i;
    scanf("%d%d", &N, &Q);
    for (i = 1; i <= N; ++i) scanf("%I64d", &a[i]);
    for (i = 1; i <= Q; ++i) scanf("%I64d", &q[i]);
    for (i = 0 ; i <= N; ++i) {
        f[i] = solve(i);
    }

    for (i = 1; i <= Q; ++i) {
        int low = 0, high = N, ans = N;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (f[mid] <= q[i]) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        printf("%d\n", ans);
    }   
    return 0;
}