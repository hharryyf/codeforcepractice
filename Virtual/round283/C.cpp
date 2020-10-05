#include <bits/stdc++.h>
#define MAX_SIZE 111
typedef long long ll;
using namespace std;

vector<int> rem;
char st[MAX_SIZE][MAX_SIZE];
int n, m;

bool valid() {
    int sz = rem.size(), i, j;
    for (j = 0 ; j < n - 1; ++j) {
        string s1, s2;
        for (i = 0 ; i < sz; ++i) {
            s1 += st[j][rem[i]], s2 += st[j+1][rem[i]];
        }

        if (s1 > s2) return false;
    }
    // cout << "ok" << endl;
    return true;
}

int main() {
    int i;
    scanf("%d%d", &n, &m);
    for (i = 0 ; i < n; ++i) {
        scanf("%s", st[i]);
    }

    for (i = 0 ; i < m; ++i) {
        rem.push_back(i);
        if (!valid()) {
            rem.pop_back();
        }
    }

    cout << m - (int) rem.size() << endl;
    return 0;
}