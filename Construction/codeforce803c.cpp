#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ll n, k, i;
    cin >> n >> k;
    if (k > 1000000) {
        printf("-1\n");
        return 0;
    }
    int g = n * 2 / (k * (k + 1));
    if (g == 0) {
        printf("-1\n");
        return 0;
    }

    ll h = 1;
    for (i = 1; i <= sqrt(n); ++i) {
        if (n % i == 0) {
            if (i <= g) {
                h = max(i, h);
            } 
            
            if (n / i <= g) {
                h = max(h, n / i);
            }
        }
    }

    g = h;
    for (i = 1; i < k; ++i) {
        cout << g * i << " ";
        n -= g * i;
    }
    cout << n << endl;
    return 0;
}