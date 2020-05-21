
#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll mod = 1e9 + 7;

ll mul(ll v1, ll v2) {
    return (v1 * v2) % mod;
}

int main() {
    int w, h, i, j;
    ll ans = 0;
    cin >> w >> h;
    // firstly, get all triangles with area = X
    // twice the expression is |(x1 - x) * (y2 - y) - (y1 - y) * (x2 - x)|
    // we should get the number of such combinations that are even
    int x,y, x1, x2, y1, y2; 
    int oddx = w / 2 + (w % 2);
    int evenx = w - oddx + 1;
    int oddy = h / 2 + (h % 2);
    int eveny = h - oddy + 1;
    int X[2] = {evenx, oddx};
    int Y[2] = {eveny, oddy};
    // cout << X[0] << " " << X[1] << " " << Y[0] << " "<< Y[1] << endl;
    for (x = 0 ; x < 2; ++x) {
        for (y = 0 ; y < 2; ++y) {
            for (x1 = 0 ; x1 < 2; ++x1) {
                for (y1 = 0 ; y1 < 2; ++y1) {
                    for (x2 = 0 ; x2 < 2; ++x2) {
                        for (y2 = 0 ; y2 < 2; ++y2) {
                            int a = abs((x1 - x) * (y2 - y) - (y1 - y) * (x2 - x));
                            if (a % 2 == 0) {
                                ans += mul(mul(mul(X[x], X[x1]), X[x2]), mul(mul(Y[y], Y[y1]), Y[y2]));              
                                ans %= mod;
                            }
                        }
                    }
                }
            }
        }
    }
    
    // secondly, we eliminate all triangles with area
    for (i = 0; i <= w; ++i) {
        for (j = 0; j <= h; ++j) {
            if (i == 0 && j == 0) {
                ans = ans - (w - i + 1) * (h - j + 1);
            } else if (i == 0 || j == 0) {
                ans = ans - mul((w - i + 1) * (h - j + 1), __gcd(i, j) * 6);
            } else {
                // the number of increment here is (w-i+1) * (h-j+1) * (gcd(i, j) - 1) * 12
                ans = ans - mul((w - i + 1) * (h - j + 1), __gcd(i, j) * 12);
            }
            ans %= mod;
            if (ans < 0) ans += mod;
        }
    }
    cout << mul(ans, 1) << endl;
    return 0;
}