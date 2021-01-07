#include <bits/stdc++.h>
#define MAX_SIZE 300011
using namespace std;

char st[MAX_SIZE];

int main() {
    int i;
    scanf("%s", st + 1);
    vector<int> ret;
    int len = strlen(st + 1);
    for (i = 1; i <= len; i = i + 3) {
        if (st[i] == st[i+1] && st[i+1] == st[i+2]) {
            if (st[i-1] != st[i]) {
                st[i+2] = '0' + (1 - (st[i+2] - '0'));
                st[i+1] = '0' + (1 - (st[i+1] - '0'));
                ret.push_back(i+1);
            } else {
                st[i] = '0' + (1 - (st[i] - '0'));
                st[i+1] = '0' + (1 - (st[i+1] - '0'));
                ret.push_back(i);
            }
        } else {
            if (st[i] == st[i+1]) {
                st[i+2] = '0' + (1 - (st[i+2] - '0'));
                st[i+1] = '0' + (1 - (st[i+1] - '0'));
                ret.push_back(i+1);
            } else if (st[i+1] == st[i+2]) {
                st[i] = '0' + (1 - (st[i] - '0'));
                st[i+1] = '0' + (1 - (st[i+1] - '0'));
                ret.push_back(i);
            }
        }
    }

    int cnt = 1;
    for (i = 1; i < len; ++i) {
        cnt += (st[i] != st[i+1]);
    }
    
    if (cnt < 2 * (len / 3)) {
        printf("bad!\n");
        return 9;
    }
    printf("%d\n", (int) ret.size());
    for (auto v : ret) {
        printf("%d ", v);
    }
    return 0;
}