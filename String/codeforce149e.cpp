#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

char st[MAX_SIZE], q[1011];
int pre[1011], suf[1011];

vector<int> z_function(vector<char> &s) {
    int n = (int) s.size();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

vector<char> s;
vector<int> idx;

void solve_forward() {
    int i;
    int len = strlen(st), len2 = strlen(q);
    s = vector<char>(len + len2 + 1, 0);
    idx = vector<int>(len + len2 + 1, 0);
    for (i = 0 ; i < 1011; ++i) pre[i] = 201011;
    for (i = 0 ; i < len2; ++i) {
        s[i] = q[i];
        idx[i] = -1;
    }

    s[len2] = '#';
    idx[len2] = -1;
    for (i = 0 ; i < len; ++i) {
        s[i + len2 + 1] = st[i];
        idx[i + len2 + 1] = i;
    }

    vector<int> z = z_function(s);
    for (i = 0 ; i < (int) z.size(); ++i) {
        if (idx[i] != -1) {
            pre[z[i]] = min(idx[i], pre[z[i]]);
        }
    }

    for (i = len2; i >= 0; --i) {
        pre[i] = min(pre[i], pre[i+1]);
    }
}

void solve_back() {
    int i;
    int len = strlen(st), len2 = strlen(q);
    s = vector<char>(len + len2 + 1, 0);
    idx = vector<int>(len + len2 + 1, 0);
    for (i = 0 ; i < 1011; ++i) suf[i] = -1;
    for (i = 0 ; i < len2; ++i) {
        s[i] = q[len2 - i - 1];
        idx[i] = -1;
    }

    s[len2] = '#';
    idx[len2] = -1;
    for (i = 0 ; i < len; ++i) {
        s[i + len2 + 1] = st[len - i - 1];
        idx[i + len2 + 1] = len - i - 1;
    }

    vector<int> z = z_function(s);
    for (i = 0 ; i < (int) z.size(); ++i) {
        if (idx[i] != -1) {
            suf[z[i]] = max(idx[i], suf[z[i]]);
        }
    }

    for (i = len2; i >= 0; --i) {
        suf[i] = max(suf[i], suf[i+1]);
    }
}

int solve() {
    solve_forward();
    solve_back();
    int i, len = strlen(q);/*
    for (i = 0; i <= len; ++i) {
        cout << pre[i] << " " << suf[i] << endl;
    }*/
    for (i = 1; i <= len - 1; ++i) {
        int p1 = pre[i], p2 = suf[len - i];
        if (p2 - p1 + 1 >= len) {
            return 1;
        }
    }

    return 0;
}

int main() {
    scanf("%s", st);
    int T, ans = 0;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%s", q);
        ans = ans + solve();
    }

    printf("%d\n", ans);
    return 0;
}