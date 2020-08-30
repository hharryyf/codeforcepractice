#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 200111
using namespace std;
typedef long long ll;

struct rolling_hash {
    ll val[MAX_SIZE];
    ll ep[MAX_SIZE];
    ll mod = 1e9 + 7;
    int base = 41;
    int N;
    void init(int base=41, ll mod=1e9+7) {
        int i;
        this->base = base, this->mod = mod;
        ep[0] = 1;
        for (i = 1; i < MAX_SIZE; ++i) {
            ep[i] = ep[i-1] * base;
            ep[i] %= mod; 
        }
    }

    void calc(char st[], int N) {
        this->N = N;
        for (int i = 1 ; i <= N; ++i) {
            val[i] = val[i-1] * base + (st[i] - 'a');
            val[i] %= mod;
        }
    }

    ll decode(int l, int r) {
        ll valL = val[l-1] * ep[r - l + 1];
        ll valR = val[r];
        return ((valR - valL) % mod + mod) % mod;
    }

    bool equal(int l1, int r1, int l2, int r2) {
        if (r1 - l1 != r2 - l2) return false;
        return decode(l1, r1) == decode(l2, r2);
    }
};

rolling_hash h[26][2];

char st[MAX_SIZE];
char tmp[MAX_SIZE];
int nxt[MAX_SIZE][26];
pair<int, int> ord[26];
vector<pair<ll, ll>> gen(int l, int r) {
    int i;
    vector<pair<ll, ll>> ret;
    for (i = 0; i < 26; ++i) {
        ord[i].first = nxt[l][i];
        ord[i].second = i;
    }

    sort(ord, ord + 26);
    for (i = 0 ; i < 26; ++i) {
        if (ord[i].first <= r) {
            ret.emplace_back(h[ord[i].second][0].decode(l, r), h[ord[i].second][1].decode(l, r));
        }
    }
    return ret;
}

int main() {
    int i, j, N, Q;
    scanf("%d%d", &N, &Q);
    scanf("%s", st + 1);
    for (j = 0 ; j < 26; ++j) {
        for (i = 1 ; i <= N; ++i) {
            if (st[i] == j + 'a') {
                tmp[i] = 'b';
            } else {
                tmp[i] = 'a';
            }
        }

        h[j][0].init();
        h[j][1].init(33, 19260817);
        h[j][0].calc(tmp, N);
        h[j][1].calc(tmp, N);
    }

    for (i = N; i >= 1; --i) {
        for (j = 0 ; j < 26; ++j) {
            if (st[i] == 'a' + j) {
                nxt[i][j] = i;
            } else {
                if (i == N) {
                    nxt[i][j] = N + 1;
                } else {
                    nxt[i][j] = nxt[i+1][j];
                }
            }
        }
    }

    while (Q-- > 0) {
        int l, r, len;
        scanf("%d%d%d", &l, &r, &len);
        // [l, l + len - 1]
        // [r, r + len - 1]
        auto v1 = gen(l, l + len - 1);
        auto v2 = gen(r, r + len - 1);
        printf("%s\n", v1 == v2 ? "YES" : "NO");
    }
    return 0;
}