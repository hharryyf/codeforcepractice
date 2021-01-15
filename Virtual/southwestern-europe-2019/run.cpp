#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll f(ll v) {
    return (v + v / 1048576 + 12345) % (1ll << 40);
}

pair<ll, ll> cycle() {
    ll s0 = 1611516670;
    ll tortoise = f(s0), hare = f(tortoise);
    while (tortoise != hare) {
        tortoise = f(tortoise);
        hare = f(f(hare));
    }
    ll mu = 0;
    tortoise = s0;
    while (tortoise != hare) {
        tortoise = f(tortoise);
        hare = f(hare);
        mu += 1;
    }
    ll lam = 1;
    hare = f(tortoise);
    while (tortoise != hare) {
        hare = f(hare);
        lam += 1;
    }
 
    return make_pair(lam, mu);

}

int main() {
    auto p = cycle();
    cout << p.first << " " << p.second << endl;
    return 0;
}