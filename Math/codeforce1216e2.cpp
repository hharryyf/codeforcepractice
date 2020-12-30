#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll num[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
ll cost(ll val) {
    int i;
    ll ret = 0;
    for (i = 0 ; i < 9; ++i) {
        if (num[i+1] <= val) {
            ret = ret + 1ll * (i + 1) * (num[i+1] - num[i]) * (val + 1);
            ret = ret - 1ll * (i + 1) * (num[i+1] + num[i] - 1) * (num[i+1] - num[i]) / 2;
        } else {
            ret = ret + 1ll * (i + 1) * (val - num[i] + 1) * (val + 1);
            ret = ret - 1ll * (i + 1) * (val - num[i] + 1) * (val + num[i]) / 2;
            break;
        }
    }

    return ret;
}

ll cost2(ll val) {
    int i;
    ll ret = 0;
    for (i = 0 ; i < 9; ++i) {
        if (num[i+1] <= val) {
            ret = ret + 1ll * (i + 1) * (num[i+1] - num[i]);
        } else {
            ret = ret + 1ll * (i + 1) * (val - num[i] + 1);
            break;
        }
    }
    return ret;
}

int main() {
    int T;
    scanf("%d", &T); 
    while (T-- > 0) {
        ll N;
        cin >> N;
        ll low = 1, high = 800000000, chunk = 1;
        while (low <= high) {
            ll mid = (low + high) / 2;
            if (cost(mid) <= N) {
                low = mid + 1;
                chunk = mid;
            } else {
                high = mid - 1;
            }
        }

        N = N - cost(chunk);
        if (N == 0) {
            printf("%I64d\n", chunk % 10);
            continue;
        }

        low = 1, high = chunk + 1;
        ll ret = 1;
        while (low <= high) {
            ll mid = (low + high) / 2;
            if (cost2(mid) <= N) {
                low = mid + 1;
                ret = mid;
            } else {
                high = mid - 1;
            }
        }

        N = N - cost2(ret);
        if (N == 0) {
            printf("%I64d\n", ret % 10);
            continue;
        }
        // cout << "! " << N << " " << ret << endl;
        string s = to_string(ret + 1);
        printf("%c\n", s[N - 1]);
    }
    return 0;
}