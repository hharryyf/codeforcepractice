#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 32014
using namespace std;

vector<int> prime;
int visited[MAX_SIZE];

void preprocess() {
    int i, j;
    for (i = 2; i < MAX_SIZE; ++i) {
        if (visited[i]) continue;
        prime.push_back(i);
        for (j = 1; j * i < MAX_SIZE; ++j) {
            visited[i * j] = 1;
        }
    }
}

void solve(int n) {
    int i, up = sqrt(n), N = n;
    // all factors
    set<int> fac;
    // prime factors
    vector<pair<int, vector<int>>> prifac;
    fac.insert(N);
    for (i = 2; i <= up; ++i) {
        if (N % i != 0) continue;
        fac.insert(i);
        fac.insert(N / i);
        if (binary_search(prime.begin(), prime.end(), i)) {
            int curr = 1;
            vector<int> ret;
            while (n % i == 0) {
                curr = curr * i;
                ret.push_back(curr);
                // flag |= (curr == N);
                n = n / i;
            }
            prifac.emplace_back(i, ret);
        }
    }

    // cout << fac.size() << endl;
    if (n > 1) {
        prifac.emplace_back(n, vector<int>(1, n));
    }

    for (auto iter : prifac) {
        // cout << iter.first << ": ";
        for (auto it : iter.second) {
            fac.erase(it);
            // cout << it << " ";
        }
        // cout << endl;
    }

    vector<int> ans;
    vector<int> res;
    for (auto v : fac) {
        if (v == N) continue;
        int sz = prifac.size();
        bool ok = true;
        for (i = 0 ; i < sz; ++i) {
            if ((v % prifac[i].first == 0) && (v % prifac[(i + 1) % sz].first == 0)) {
                res.push_back(v);
                ok = false;
                break;
            }
        }

        if (ok) {
            for (i = 0 ; i < sz; ++i) {
                if (v % prifac[i].first == 0) {
                    prifac[i].second.push_back(v);
                    break;
                }
            }
        }
    }

    for (auto v : res) {
        int sz = prifac.size();
        for (i = 0 ; i < sz; ++i) {
            if ((v % prifac[i].first == 0) && (v % prifac[(i + 1) % sz].first == 0)) {
                prifac[i].second.push_back(v);
                break;
            }
        }
    }
    for (auto iter : prifac) {
        for (auto it : iter.second) {
            ans.push_back(it);
        }
    }
    if ((int) prifac.size() > 1)
        ans.push_back(N);
    int sz = ans.size();
    int cnt = 0;
    // cout << ans.size() << endl;
    for (i = 0 ; i < sz; ++i) {
        printf("%d ", ans[i]);
        // if (ans[i] == 0) cout << "no !" << endl;
        cnt += (__gcd(ans[i], ans[(i + 1) % sz]) == 1);
    }
    printf("\n%d\n", cnt);
}
 
int main() {
    int T;
    preprocess();
    scanf("%d", &T);
    while (T-- > 0) {
        int n;
        scanf("%d", &n);
        solve(n);
    }
    return 0;
}