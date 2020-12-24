#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

int a[MAX_SIZE];
int N;

int main() {
    int i, root = 0;
    set<int> st;
    scanf("%d", &N);
    for (i = 1; i <= N - 1; ++i) scanf("%d", &a[i]);
    for (i = 1; i <= N; ++i) {
        st.insert(i);
    }   
    root = a[1];
    printf("%d\n", a[1]);
    st.erase(a[1]);
    for (i = 2; i <= N; ++i) {
        if (st.find(a[i]) == st.end()) {
            printf("%d %d\n", root, *st.rbegin());
            st.erase(*st.rbegin());
            root = a[i];
        } else {
            printf("%d %d\n", root, a[i]);
            st.erase(a[i]);
            root = a[i];
        }
    }

    if (!st.empty()) {
        printf("%d %d\n", *st.begin(), root);
    }
    return 0;
}