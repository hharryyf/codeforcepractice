#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

char s[24];
map<string, int> mp;
vector<string> rmap;

struct student {
    pair<int, int> ran;
    int id;
    bool operator < (student other) const {
        return ran < other.ran;
    }
};

student stu[MAX_SIZE];
int ans[MAX_SIZE];

void preprocess() {
    rmap = vector<string>(7, "");
    mp["S"] = 1;
    mp["M"] = 2;
    mp["L"] = 3;
    mp["XL"] = 4;
    mp["XXL"] = 5;
    mp["XXXL"] = 6;
    rmap[1] = "S";
    rmap[2] = "M";
    rmap[3] = "L";
    rmap[4] = "XL";
    rmap[5] = "XXL";
    rmap[6] = "XXXL";
}

pair<int, int> parse(char s2[]) {
    int i, len = strlen(s2);
    int L = 0, R = 0;
    string s1 = "";
    for (i = 0 ; i < len; ++i) {
        if (s[i] == ',') {
            L = mp[s1];
            s1 = "";
        } else {
            s1 += s[i];
        }
    }

    if (s1.size() > 0) {
        R = mp[s1];
        if (L == 0) L = R;
    } else {
        R = L;
    }
    return make_pair(L, R);
}

int a[7];
set<pair<int, int>> st;

int main() {
    int i, j, n;
    preprocess();
    for (i = 1; i <= 6; ++i) {
        scanf("%d", &a[i]);
    }

    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%s", s);
        stu[i].ran = parse(s);
        // cout << stu[i].ran.first << "  " << stu[i].ran.second << endl;
        stu[i].id = i;
    }

    sort(stu + 1, stu + 1 + n);
    for (i = 1, j = 1; i <= 6; ++i) {
        while (j <= n && stu[j].ran.first <= i) {
            st.insert(make_pair(stu[j].ran.second, stu[j].id));
            j++;
        }

        while (!st.empty()) {
            auto it = st.begin();
            if (it->first < i) {
                printf("NO\n");
                return 0;
            }

            if (a[i] <= 0) break;
            ans[it->second] = i;
            a[i]--;
            st.erase(it);
        }
    }

    if (!st.empty()) {
        printf("NO\n");
        return 0;
    }
    printf("YES\n");
    for (i = 1; i <= n; ++i) {
        cout << rmap[ans[i]] << endl;;
    }

    return 0;
}