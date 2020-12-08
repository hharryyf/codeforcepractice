#include <bits/stdc++.h>
#define MAX_SIZE 257
typedef long long ll;
using namespace std;

const ll mod = 19260817, base = 10007;
ll pw[MAX_SIZE];
char st[MAX_SIZE][MAX_SIZE];
int bt[MAX_SIZE][MAX_SIZE];
ll p[MAX_SIZE][MAX_SIZE];
int N, M;

int manchester(vector<int> &s) {
    int n = s.size();
    /*cout << "calculate ";
    for (auto ch : s) {
        cout << ch << " ";
    }
    cout << endl;*/
    vector<int> d1(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
            k++;
        }
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }

    vector<int> d2(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
            k++;
        }
        d2[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k ;
        }
    }

    int ret = 0;
    for (int i = 0 ; i < n; ++i) {
        if (s[i] >= 0) {
            ret += d1[i];
        }
    }
    for (int i = 0; i < n; ++i) {
        if (s[i] >= 0) {
            ret += d2[i];
        }
    }

    // cout << "get " << ret << endl; 
    return ret;
}

int main() {
    int i, j, k;
    scanf("%d%d", &N, &M);
    pw[0] = 1;
    for (i = 1; i < MAX_SIZE; ++i) {
        pw[i] = pw[i-1] * base;
        pw[i] %= mod;
    }

    for (i = 1; i <= N; ++i) {
        scanf("%s", st[i] + 1);
        for (j = 1; j <= M; ++j) {
            bt[i][j] = bt[i][j-1] ^ (1 << (st[i][j] - 'a'));
            p[i][j] = p[i][j-1] + pw[st[i][j] - 'a'];
            p[i][j] %= mod;
        }
    }

    ll ans = 0;
    for (j = 1; j <= M; ++j) {
        for (k = 1; k <= j; ++k) {
            vector<int> s(N);
            int tol = -1;
            for (i = 1; i <= N; ++i) {
                s[i-1] = p[i][j] - p[i][k-1];
                s[i-1] %= mod;
                if (s[i-1] < 0) s[i-1] += mod;
                if (__builtin_popcount(bt[i][j] ^ bt[i][k-1]) > 1) s[i-1] = tol--; 
            }

            ans = ans + manchester(s);
        }
    }

    printf("%I64d\n", ans);
    return 0;
}