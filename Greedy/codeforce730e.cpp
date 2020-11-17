#include <bits/stdc++.h>
#define MAX_SIZE 111
using namespace std;

struct people {
    int a, d, id;
    bool operator < (people other) const {
        if (a != other.a) return a > other.a;
        return id < other.id;
    }
};

people s[MAX_SIZE];
int n;

int main() {
    int i, j, ans = 0;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d%d", &s[i].a, &s[i].d);
        s[i].id = i;
    }

    sort(s + 1, s + 1 + n);
    
    vector<int> ret;
    for (i = 1; i <= n; ++i) {
        if (s[i].d < 0) {
            ret.push_back(s[i].id);
        }
    }

    for (auto v : ret) {
        for (i = 1; i <= n; ++i) {
            if (s[i].id == v) {
                j = i;
                while (j < n && (s[j].a + s[j].d < s[j+1].a || (s[j].a + s[j].d == s[j+1].a && s[j].id > s[j+1].id))) {
                    swap(s[j], s[j+1]);
                    ans++;
                    j++;
                }
                s[j].a = s[j].a + s[j].d;
                break;
            }
        }
    }

    ret.clear();
    for (i = n; i >= 1; --i) {
        if (s[i].d > 0) {
            ret.push_back(s[i].id);
        }
    }

    for (auto v : ret) {
        for (i = n; i >= 1; --i) {
            if (s[i].id == v) {
                j = i;
                while (j > 1 && (s[j].a + s[j].d > s[j-1].a || (s[j].a + s[j].d == s[j-1].a && s[j].id < s[j-1].id))) {
                    swap(s[j], s[j-1]);
                    ans++;
                    j--;
                }
                s[j].a = s[j].a + s[j].d;
                break;
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}