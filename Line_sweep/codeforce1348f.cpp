#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

vector<pair<int, int>> in[MAX_SIZE];
set<pair<int, int>> st;
int sq1[MAX_SIZE], sq2[MAX_SIZE];

int main() {
    int n, i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        in[a].emplace_back(b, i);
    }

    for (i = 1; i <= n; ++i) {
        for (auto p : in[i]) {
            st.insert(p);
        }

        auto iter = st.begin();
        sq1[iter->second] = i, sq2[iter->second] = i;
        st.erase(iter);
    }

    st.clear();
    bool valid = true;
    for (i = 1; i <= n; ++i) {
        for (auto p : in[i]) {
            st.insert(p);
        }

        if ((int) st.size() > 1) {
            auto iter = st.begin();
            ++iter;
            if (sq1[iter->second] <= st.begin()->first) {
                swap(sq2[iter->second], sq2[st.begin()->second]);
                valid = false;
                break;
            }
        }
        st.erase(st.begin());
    }

    if (!valid) {
        printf("NO\n");
        for (i = 1; i <= n; ++i) {
            printf("%d ", sq1[i]);
        }
        printf("\n");
        for (i = 1; i <= n; ++i) {
            printf("%d ", sq2[i]);
        }
        printf("\n");
    } else {
        printf("YES\n");
        for (i = 1; i <= n; ++i) {
            printf("%d ", sq1[i]);
        }
        printf("\n");
    }
    return 0;
}