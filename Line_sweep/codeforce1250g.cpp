#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 200011
using namespace std;

ll prea[MAX_SIZE], preb[MAX_SIZE], wa[MAX_SIZE], wb[MAX_SIZE], K;
int a[MAX_SIZE], b[MAX_SIZE], ok[MAX_SIZE], cost[MAX_SIZE], N;
int pre[MAX_SIZE];
vector<pair<int, int>> add[MAX_SIZE];
vector<pair<int, int>> del[MAX_SIZE];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int i;
        scanf("%d%I64d", &N, &K);
        ok[0] = 0;
        add[0].clear();
        del[0].clear();
        for (i = 1; i <= N; ++i) {
            scanf("%d", &a[i]);
            prea[i] = prea[i-1] + a[i];
            add[i].clear();
            del[i].clear();
            pre[i] = ok[i] = 0;
            cost[i] = MAX_SIZE;
        }

        for (i = 1; i <= N; ++i) {
            scanf("%d", &b[i]);
            preb[i] = preb[i-1] + b[i];
        }

        for (i = 1; i <= N; ++i) {
            if (prea[i] > preb[i]) {
                wa[i] = -preb[i];
                wb[i] = -preb[i];
            } else {
                wb[i] = -prea[i];
                wa[i] = -prea[i];
            }
        }

        multiset<pair<int, int>> st;
        add[0].emplace_back(0, 0);
        del[0].emplace_back(0, 0);
        for (i = 0 ; i <= N - 1; ++i) {
            int r = -1, low = i + 1, high = N;
            for (auto p : add[i]) {
                st.insert(p);
            }

            if (!st.empty()) {
                cost[i] = st.begin()->first;
                pre[i] = st.begin()->second;
            } else {
                break;
            }

            while (low <= high) {
                int mid = (low + high) / 2;
                if (prea[mid] + wa[i] < K) {
                    r = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            if (r != -1) {
                if (preb[r] + wb[i] >= K) {
                    ok[i] = 1;
                }

                add[i+1].emplace_back(cost[i] + 1, i);
                del[r].emplace_back(cost[i] + 1, i);
            }

            for (auto p : del[i]) {
                st.erase(st.find(p));
            }
        }

        int idx = -1;
        for (i = 0; i < N; ++i) {
            if (ok[i]) {
                if (idx == -1 || cost[i] < cost[idx]) {
                    if (cost[i] < MAX_SIZE) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
            printf("-1\n");
        } else {
            printf("%d\n", cost[idx]);
            int curr = idx;
            while (idx != 0) {
                printf("%d ", idx);
                idx = pre[idx];
                if (curr <= idx) return 9;
                curr = idx;
            }
            printf("\n");
        }
    }

    return 0;
}