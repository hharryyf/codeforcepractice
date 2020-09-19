#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 1031
using namespace std;
typedef long long ll;

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        ll n;
        ll cnt = 0;
        cin >> n;
        for (int i = 0; i <= 62; ++i) {
            cnt += n / (1ll << i);
        }

        cout << cnt << endl;
    }
    return 0;
}