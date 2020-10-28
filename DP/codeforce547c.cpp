#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;
typedef long long ll;
vector<int> prime;
int visited[711];
int a[MAX_SIZE];
int cnt[MAX_SIZE << 3];
int tol = 0;
ll ans;
int n, q;

void init() {
    int i, j;
    for (i = 2; i <= 707; ++i) {
        if (visited[i]) continue;
        prime.push_back(i);
        for (j = 1; j * i <= 707; ++j) {
            visited[i * j] = 1;
        }
    }
}

void upd(vector<int> &vc, int v) {
    int sz = vc.size(), i, j;
    for (i = 1; i < (1 << sz); ++i) {
        int mul = 1;
        for (j = 0 ; j < sz; ++j) {
            if ((1 << j) & i) {
                mul *= vc[j];
            }
        }

        if (mul > 1) {
            cnt[mul] += v;
        }
    }
}

void add(int num) {
    tol++;
    vector<int> fac;
    int i, j;
    for (auto p : prime) {
        if (num % p == 0) {
            fac.push_back(p);
            while (num % p == 0) num /= p;
        }
    }

    if (num > 1) fac.push_back(num);

    int sz = fac.size();
    for (i = 1; i < (1 << sz); ++i) {
        int bt = __builtin_popcount(i);
        int mul = 1;
        for (j = 0 ; j < sz; ++j) {
            if ((1 << j) & i) {
                mul *= fac[j];
            }
        }

        if (mul > 1) {
            if (bt % 2 == 1) {
                ans += cnt[mul];
            } else {
                ans -= cnt[mul];
            }
        }
    }
    
    upd(fac, 1);
}

void del(int num) {
    tol--;
    vector<int> fac;
    int i, j;
    for (auto p : prime) {
        if (num % p == 0) {
            fac.push_back(p);
            while (num % p == 0) num /= p;
        }
    }

    if (num > 1) fac.push_back(num);
    upd(fac, -1);
    int sz = fac.size();
    for (i = 1; i < (1 << sz); ++i) {
        int bt = __builtin_popcount(i);
        int mul = 1;
        for (j = 0 ; j < sz; ++j) {
            if ((1 << j) & i) {
                mul *= fac[j];
            }
        }

        if (mul > 1) {
            if (bt % 2 == 1) {
                ans -= cnt[mul];
            } else {
                ans += cnt[mul];
            }
        }
    }
}

int main() {
    int i;
    init();
    scanf("%d%d", &n, &q);
    for (i = 1; i <= n; ++i) scanf("%d", &a[i]);
    while (q-- > 0) {
        int v;
        scanf("%d", &v);
        if (a[v] > 0) {
            add(a[v]);
        } else {
            del(-a[v]);
        }
        a[v] *= -1;
        printf("%I64d\n", 1ll * tol * (tol - 1) / 2 - ans);
    }
    return 0;
}