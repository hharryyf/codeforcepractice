#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    int n;
    ll k;
    cin >> n >> k;
    if (k > 1ll * n * (n-1) / 2) {
        cout << "Impossible" << endl;
        return 0;
    }

    int i = 0;
    ll len = 0;
    string ret = "";
    while (len + i <= k) {
        ret += '(';
        len += i;
        i++;
    }

    ll pos = k - len;
    // cout << pos << endl;
    while (i > 0) {
        ret += ')';
        i--;
        if (i > 0 && i == pos) {
            ret += "()";
        }
    }

    len = (int) ret.length();
    while (len < 2 * n) {
        ret += "()";
        len += 2;
    }

    cout << ret << endl;
    return 0;
}