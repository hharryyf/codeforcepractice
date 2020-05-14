#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

int ans[MAX_SIZE];

int main() {
    int n, h, i;
    scanf("%d%d", &n, &h);
    int v;
    vector<pair<int, int>> ret;
    for (i = 1; i <= n; ++i) {
        scanf("%d", &v);
        ret.emplace_back(v, i);
    }

    sort(ret.begin(), ret.end());

    int mnn1 = ret[0].first + ret[1].first;
    int mxx1 = ret[(int) ret.size() - 1].first + ret[(int) ret.size() - 2].first;
    int mnn2 = 1e9, mxx2 = 0;
    for (i = 1; i < (int) ret.size(); ++i) {
        mnn2 = min(mnn2, ret[0].first + ret[i].first + h);
        if (i > 1) {
            mnn2 = min(mnn2, ret[i].first + ret[i-1].first);
            mxx2 = max(mxx2, ret[i].first + ret[i-1].first);
        }

        mxx2 = max(mxx2, ret[0].first + ret[i].first + h);
    }

    if (mxx2 - mnn2 < mxx1 - mnn1) {
        ans[ret[0].second] = 2;
    }
    printf("%d\n", min(mxx2 - mnn2, mxx1 - mnn1));

    for (i = 1; i <= n; ++i) {
        if (ans[i] == 0) {
            printf("1 ");
        } else {
            printf("2 ");
        }
    }

    printf("\n");
    return 0;
}