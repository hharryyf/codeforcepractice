#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

char s[MAX_SIZE];
int cnt[29];

int main() {
    int i, n;
    scanf("%s", s);
    n = strlen(s);
    for (i = 0 ; i < n; ++i) {
        cnt[s[i] - 'a']++;
    }

    vector<int> ret;
    for (i = 0 ; i < 26; ++i) {
        if (cnt[i] % 2 == 1) {
            ret.push_back(i);
        }
    }

    int sz = ret.size();
    for (i = 0 ; i < sz / 2; ++i) {
        cnt[ret[i]]++;
        cnt[ret[sz - i - 1]]--;
    }

    int pos = -1;
    for (i = 0 ; i < 26; ++i) {
        if (cnt[i] % 2 == 1) {
            pos = i;
        }
    }

    if (pos != -1) {
        s[n / 2] = pos + 'a';
        cnt[pos]--;
    }

    int l = 0, r = n - 1;
    for (i = 0 ; i < 26; ++i) {
        sz = cnt[i] / 2;
        while (sz > 0) {
            s[l] = i + 'a';
            l++;
            sz--;
        }
        sz = cnt[i] / 2;
        while (sz > 0) {
            s[r] = i + 'a';
            r--;
            sz--;
        }
    }

    printf("%s\n", s);
    return 0;
}