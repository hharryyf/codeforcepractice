#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;

int n, m, n2;
char s[MAX_SIZE];
char p[MAX_SIZE];
char ns[MAX_SIZE];

vector<string> ans1;

int find_length() {
    int i;
    for (i = 1; i <= 6; ++i) {
        // check if n - i has i digits
        if ((int) to_string(n - i).length() == i) {
            return i;
        }
    }

    return -1;
}

char as1[MAX_SIZE], as2[MAX_SIZE];

static bool cmp(const string &r1, const string &r2) {
    return (r1 + r2) < (r2 + r1);
}

int main() {
    int i;
    scanf("%s", s);
    scanf("%s", p);
    n = strlen(s);
    n2 = strlen(p);
    int k = n - find_length();
    // cout << "length= " << k << endl;
    if (k == -1) return 0;
    // we know that k is the length of the string, we should extract a subsequence
    // of the digit representation of k
    string dgt = to_string(k);
    unordered_map<char, int> st;
    for (auto ch : dgt) {
        st[ch]++;
    }

    for (i = 0 ; i < n; ++i) {
        if (st[s[i]] == 0) {
            ns[m++] = s[i];
        } else {
            st[s[i]]--;
        }
    }
    // cout << ns << endl;
    st.clear();
    for (i = 0 ; i < n2; ++i) {
        st[p[i]]++;
    }

    multiset<char> ss;
    for (i = 0 ; i < m; ++i) {
        if (st[ns[i]] == 0) {
            ss.insert(ns[i]);
        } else {
            st[ns[i]]--;
        }
    }

    if (ss.upper_bound('0') == ss.end()) {
        for (i = 0 ; i < n2; ++i) putchar(p[i]);
        for (auto ch : ss) putchar(ch);
    } else if (n2 == 0 || p[0] == '0') {
        putchar(*ss.upper_bound('0'));
        ss.erase(ss.upper_bound('0'));
        while (!ss.empty() && *ss.begin() == '0') {
            ss.erase(ss.begin());
            putchar('0');
        }
        printf("%s", p);
        for (auto ch : ss) putchar(ch);
    } else {
        // cout << "this case " << endl;
        ans1 = vector<string>(1, p);
        char c = *ss.upper_bound('0');
        // printf("%c\n", c);
        ss.erase(ss.upper_bound('0'));
        for (auto ch : ss) {
            ans1.push_back(string(1, ch));
        }
        
        sort(ans1.begin(), ans1.end(), cmp);
        as1[0] = c;
        i = 1;
        for (auto &rs : ans1) {
            for (auto ch : rs) {
                as1[i++] = ch;
            }
        }
        ss.insert(c);
        for (i = 0 ; i < n2; ++i) {
            as2[i] = p[i];
        }

        for (auto ch : ss) {
            as2[i++] = ch;
        }

        if (strcmp(as1, as2) < 0) {
            printf("%s\n", as1);
        } else {
            // cout << "here" << endl;
            printf("%s\n", as2);
        }
    }
    return 0;
}