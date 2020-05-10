#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m, k, i;
    scanf("%d%d%d", &n, &m, &k);
    if (k > 4 * n * m - 2 * n - 2 * m) {
        printf("NO\n");
        return 0;
    }
    printf("YES\n");
    if (n == 1 && m == 1) {
        printf("0\n");
        return 0;
    }

    if (n == 1) {
        if (k <= m - 1) {
            printf("1\n");
            printf("%d %c", k, 'R');
        } else {
            printf("2\n");
            printf("%d %c\n%d %c\n", m - 1, 'R', k - (m - 1), 'L');
        }
        return 0;
    }

    if (m == 1) {
        if (k <= n - 1) {
            printf("1\n");
            printf("%d %c", k, 'D');
        } else {
            printf("2\n");
            printf("%d %c\n%d %c\n", n - 1, 'D', k - (n - 1), 'U');
        }
        return 0;
    }

    vector<int> idx;
    vector<string> str;
    idx.push_back(m - 1);
    str.push_back("R");
    idx.push_back(2 * m - 2);
    str.push_back("L");
    int cnt = 2 * m - 2;
    for (i = 2; i <= n; ++i) {
        // down once
        idx.push_back(cnt + 1);
        str.push_back("D");
        cnt++;
        idx.push_back(cnt + 3 * (m - 1));
        str.push_back("RUD");
        cnt += 3 * (m - 1);
        idx.push_back(cnt + m - 1);
        str.push_back("L");
        cnt += m - 1;
    }
    idx.push_back(4 * n * m - 2 * n - 2 * m);
    str.push_back("U");
    int curr = 0;
    cnt = upper_bound(idx.begin(), idx.end(), k) -  idx.begin() - 1;
    vector<pair<int, string>> ret;
    for (i = 0 ; i <= cnt; ++i) {
        int nm = (i == 0 ? idx[i] : idx[i] - idx[i-1]);
        ret.emplace_back(nm / (int) str[i].length(), str[i].data());
        curr = idx[i];
    }

    if (curr < k) {
        int whole = (k - curr) / (int) str[cnt + 1].length();
        int frac = (k - curr) % (int) str[cnt + 1].length();
        if (whole != 0) {
            ret.emplace_back(whole, str[cnt + 1]);
        }

        if (frac != 0) {
            for (i = 0 ; i < frac; ++i) {
                string st = "";
                st += str[cnt + 1][i];
                ret.emplace_back(1, st);
            }
        }
    }

    cout << ret.size() << endl;
    for (auto v : ret) {
        cout << v.first << " " << v.second << endl;
    }
    return 0;
}