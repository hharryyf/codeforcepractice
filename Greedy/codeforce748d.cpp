#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

map<string, vector<int>> st;
map<string, vector<int>> palindrome;
char s[MAX_SIZE];

vector<pair<int, int>> pgroup;
vector<int> single;

int main() {
    int i, n, k, j;
    scanf("%d%d", &n, &k);
    for (j = 1; j <= n; ++j) {
        int v;
        scanf("%s%d", s, &v);
        bool flag = true;
        for (i = 0 ; i < k / 2; ++i) {
            if (s[i] != s[k - i - 1]) {
                flag = false;
                break;
            }
        }

        if (flag) {
            palindrome[string(s)].push_back(v);
        } else {
            st[string(s)].push_back(v);
        }
    }


    int ans = 0;
    auto iter = st.begin();
    
    while (iter != st.end()) {
        sort(iter->second.begin(), iter->second.end());
        ++iter;
    }

    iter = palindrome.begin();
    while (iter != palindrome.end()) {
        sort(iter->second.begin(), iter->second.end());
        ++iter;
    }
    iter = st.begin();
    // we finish the non-palindrome case
    // it is matching greedily
    while (iter != st.end()) {
        string ss = iter->first;
        reverse(ss.begin(), ss.end());
        auto iter1 = st.find(ss);
        if (iter1 != st.end()) {
            while (!iter->second.empty() && !iter1->second.empty()) {
                ans += max(0, iter->second.back() + iter1->second.back());
                iter->second.pop_back();
                iter1->second.pop_back();
            }
        } 
        ++iter;
    }

    // now we should deal with the tricky case, palindrome + palindrome
    iter = palindrome.begin();
    while (iter != palindrome.end()) {
        while ((int) iter->second.size() >= 2) {
            int v1 = iter->second.back();
            iter->second.pop_back();
            int v2 = iter->second.back();
            iter->second.pop_back();
            if (v1 + v2 >= 0) {
                pgroup.emplace_back(v1, v2);
            } else if (v1 > 0) {
                single.push_back(v1);
            }
        }

        if (!iter->second.empty()) {
            int v = iter->second.back();
            if (v > 0) {
                single.push_back(v);
            }
            iter->second.pop_back();
        }
        ++iter;
    }

    int cost1 = 0, cost2 = 0;
    int mnn = 0;
    for (auto p : pgroup) {
        cost1 += p.first + p.second;
        mnn = min(mnn, p.second);
    }

    int mxx = 0;
    if (!single.empty()) mxx = *max_element(single.begin(), single.end());
    cost2 = cost1 + mxx;
    cost1 -= mnn;
    // cout << mnn << " " << cost1 << " " << cost2 << " " << *max_element(single.begin(), single.end()) << endl;
    ans = ans + max(cost1, cost2);
    printf("%d\n", ans);
    return 0;
}