#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> getsubmatrix(int k) {
    vector<vector<int>> ret = vector<vector<int>>(1 << k, vector<int>(1 << k, 0));
    if (k == 0) {
        ret[0][0] = 1;
        return ret;
    }

    auto p = getsubmatrix(k-1);
    int i, j;
    for (i = 0 ; i < (1 << (k-1)); ++i) {
        for (j = 0 ; j < (1 << (k - 1)); ++j) {
            ret[i][j] = p[i][j];
            ret[i + (1 << (k-1))][j] = p[i][j];
            ret[i][j + (1 << (k-1))] = p[i][j];
            ret[i + (1 << (k-1))][j + (1 << (k-1))] = -p[i][j];
        }
    }

    return ret;
}

int main() {
    int i, j, k;
    scanf("%d", &k);
    auto ret = getsubmatrix(k);
    for (i = 0 ; i < (1 << k); ++i) {
        for (j = 0 ; j < (1 << k); ++j) {
            printf("%c", ret[i][j] > 0 ? '+' : '*');
        }
        printf("\n");
    }
    return 0;
}