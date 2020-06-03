#include <bits/stdc++.h>
#define MAX_SIZE 400011
using namespace std;

int n;
int a[MAX_SIZE];
int cnt[MAX_SIZE];
map<int, int> occ;
multiset<int> st;
vector<vector<int>> ans;

int main() {
    int i, j;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        occ[a[i]]++;
    }

    auto iter = occ.begin();
    while (iter != occ.end()) {
        st.insert(iter->second);
        ++iter;
    }
    
    // the number of row is i
    // get the maximum column
    int row = 0, col = 0;
    int tol = 0;
    for (i = 1; i <= sqrt(n); ++i) {
        // each element can be used at most i times
        while (!st.empty() && *st.begin() <= i) {
            tol += *st.begin();
            st.erase(st.begin());
        }

        int mx = i * (int) st.size() + tol;
        int ct = mx / i;
        if (i <= ct && ct * i >= row * col) {
            row = i, col = ct;
        }
    }


    printf("%d\n%d %d\n", row * col, row, col);
    
    iter = occ.begin();
    vector<pair<int, int>> freq;
    vector<int> num;

    tol = row * col;

    while (iter != occ.end()) {
        if (tol > 0) {
            int del = min(tol, min(iter->second, row));
            if (del != 0) {
                freq.emplace_back(del, iter->first);
                tol -= del;
            }
        }
        iter++;
    }

    sort(freq.begin(), freq.end(), greater<pair<int, int>>());
    for (auto f : freq) {
        while (f.first > 0) {
            num.push_back(f.second);
            f.first--;
        }
    }
    ans = vector<vector<int>>(row, vector<int>(col, 0));
    for (i = 0 ; i < col; ++i) {
        // chunk id = [i * row, i * row + row - 1]
        int id = i * row;
        for (j = 0 ; j < row; ++j) {
            ans[j][(i + j) % col] = num[id + j];
        }
    }

    for (i = 0; i < row; ++i) {
        for (j = 0 ; j < col; ++j) {
            printf("%d ", ans[i][j]);
        }
        printf("\n");
    }
    return 0;
}