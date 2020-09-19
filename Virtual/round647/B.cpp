#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 1031
using namespace std;
typedef long long ll;
const ll inf = 1e9;

int a[MAX_SIZE];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int n, i, j, valid = 0;
        scanf("%d", &n);
        for (i = 0 ; i < n; ++i) {
            scanf("%d", &a[i]);
        }

        multiset<int> st;
        for (i = 1 ; i <= 1024; ++i) {
            st.clear();
            for (j = 0 ; j < n; ++j) {
                st.insert(i ^ a[j]);
            }

            for (j = 0 ; j < n; ++j) {
                if (st.find(a[j]) != st.end()) {
                    st.erase(st.find(a[j]));
                }
            }

            if (st.empty()) {
                printf("%d\n", i);
                valid = 1;
                break;
            }
        }

        if (!valid) {
            printf("-1\n");
        }
    }
    return 0;
}