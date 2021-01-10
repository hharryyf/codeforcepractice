#include <bits/stdc++.h>
#define MAX_SIZE 2511
typedef long long ll;
using namespace std;
const int mod = 1000000007;
struct oper {
    int tp, idx;
    ll l, r;
};

oper q[MAX_SIZE];
ll sz[MAX_SIZE];
char st[MAX_SIZE], op[5];
int pre[MAX_SIZE];
int N, len;
map<pair<ll, ll>, int> memo[MAX_SIZE];

int add(int v, int u) {
    int ret = (v + u) % mod;
    if (ret < 0) ret += mod;
    return ret;
}

int solve(int idx, ll l, ll r) {
    if (idx == 0) return pre[r] - (l != 0 ? pre[l-1] : 0);
    if (memo[idx].count(make_pair(l, r))) return memo[idx][make_pair(l, r)];
    int ret = 0;
    if (q[idx].tp == 1) {
        if (l < sz[(int) q[idx].l]) ret = solve((int) q[idx].l, l, min(sz[(int) q[idx].l] - 1, r));
        if (r >= sz[(int) q[idx].l]) ret = add(ret, solve((int) q[idx].r, max(0ll, l - sz[(int) q[idx].l]), r - sz[(int) q[idx].l]));
    } else {
        ret = solve(q[idx].idx, l + q[idx].l, r + q[idx].l);
    }
    return memo[idx][make_pair(l, r)] = ret;
}

int main() {
    int i;
    scanf("%d", &N);
    scanf("%s", st);
    len = strlen(st);
    for (i = 0 ; i < len; ++i) {
        pre[i] = (int) st[i];
        if (i != 0) pre[i] += pre[i-1];
    }

    sz[0] = len;
    for (i = 1 ; i < N; ++i) {
        scanf("%s", op);
        if (op[0] == 'A') {
            scanf("%I64d%I64d", &q[i].l, &q[i].r);
            q[i].tp = 1;
            sz[i] = sz[(int)q[i].l] + sz[(int)q[i].r];
        } else {
            scanf("%d%I64d%I64d", &q[i].idx, &q[i].l, &q[i].r);
            sz[i] = q[i].r - q[i].l;
            q[i].r--;
        }
    }

    printf("%d\n", (solve(N - 1, 0, sz[N - 1] - 1) + mod) % mod);
    return 0;
}