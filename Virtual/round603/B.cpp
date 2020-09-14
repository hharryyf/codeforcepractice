#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

char st[6];
string ss[11];
map<string, int> s;
multiset<string> t;

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int n, i, j, k;
        scanf("%d", &n);
        s.clear();
        t.clear();
        for (i = 0 ; i < n; ++i) {
            scanf("%s", st);
            ss[i] = string(st);
            s[ss[i]]++;
            t.insert(ss[i]);
        }
        
        int cnt = 0;
        vector<string> ret;
        for (auto iter : s) {
            cnt += (iter.second - 1);
        }

        for (i = 0 ; i < n; ++i) {
            if (s[ss[i]] == 1) {
                ret.push_back(ss[i]);
            } else {
                t.erase(t.find(ss[i]));
                if (t.find(ss[i]) == t.end()) {
                    ret.push_back(ss[i]);
                    t.insert(ss[i]);
                    continue;
                }
                for (k = 0 ; k < 4; ++k) {
                    auto ch = ss[i][k];
                    bool ok = false;
                    for (j = 0 ; j <= 9; ++j) {
                        ss[i][k] = j + '0';
                        if (t.find(ss[i]) == t.end()) {
                            ok = true;
                            break;
                        }
                    }

                    if (ok) {
                        ret.push_back(ss[i]);
                        break;
                    } else {
                        ss[i][k] = ch;
                    }
                }
                t.insert(ss[i]);
            }
        }
        printf("%d\n", cnt);
        for (auto c : ret) {
            cout << c << endl;
        }
    }
    return 0;
}