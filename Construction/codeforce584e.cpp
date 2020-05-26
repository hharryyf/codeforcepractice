#include <bits/stdc++.h>
#define MAX_SIZE 2011
using namespace std;

int p[MAX_SIZE], s[MAX_SIZE];
int target[MAX_SIZE];
vector<pair<int, int>> oper;

int main() {
    int i, j, n;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &p[i]);
    }

    for (i = 1; i <= n; ++i) {
        scanf("%d", &s[i]);
        target[s[i]] = i;
    }

    int ans = 0;
    for (i = 1; i <= n; ++i) {
        if (s[i] == p[i]) continue;
        int pos = i;
        for (j = i + 1; j <= n; ++j) {
            if (p[j] == s[i]) {
                pos = j;
                break;
            }
        }
       
        for (j = pos - 1; j >= i; --j) {
            if (target[p[j]] >= pos) {
                // cout << p[j] << " " << target[p[j]] << endl;
                swap(p[j], p[pos]);
                ans += pos - j;
                oper.emplace_back(pos, j);
                pos = j;
            }
        }
    }

    printf("%d\n%d\n", ans, (int) oper.size());
    for (auto v : oper) {
        printf("%d %d\n", v.first, v.second);
    }   
    return 0;
}