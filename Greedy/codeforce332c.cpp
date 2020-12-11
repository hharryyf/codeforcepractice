#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

struct student {
    int a, b, id;
    bool operator < (student other) const {
        if (a != other.a) return a < other.a;
        if (b != other.b) return b < other.b;
        return id < other.id;
    }
};

static bool cmp(student &s1, student &s2) {
    if (s1.b != s2.b) return s1.b < s2.b;
    if (s1.a != s2.a) return s1.a > s2.a;
    return s1.id < s2.id;
}

student stu[MAX_SIZE];
set<student> selected, candidate;
int N, P, K;
long long cost[MAX_SIZE];

int main() {
    int i;
    scanf("%d%d%d", &N, &P, &K);
    for (i = 1; i <= N; ++i) {
        scanf("%d%d", &stu[i].a, &stu[i].b);
        stu[i].id = i;
    }

    sort(stu + 1, stu + 1 + N, cmp);

    for (i = P - K + 1; i <= N; ++i) {
        selected.insert(stu[i]);
        cost[P - K] += stu[i].a;
    }

    while ((int) selected.size() > K) {
        auto s = *selected.begin();
        selected.erase(s);
        candidate.insert(s);
        cost[P - K] -= s.a;
    }

    for (i = P - K + 1; i <= N - K; ++i) {
        cost[i] = cost[i - 1];
        if (selected.find(stu[i]) == selected.end()) {
            candidate.erase(stu[i]);
        } else {
            selected.erase(stu[i]);
            cost[i] -= stu[i].a;
            cost[i] += candidate.rbegin()->a;
            selected.insert(*candidate.rbegin());
            candidate.erase(*candidate.rbegin());
        }
    }

    /*for (i = 1; i <= N; ++i) {
        printf("%I64d ", cost[i]);
    }
    printf("\n");*/
    int idx = 0;
    long long tol = 0;
    for (i = 0 ; i <= N - K; ++i) {
        if (tol <= cost[i]) {
            idx = i;
            tol = cost[i];
        }
    }

    priority_queue<student> q;
    for (i = idx + 1; i <= N; ++i) {
        q.push(stu[i]);
    }

    for (i = idx; i > idx - (P - K) && i > 0; --i) {
        printf("%d ", stu[i].id);
    }

    for (i = 0 ; i < K; ++i) {
        printf("%d ", q.top().id);
        q.pop();
    }

    return 0;
}