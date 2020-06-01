#include <bits/stdc++.h>
#define MAX_SIZE 66
typedef long long ll;
using namespace std;

char s[MAX_SIZE];
vector<ll> rmpt;

int main() {
    int T;
    scanf("%d", &T);
    while (T > 0) {
        int n, m, i, j;
        scanf("%d%d", &n, &m);
        rmpt.clear();
        vector<pair<ll, ll>> interval;
        vector<pair<ll, ll>> ord;
        for (i = 0 ; i < n; ++i) {
            scanf("%s", s);
            ll curr = 0;
            for (j = m - 1; j >= 0; --j) {
                curr += (1ll << (m - j - 1)) * (s[j] - '0');
            }
            rmpt.push_back(curr);
        }

        sort(rmpt.begin(), rmpt.end());
        ll tol = 0;
        int sz = rmpt.size();
        if (rmpt[0] != 0) {
            interval.emplace_back(0, rmpt[0] - 1);
            ord.emplace_back(tol, tol + rmpt[0] - 1);
            tol = tol + rmpt[0];
        }

        for (i = 0; i < sz - 1; ++i) {
            if (rmpt[i+1] - rmpt[i] > 1) {
                interval.emplace_back(rmpt[i] + 1, rmpt[i+1] - 1);
                ord.emplace_back(tol, tol + rmpt[i+1] - rmpt[i] - 2);
                tol = tol + rmpt[i+1] - rmpt[i] - 1;
            }
        }

        if (rmpt.back() != ((1ll << m) - 1)) {
            interval.emplace_back(rmpt.back() + 1, (1ll << m) - 1);
            ord.emplace_back(tol, tol + (1ll << m) - rmpt.back() - 2);
        }

        ll k = (1ll << m) - n;
        k--;
        k /= 2;
        /*cout << "print case " << endl;
        for (i = 0 ; i < (int) interval.size(); ++i) {
            printf("%I64d %I64d , %I64d %I64d\n", interval[i].first, interval[i].second, ord[i].first, ord[i].second);
        }
        */
        for (i = 0 ; i < (int) interval.size(); ++i) {
            if (k >= ord[i].first && k <= ord[i].second) {
                ll num = k - ord[i].first + interval[i].first;
                // cout << num << " is found for  k= " << k << endl;
                vector<int> ret;
                while (num > 0) {
                    ret.push_back(num % 2);
                    num /= 2;
                }

                while ((int) ret.size() < m) {
                    ret.push_back(0);
                }
                reverse(ret.begin(), ret.end());
                for (auto v : ret) {
                    printf("%d", v);
                }
                printf("\n");
                break;
            }
        }
        --T;
    }
    return 0;
}