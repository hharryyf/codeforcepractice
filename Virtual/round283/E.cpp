#include <bits/stdc++.h>
#define MAX_SIZE 200011
typedef long long ll;
using namespace std;

struct event {
    // tp = 0 means the plays, tp = 1 means the actors
    int l, r, id, tp;
    bool operator < (event other) const {
        if (r != other.r) {
            return r < other.r;
        }
        return tp < other.tp;
    }
};

int cap[MAX_SIZE];
vector<event> evt;
// left bound, id
set<pair<int, int>> st;
int n, m;
int ans[MAX_SIZE];

int main() {
    int i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        int l, r;
        scanf("%d%d", &l, &r);
        evt.push_back(event{l, r, i, 0});
    }
    scanf("%d", &m);
    for (i = 1; i <= m; ++i) {
        int l, r;
        scanf("%d%d%d", &l, &r, &cap[i]);
        evt.push_back(event{l, r, i, 1});
    }

    sort(evt.begin(), evt.end());
    int sz = evt.size();
    for (i = 0 ; i < sz; ++i) {
        if (evt[i].tp == 0) {
            st.insert(make_pair(evt[i].l, evt[i].id));
        } else {
            while (!st.empty() && cap[evt[i].id] > 0) {
                auto iter = st.lower_bound(make_pair(evt[i].l, -1));
                if (iter == st.end()) {
                    break;
                }
                ans[iter->second] = evt[i].id;
                st.erase(*iter);
                cap[evt[i].id]--;
            }
        }
    }

    if (st.empty()) {
        printf("YES\n");
        for (i = 1; i <= n; ++i) {
            printf("%d ", ans[i]);
        }
        printf("\n");
    } else {
        printf("NO\n");
    }
    return 0;
}