#include <bits/stdc++.h>
#define MAX_SIZE 3011
using namespace std;

struct stu {
    char name[12];
    int ai;
    int hi;
    bool operator < (stu other) const {
        return ai < other.ai;
    }
};

stu a[MAX_SIZE];
deque<int> q;

int main() {
    int n, i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%s %d", a[i].name, &a[i].ai);
    }

    sort(a + 1, a + 1 + n);

    for (i = 1; i <= n; ++i) {
        if (a[i].ai > (int) q.size()) {
            printf("-1\n");
            return 0;
        }
        q.insert(q.begin() + a[i].ai, i);
    }

    int height = 19260817;
    while (!q.empty()) {
        a[q.front()].hi = height--;
        q.pop_front();
    }

    for (i = 1; i <= n; ++i) {
        printf("%s %d\n", a[i].name, a[i].hi);
    }
    return 0;
}