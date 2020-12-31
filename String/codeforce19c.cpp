#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 100111
using namespace std;
typedef long long ll;

struct rolling_hash {
    ll val[MAX_SIZE];
    ll ep[MAX_SIZE];
    ll mod = 1e9 + 9;
    int base = 100011;
    int N;
    void init(int base=100011, ll mod=1e9+9) {
        int i;
        this->base = base, this->mod = mod;
        ep[0] = 1;
        for (i = 1; i < MAX_SIZE; ++i) {
            ep[i] = ep[i-1] * base;
            ep[i] %= mod; 
        }
    }

    void calc(int st[], int N) {
        this->N = N;
        for (int i = 1 ; i <= N; ++i) {
            val[i] = val[i-1] * base + st[i] + 1;
            val[i] %= mod;
        }
    }

    ll decode(int l, int r) {
        ll valL = val[l-1] * ep[r - l + 1];
        ll valR = val[r];
        ll ret = (valR - valL) % mod;
        if (ret < 0) ret += mod;
        return ret;
    }

    bool equal(int l1, int r1, int l2, int r2) {
        if (r1 - l1 != r2 - l2) return false;
        return decode(l1, r1) == decode(l2, r2);
    }
};

rolling_hash h;
int st[MAX_SIZE], N;
vector<int> occ[MAX_SIZE];
int tmp[MAX_SIZE];
vector<int> disc;

int main() {
    int i, j;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &st[i]);
        tmp[i] = st[i];
    }

    sort(tmp + 1, tmp + 1 + N);
    for (i = 1; i <= N; ++i) {
        if (i == 1 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
    }

    for (i = 1; i <= N; ++i) {
        st[i] = lower_bound(disc.begin(), disc.end(), st[i]) - disc.begin();
    }

    h.init(100011, 19260817);
    h.calc(st, N);
    int L = 1, l1, l2, r1, r2;
    for (i = 1; i <= N; ++i) {
        for (j = 0 ; j < (int) occ[st[i]].size(); ++j) {
            l2 = occ[st[i]][j] + 1;
            r2 = i;
            r1 = occ[st[i]][j];
            l1 = r1 - (r2 - l2);
            // cout << l1 << " " << r1 << " " << l2 << " " << r2 << endl;
            if (l1 >= L && h.equal(l1, r1, l2, r2)) {
                L = l2;
            }
        }

        occ[st[i]].push_back(i);
    }

    printf("%d\n", N - L + 1);
    for (i = L; i <= N; ++i) {
        printf("%d ", disc[st[i]]);
    }
    printf("\n");
    return 0;
}