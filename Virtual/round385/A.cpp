#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

set<string> st;
char s[55];
list<char> q;
int n;

int main() {
    int n, i;
    scanf("%s", s);
    n = strlen(s);
    for (i = 0 ; i < n; ++i) {
        q.push_back(s[i]);
    }

    for (i = 0 ; i <= n; ++i) {
        string ss;
        for (auto v : q) {
            ss += v;
        }
        st.insert(ss);
        auto ch = q.back();
        q.pop_back();
        q.push_front(ch);
    }

    cout << st.size() << endl;
    return 0;
}