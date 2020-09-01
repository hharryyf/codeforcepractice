#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 700111
using namespace std;

vector<int> pos[MAX_SIZE];
int len[MAX_SIZE];
char st[MAX_SIZE];
int N;
map<int, int> ans[MAX_SIZE];
char st1[12], st2[12];

void calc(int idx) {
    int i;
    int val = 0;
    for (i = idx; i <= min(idx + 3, N); ++i) {
        val = val * 27;
        val += st[i] - 'a' + 1;
        pos[val].push_back(idx);
        len[val] = i - idx + 1;
    }
}

int geth(char s[]) {
    int val = 0, i, L = strlen(s);
    for (i = 0 ; i < L; ++i) {
        val *= 27;
        val += s[i] - 'a' + 1;
    }
    return val;
}

int main() {
    int i;
    scanf("%s", st + 1);
    N = strlen(st + 1);
    for (i = 1; i <= N; ++i) {
        calc(i);
    }

    int Q;
    scanf("%d", &Q);
    while (Q-- > 0) {  
        scanf("%s%s", st1, st2);
        int v1 = geth(st1), v2 = geth(st2);
        // cout << "hash= " << v1 << " " << v2 << endl;
        if (pos[v1].empty() || pos[v2].empty()) {
            printf("-1\n");
        } else {
            if (v1 > v2) swap(v1, v2);
            auto iter = ans[v1].find(v2);
            if (iter != ans[v1].end()) {
                printf("%d\n", iter->second);
            } else {
                if (pos[v1].size() > pos[v2].size()) swap(v1, v2);
                int ret = N;
                for (auto p : pos[v1]) {
                    int id = lower_bound(pos[v2].begin(), pos[v2].end(), p) - pos[v2].begin();
                    int l = p, r = p + len[v1] - 1;
                    if (id < (int) pos[v2].size()) {
                        l = min(l, pos[v2][id]);
                        r = max(pos[v2][id] + len[v2] - 1, r);
                        ret = min(ret, r - l + 1);
                        // cout << l << " " << r << endl;
                    }

                    l = p, r = p + len[v1] - 1;
                    if (id > 0) {
                        id--;
                        l = min(l, pos[v2][id]);
                        r = max(pos[v2][id] + len[v2] - 1, r);
                        ret = min(ret, r - l + 1);
                        // cout << l << " " << r << endl;
                    }
                }
                if (v1 > v2) swap(v1, v2);
                ans[v1][v2] = ret;
                printf("%d\n", ret);
            }
        }
    }
    return 0;
}