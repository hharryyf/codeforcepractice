#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;

string st[MAX_SIZE];
list<char> lst;
char ss[MAX_SIZE * MAX_SIZE];

int main() {
    int i, n, l, k, j;
    scanf("%d%d%d", &n, &l, &k);
    scanf("%s", ss + 1);
    sort(ss + 1, ss + 1 + n * l);
    for (i = 1; i <= n * l; ++i) {
        lst.push_back(ss[i]);
    }

    // sort(lst.begin(), lst.end());

    for (i = 1; i <= k; ++i) {
        st[i] += lst.front();
        lst.pop_front();
    }

    int current = 1;
    for (i = 2; i <= l; ++i) {
        while (current < k) {
            if (st[current].back() < st[k].back()) {
                current++;
            } else {
                break;
            }
        }

        for (j = current; j <= k; ++j) {
            st[j] += lst.front();
            lst.pop_front();
        }
    }

    for (i = 1; i <= n; ++i) {
        while ((int) st[i].length() < l) {
            st[i] += lst.front();
            lst.pop_front();
        }
    }

    sort(st + 1, st + 1 + n);

    for (i = 1; i <= n; ++i) {
        printf("%s\n", st[i].data());
    }
    return 0;
}