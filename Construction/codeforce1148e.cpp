#include <bits/stdc++.h>
#define MAX_SIZE 300011
using namespace std;
typedef long long ll;

pair<int, int> t[MAX_SIZE], s[MAX_SIZE];
vector<pair<pair<int, int>, int>> oper;

int main() {
    int n, i;
    ll tol = 0;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &s[i].first);
        tol += s[i].first;
        s[i].second = i;
    }

    for (i = 1; i <= n; ++i) {
        scanf("%d", &t[i].first);
        t[i].second = i;
        tol -= t[i].first;
    }

    if (tol != 0) {
        printf("NO\n");
        return 0;
    }

    sort(s + 1, s + 1 + n);
    sort(t + 1, t + 1 + n);

    // we conclude that s[i] match with t[i] can be the optimal construction
    // and if it is not the optimal construction, there's no solution
    set<pair<int, int>> st;
    for (i = 1; i <= n; ++i) {
        if (s[i].first < t[i].first) {
            st.insert(make_pair(t[i].first - s[i].first, s[i].second));
        } else if (t[i].first < s[i].first) {
            while (!st.empty() && (t[i].first < s[i].first)) {
                auto p = st.begin();
                int d = p->first;
                if (d <= s[i].first - t[i].first) {
                    s[i].first -= d;
                    oper.push_back(make_pair(make_pair(p->second, s[i].second), d));
                    st.erase(p);
                } else {
                    oper.push_back(make_pair(make_pair(p->second, s[i].second), s[i].first - t[i].first));
                    pair<int, int> npr = make_pair(d - (s[i].first - t[i].first), p->second);
                    st.erase(p);
                    s[i].first = t[i].first;
                    st.insert(npr);
                }
            }

            if (t[i].first < s[i].first) {
                printf("NO\n");
                return 0;
            }
        }
    }

    printf("YES\n");
    printf("%d\n", (int) oper.size());
    for (auto v : oper) {
        printf("%d %d %d\n", v.first.first, v.first.second, v.second);
    }
    return 0;
}