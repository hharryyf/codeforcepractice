#include <bits/stdc++.h>
#define MAX_SIZE 1000111
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

char st[MAX_SIZE];
int best[MAX_SIZE];
int ans[MAX_SIZE];
int N;
rolling_hash h1, h2;


int main() {
    int i;
    scanf("%d", &N);
    scanf("%s", st + 1);
    h1.init(29, 19260817);
    h2.init();
    h1.calc(st, N);
    h2.calc(st, N);
    for (i = 1; i <= N / 2; ++i) {
        // centre at i
        best[i] = -1;
        if (st[i] != st[N - i + 1]) continue;
        int low = 0, high = i - 1;
        while (low <= high) {
            int mid = (low + high) >> 1;
            int l1 = i - mid, r1 = i + mid;
            int l2 = N - i + 1 - mid, r2 =  N - i + 1 + mid;
            if (h1.equal(l1, r1, l2, r2) && h2.equal(l1, r1, l2, r2)) {
                best[i] = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }

    for (i = 1; i <= N / 2; ++i) {
        if (best[i] != -1) {
            ans[i - best[i]] = max(ans[i - best[i]], 2 * best[i] + 1);
        }
    }

    for (i = 1; i <= N / 2; ++i) {
        ans[i] = max(ans[i], ans[i - 1] - 2);
    }

    for (i = 1; i <= (N + 1) / 2; ++i) {
        printf("%d ", ans[i] > 0 ? ans[i] : -1);
    }
    printf("\n");
    return 0;
}