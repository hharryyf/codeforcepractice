#include <bits/stdc++.h>
#define MAX_SIZE 2011
using namespace std;

int tol[MAX_SIZE][MAX_SIZE];
int a[MAX_SIZE][MAX_SIZE], sum[MAX_SIZE], sum2[MAX_SIZE];
int h[MAX_SIZE][MAX_SIZE];
vector<int> q[MAX_SIZE][MAX_SIZE];
int ans[MAX_SIZE * 50];
int X, Y, N, Q;
vector<pair<int, int>> st;

int main() {
    int i, j;
    scanf("%d%d%d%d", &X, &Y, &N, &Q);
    while (N-- > 0) {
        int x1, x2, y1, y2;
        scanf("%d%d%d%d", &x1, &x2, &y1, &y2);
        ++x1, ++y1;
        for (i = x1; i <= x2; ++i) {
            for (j = y1; j <= y2; ++j) {
                a[i][j] = 1;
            }
        }
    }

    for (i = 1; i <= Q; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        q[x][y].push_back(i);
    }

    for (i = 1; i <= X; ++i) {
        for (j = 1; j <= Y; ++j) {
            if (a[i][j] == 1) {
                h[i][j] = 0;
            } else {
                h[i][j] = h[i - 1][j] + 1;
            }
        }
    }

    for (i = 1; i <= X; ++i) {
        st.clear();
        st.emplace_back(0, 0);
        for (j = 1; j <= Y + 1; ++j) {
            // cout << "try insert " << i << " " << j << " height " << h[i][j] << endl;
            pair<int, int> curr = {h[i][j], j};
            while (curr.first < st.back().first) {
                auto p = st.back();
                curr.second = p.second;
                st.pop_back();
                tol[p.first][j - p.second]++;
                //cout << "+ " << p.first << " " << j - p.second << endl;
                tol[max(curr.first, st.back().first)][j - p.second]--;
                //cout << "- " << max(curr.first, st.back().first) << " " << j - p.second << endl;
            }
            st.emplace_back(curr.first, curr.second);
        }
    }

    for (i = X; i >= 1; --i) {
        for (j = Y; j >= 1; --j) {
            sum[j] += tol[i][j];
            // cout << tol[i][j] << endl;
        }

        for (j = Y; j >= 1; --j) {
            sum2[j] = sum2[j + 1] + sum[j];
        }

        for (j = Y; j >= 1; --j) {
            sum2[j] = sum2[j + 1] + sum2[j];
        }

        for (j = 1; j <= Y; ++j) {
            
            for (auto id : q[i][j]) {
                ans[id] = sum2[j];
            }
        }
    }

    for (i = 1; i <= Q; ++i) {
        printf("%d\n", ans[i]);
    }
    return 0;
}