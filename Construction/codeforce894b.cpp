#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll mod = 1e9 + 7;

ll fastpower(ll p) {
    ll base = 2;
    ll ret = 1;
    while (p > 0) {
        if (p % 2 == 0) {
            base = (base * base) % mod;
            p /= 2;
        } else {
            ret = ret * base;
            ret %= mod;
            --p;
        }
    }
    return ret;
}

int main() {
    ll n, m;
    int num;
    cin >> n >> m >> num;
    if (num == -1 && n % 2 != m % 2) {
        cout << 0 << endl;
        return 0;
    }


    cout << fastpower(((n - 1) % (mod - 1)) * ((m - 1) % (mod - 1))) % mod << endl;
    return 0;
}