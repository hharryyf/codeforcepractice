#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define MAX_SIZE 1000011

int a[MAX_SIZE];

int find(ll v) {
    int i, ret = -1;
    for (i = 1; i <= 2 * sqrt(v) + 1; ++i) {
        if (1ll * i * (i-1) / 2 >= v) {
            ret = i;
            break;
        }
    }

    if (ret == -1 || 1ll * ret * (ret - 1) / 2 != v) return -1;
    return ret;
}

int main() {
    ll a00, a01, a10, a11;
    cin >> a00 >> a01 >> a10 >> a11;
    if (a00 + a01 + a10 + a11 == 0) {
        printf("0\n");
        return 0;
    }

    ll n = find(a00 + a01 + a10 + a11);
    ll n0 = find(a00), n1 = find(a11); 
    if (a00 == 0 && a01 == 0 && a10 == 0) {
        n0 = 0;
    }

    if (a11 == 0 && a01 == 0 && a10 == 0) {
        n1 = 0;
    }

    // cout << n0 << " " << n1 << " " << n << endl;
    if (n0 == -1 || n1 == -1 || n == -1 || n0 + n1 != n) {
        printf("Impossible\n");
        return 0;
    }

    int i = 1;
    while (n0 > 0 && n1 > 0)  {
        if (a01 >= n1) {
            a[i++] = 0;
            a01 -= n1;
            n0++;
        } else {
            a[i++] = 1;
            n1--;
        }
    }

    if (a01 != 0) {
        printf("Impossible\n");
        return 0;
    }

    while (n0 > 0) {
        a[i++] = 0;
        n0--;
    }

    while (n1 > 0) {
        a[i++] = 1;
        n1--;
    }

    for (i = 1; i <= (int) n; ++i) {
        printf("%d", a[i]);
    }
    printf("\n");
    return 0;
}