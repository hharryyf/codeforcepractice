#include <bits/stdc++.h>
#define MAX_SIZE 300011
typedef long long ll;
using namespace std;

int n;
int pos[MAX_SIZE];
char color[MAX_SIZE];
char st[3];
// invariant, color[l], color[r] are green
ll calc(int l, int r) {
    int i;
    ll cost = 0;
    if (l == r) return 0;
    if (r - l == 1) return pos[r] - pos[l];
    ll ret = (pos[r] - pos[l]) * 2;
    int maxb = 0, maxr = 0;
    int lastb = -1, lastr = -1;
    for (i = l; i <= r; ++i) {
        if (color[i] == 'B' || color[i] == 'G') {
            if (lastb != -1) {
                maxb = max(maxb, pos[i] - pos[lastb]);
            }
            lastb = i;
        }
        
        if (color[i] == 'R' || color[i] == 'G') {
            if (lastr != -1) {
                maxr = max(maxr, pos[i] - pos[lastr]);
            }
            lastr = i;
        }
    }
    cost = (pos[r] - pos[l]) * 3 - maxr - maxb;
    ret = min(ret, cost);
    return ret;
}

ll solve() {
    vector<int> idx;
    int i;
    ll cost = 0;
    for (i = 1; i <= n; ++i) {
        if (color[i] == 'G') {
            idx.push_back(i);
        }
    }

    if (idx.empty()) {
        int lastb = -1, lastr = -1;
        for (i = 1; i <= n; ++i) {
            if (color[i] == 'B') {
                if (lastb != -1) {
                    cost += pos[i] - pos[lastb];
                }
                lastb = i;
            } else if (color[i] == 'R') {
                if (lastr != -1) {
                    cost += pos[i] - pos[lastr];
                }
                lastr = i;
            }
        }
    } else {
        // calculate 2 costs first 1 to idx[0] and idx.back() to n
        // then calculate the center costs
        int lastb = -1, lastr = -1;
        for (i = 1; i < idx[0]; ++i) {
            if (color[i] == 'B') {
                if (lastb != -1) {
                    cost += pos[i] - pos[lastb];
                }
                lastb = i;
            } else if (color[i] == 'R') {
                if (lastr != -1) {
                    cost += pos[i] - pos[lastr];
                }
                lastr = i;
            }
        }

        if (lastb != -1) {
            cost += pos[idx[0]] - pos[lastb];
        }

        if (lastr != -1) {
            cost += pos[idx[0]] - pos[lastr];
        }

        lastb = lastr = -1;

        for (i = n; i > idx.back(); --i) {
            if (color[i] == 'B') {
                if (lastb != -1) {
                    cost += pos[lastb] - pos[i];
                }
                lastb = i;
            } else if (color[i] == 'R') {
                if (lastr != -1) {
                    cost += pos[lastr] - pos[i];
                }
                lastr = i;
            }
        }

        if (lastb != -1) {
            cost += -pos[idx.back()] + pos[lastb];
        }

        if (lastr != -1) {
            cost += -pos[idx.back()] + pos[lastr];
        }

        for (i = 0 ; i < (int) idx.size() - 1; ++i) {
            cost += calc(idx[i], idx[i+1]);
        }
    }
    return cost;
}

int main() {
    int i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d%s", &pos[i], st);
        color[i] = st[0];
    }

    printf("%I64d\n", solve());
    return 0;
}