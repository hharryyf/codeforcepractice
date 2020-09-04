#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 2001111
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
            val[i] = val[i-1] * base + (st[i] - 'a' + 1);
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

rolling_hash h1, h2;

ll calc(char st[], int base, ll mod) {
    int n = strlen(st);
    ll ret = 0;
    for (int i = 0; i < n; ++i) {
        ret = ret * base + (st[i] - 'a' + 1);
        ret %= mod;
    }
    return ret;
}

char s[MAX_SIZE];
set<pair<pair<ll, ll>, int>> S;
vector<pair<pair<ll, ll>, int>> history;

int main() {
    int n, k, g, i, j, l, r;
    int mod1 = 1e9 + 7, elder = 19260817;
    scanf("%d%d", &n, &k);   
    h1.init(), h2.init(33, elder);
    scanf("%s", s+1);
    for (i = 1; i <= n * k; ++i) {
        s[i+n*k] = s[i];
    }
    h1.calc(s, 2 * n * k);
    h2.calc(s, 2 * n * k);
    scanf("%d", &g);
    for (i = 0 ; i < g; ++i) {
        scanf("%s", s);
        S.insert(make_pair(make_pair(calc(s, 41, mod1), calc(s, 33, elder)), i+1));
    }

    for (i = 1; i <= k; ++i) {
        history.clear();
        bool valid = true;
        // cout << "start at " << i << endl;
        for (j = 1; j <= n; ++j) {
            l = i + (j - 1) * k, r = i + j * k - 1;
            ll v1 = h1.decode(l, r), v2 = h2.decode(l, r);
            auto iter = S.lower_bound(make_pair(make_pair(v1, v2), -1));
            if (iter == S.end() || iter->first != make_pair(v1, v2)) {
                // cout << "find at " << j << " fails " << endl; 
                valid = false;
                break;
            }
            history.push_back(*iter);
            // cout << iter->first.first << " " << iter->first.second << " id= " << iter->second << endl;
            S.erase(*iter);
        }

        if (!valid) {
            for (auto p : history) {
                S.insert(p);
            }
        } else {
            printf("YES\n");
            for (auto p : history) {
                printf("%d ", p.second);
            }
            return 0;
        }
    }

    printf("NO\n");
    return 0;
}