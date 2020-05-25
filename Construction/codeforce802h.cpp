#include <bits/stdc++.h>
#define MAX_SIZE 203
using namespace std;

int n;

vector<int> comb;

int main() {
    int i;
    for (i = 0 ; i <= 100; ++i) {
        if (i == 0) comb.push_back(0);
        if (i == 1) comb.push_back(0);
        if (i == 2) comb.push_back(0);
        if (i >= 3) {
            comb.push_back((i * (i-1) * (i-2)) / 6);
        }
    }

    int n;
    scanf("%d", &n);
    i = 0;
    vector<int> pos;
    while (i < n) {
        int delta = n - i;
        int index = upper_bound(comb.begin(), comb.end(), delta) - comb.begin() - 1;
        pos.push_back(index);
        i += comb[index];
    }

    reverse(pos.begin(), pos.end());
    string st = "", pt = "bbba";
    int bcnt = 0;
    for (i = 0 ; i < (int) pos.size(); ++i) {
        while (bcnt < pos[i]) {
            st += 'b';
            bcnt++;
        }

        st += 'a';
    }

    printf("%s %s\n", st.data(), pt.data());
    return 0;
}