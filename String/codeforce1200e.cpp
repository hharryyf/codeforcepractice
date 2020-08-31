#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;
vector<char> st;
vector<char> ret;
char s[MAX_SIZE];
int p[MAX_SIZE];

void run_matching() {
    int N = strlen(s), i, j = 0;
    st.clear();
    st.push_back('$');
    for (i = 0 ; i < N; ++i) st.push_back(s[i]);
    st.push_back('#');
    // the last min(N, ret.size()) number of elements from ret
    N = min(N, (int) ret.size());
    for (i = (int) ret.size() - N; i < (int) ret.size(); ++i) {
        st.push_back(ret[i]);
    }

    N = (int) st.size() - 1;
    for (i = 2; i <= N; ++i) {
        while (j > 0 && st[i] != st[j+1]) j = p[j];
        if (st[i] == st[j+1]) ++j;
        p[i] = j;
    }

    int len = strlen(s);
    for (i = p[N]; i < len; ++i) ret.push_back(s[i]);
}

int main() {
    int i, N;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%s", s);
        run_matching();                
    }

    for (auto ch : ret) {
        printf("%c", ch);
    }
    printf("\n");
    return 0;
}