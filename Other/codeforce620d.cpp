#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 2011
using namespace std;

vector<ll> s1, s2;
pair<int, int> c1[MAX_SIZE * MAX_SIZE], c2[MAX_SIZE * MAX_SIZE];
ll a[MAX_SIZE], b[MAX_SIZE];
ll tmp[MAX_SIZE * MAX_SIZE];
int tol = 0;
int n, m;

int main() {
    int i, j;
    scanf("%d", &n);
    for (i = 0 ; i < n; ++i) scanf("%I64d", &a[i]);
    scanf("%d", &m);
    for (i = 0 ; i < m; ++i) scanf("%I64d", &b[i]);
    ll sa = 0, sb = 0;
    int tp = 0;
    ll v1 = 0, v2 = 0;
    for (i = 0 ; i < n; ++i) sa += a[i];
    for (i = 0 ; i < m; ++i) sb += b[i];
    ll ans = llabs(sa - sb);
    for (i = 0 ; i < n; ++i) {
        for (j = 0 ; j < m; ++j) {
            if (ans > llabs((sa - a[i] + b[j]) - (sb - b[j] + a[i]))) {
                ans = llabs((sa - a[i] + b[j]) - (sb - b[j] + a[i]));
                tp = 1;
                v1 = a[i], v2 = b[j];
            }
        }
    }

    for (i = 0 ; i < n; ++i) {
        for (j = 0 ; j < i; ++j) {
            tmp[tol++] = a[i] + a[j];
        }
    }

    sort(tmp, tmp + tol);
    for (i = 0 ; i < tol; ++i) {
        if (i == 0 || tmp[i] != tmp[i-1]) s1.push_back(tmp[i]);
    }

    tol = 0;
    for (i = 0 ; i < m; ++i) {
        for (j = 0 ; j < i; ++j) {
            tmp[tol++] = b[i] + b[j];
        }
    }

    sort(tmp, tmp + tol);
    for (i = 0 ; i < tol; ++i) {
        if (i == 0 || tmp[i] != tmp[i-1]) s2.push_back(tmp[i]);
    }
    
    int sz = s2.size();
    for (auto v : s1) {
        // sa - v + u, sb + v - u
        ll dif = sb + v - (sa - v);
        int idx = lower_bound(s2.begin(), s2.end(), dif / 2) - s2.begin();
        if (idx < sz) {
            if (ans > llabs(sb - sa + v * 2 - s2[idx] * 2)) {
                ans = llabs(sb - sa + v * 2 - s2[idx] * 2);
                tp = 2;
                v1 = v, v2 = s2[idx];
            }
        }

        if (idx + 1 < sz) {
            if (ans > llabs(sb - sa + v * 2 - s2[idx + 1] * 2)) {
                ans = llabs(sb - sa + v * 2 - s2[idx + 1] * 2);
                tp = 2;
                v1 = v, v2 = s2[idx + 1];
            }
        }

        if (idx - 1 >= 0) {
            if (ans > llabs(sb - sa + v * 2 - s2[idx - 1] * 2)) {
                ans = llabs(sb - sa + v * 2 - s2[idx - 1] * 2);
                tp = 2;
                v1 = v, v2 = s2[idx - 1];
            }
        }
    }

    printf("%I64d\n", ans);
    if (tp == 0) {
        printf("0\n");
    } else if (tp == 1) {
        printf("1\n");
        int i1 = 0, i2 = 0;
        for (i = 0 ; i < n; ++i) {
            if (a[i] == v1) {
                i1 = i;
                break;
            }
        }

        for (i = 0 ; i < m; ++i) {
            if (b[i] == v2) {
                i2 = i;
                break;
            }
        }

        printf("%d %d\n", i1 + 1, i2 + 1);
    } else {
        printf("2\n");
        int i1 = 0, i2 = 0, i3 = 0, i4 = 0;
        for (i = 0 ; i < n; ++i) {
            for (j = 0 ; j < i; ++j) {
                if (a[i] + a[j] == v1) {
                    i1 = i, i2 = j;
                    break;
                }
            }
        }

        for (i = 0 ; i < m; ++i) {
            for (j = 0 ; j < i; ++j) {
                if (b[i] + b[j] == v2) {
                    i3 = i, i4 = j;
                    break;
                }
            }
        }

        printf("%d %d\n%d %d\n", i1 + 1, i3 + 1, i2 + 1, i4 + 1);
    }
    return 0;
}