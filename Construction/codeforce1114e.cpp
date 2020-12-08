#include <bits/stdc++.h>
using namespace std;

int checkg(int x) {
    int ret;
    printf("> %d\n", x);
    fflush(stdout);
    scanf("%d", &ret);
    if (ret == -1) exit(0);
    return ret;
}

int main() {
    random_device rd;
    mt19937 mt(rd());
    int ans = 0, N, low = 0, high = 1000000000;
    scanf("%d", &N);
    uniform_int_distribution<int> dist(1, N);
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (checkg(mid)) {
            ans = mid + 1;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    set<int> st;
    for (int i = 0 ; i < 30; ++i) {
        int v = (1ll * dist(mt) * dist(mt)) % N + 1;
        st.insert(v);
    }

    vector<int> vc;
    for (auto v : st) {
        printf("? %d\n", v);
        fflush(stdout);
        int x;
        scanf("%d", &x);
        vc.push_back(x);
    }

    sort(vc.begin(), vc.end());
    vc.push_back(ans);
    int d = 0;
    for (int i = 0 ; i < (int) vc.size(); ++i) {
        d = __gcd(d, ans - vc[i]);
    }

    printf("! %d %d\n", ans - (N - 1) * d, d);
    fflush(stdout);
    return 0;
}