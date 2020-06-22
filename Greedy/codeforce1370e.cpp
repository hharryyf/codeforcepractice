#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;

char s[MAX_SIZE], t[MAX_SIZE];
vector<int> ret;

int main() {
    int n, i, sm = 0;
    scanf("%d", &n);
    scanf("%s", s);
    scanf("%s", t);
    for (i = 0 ; i < n; ++i) {
        if (s[i] == '0' && t[i] == '1') {
            ret.push_back(-1); 
            sm--;
        } else if (s[i] == '1' && t[i] == '0') {
            ret.push_back(1);
            sm++;
        }
    }

    if (sm != 0) {
        printf("-1\n");
        return 0;
    }

    int pos = 0, neg = 0;
    for (auto r : ret) {
        sm += r;
        pos = max(pos, sm);
        neg = min(neg, sm);
    }

    printf("%d\n", pos - neg);
    return 0;
}