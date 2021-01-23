#include <bits/stdc++.h>
#define MAX_SIZE 200011
typedef long long ll;
using namespace std;

struct qrs {
    int x, tp;
    bool operator < (qrs other) const {
        if (x != other.x) return x < other.x;
        return tp < other.tp;
    }
};

ll ans = 0, curr = 0, del = 0;
int N;
vector<qrs> evt;
char st[4];

void addevent(int x, int tp) {
    evt.push_back(qrs{x, tp});
}

map<int, int> mp1, mp2;

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
        int t, len, idx;
        scanf("%s%d%d%d", st, &t, &len, &idx);
        if (st[0] == 'h') {
            // idx + t
            addevent(idx - t, 1);
            addevent(idx - t - len, 3);
        } else {
            addevent(idx - t, 0);
            addevent(idx - t - len, 2);
        }
    }

    sort(evt.begin(), evt.end());
    for (auto e : evt) {
        if (e.tp == 1 || e.tp == 3) {
            if (e.tp == 3) {
                curr++;
            } else {
                del++;
            }
        } else {
            if (e.tp == 0) {
                ans = ans + curr;
            } else {
                ans = ans - del;
            }
        }
    }
    cout << ans << endl;
    return 0;
}