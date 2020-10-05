#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 200011
typedef long long ll;
using namespace std;

vector<vector<char>> str;
list<int> st;
int n;
char s[1011];

int main() {
    int i, j, k;
    scanf("%d", &n);
    scanf("%s", s);
    for (i = 0 ; i < n; ++i) {
        st.push_back(s[i] - '0');
    }

    for (i = 0; i < n; ++i) {
        for (j = 0 ; j <= 9; ++j) {
            auto iter = st.begin();
            while (iter != st.end()) {
                *iter = (*iter + 1) % 10;
                ++iter;
            }

            vector<char> curr(n);
            k = 0;
            for (auto v : st) {
                curr[k++] = v + '0';
            }
            str.push_back(curr);
        }

        st.push_front(st.back());
        st.pop_back();
    }

    sort(str.begin(), str.end());
    for (auto v : str[0]) {
        printf("%c", v);
    }
    printf("\n");
    return 0;
}