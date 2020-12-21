#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll up = 1e18;
ll K;
vector<int> p1, p2;
vector<ll> vc1, vc2;
int N;

bool ok(ll v1, ll v2) {
    return v1 <= up / v2;
}

void gen(vector<int> &p, vector<ll> &ret, int idx, ll num) {
    int i;
    ret.push_back(num);
    if (idx >= (int) p.size()) return;
    for (i = 0 ; i < 64; ++i) {
        gen(p, ret, idx + 1, num);
        if (ok(num, p[idx])) {
            num = num * p[idx];
        } else {
            break;
        }
    }
}

ll cnt(ll val) {
    ll ret = 0;
    int i, j, sz1 = vc1.size(), sz2 = vc2.size();
    for (i = 0, j = sz2 - 1; i < sz1; ++i) {
        while (j >= 0 && (!ok(vc1[i], vc2[j]) || vc1[i] * vc2[j] > val)) {
            j--;
        }

        ret = ret + j + 1;
    }

    return ret;
}

int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        int v;
        scanf("%d", &v);
        if (i % 2 == 1) {
            p1.push_back(v);
        } else {
            p2.push_back(v);
        }
    }

    gen(p1, vc1, 0, 1);
    gen(p2, vc2, 0, 1);
    sort(vc1.begin(), vc1.end());
    vector<ll>::iterator it;
    it = unique(vc1.begin(), vc1.end());   
    vc1.resize(distance(vc1.begin(),it));
    sort(vc2.begin(), vc2.end());
    it = unique(vc2.begin(), vc2.end());   
    vc2.resize(distance(vc2.begin(),it));
    scanf("%I64d", &K);
    ll low = 1, high = up, ans = 1;
    while (low <= high) {
        ll mid = (low + high) / 2;
        if (cnt(mid) >= K) {
            high = mid - 1;
            ans = mid;
        } else {
            low = mid + 1;
        }
    }
    // cout << cnt(8) << endl;
    printf("%I64d\n", ans);
    return 0;
}