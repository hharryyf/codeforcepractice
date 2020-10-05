#include <bits/stdc++.h>
#define MAX_SIZE 200011
typedef long long ll;
using namespace std;

int a[MAX_SIZE];
// position[i][0] means the first position such that prefix[pos[i][0]][0] >= i 
int pos[MAX_SIZE][2];
int prefix[MAX_SIZE][2];
int main() {
    int n, i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    // for (i = 0 ; i < MAX_SIZE; ++i) pos[i][0] = pos[i][1] = -1;
    int c1 = 0, c2 = 0;
    for (i = 1; i <= n; ++i) {
        if (a[i] == 1) c1++;
        else c2++;
        if (pos[c1][0] == 0) pos[c1][0] = i;
        if (pos[c2][1] == 0) pos[c2][1] = i;
        prefix[i][0] = c1, prefix[i][1] = c2;
    }

    vector<pair<int, int>> ret;
    for (i = 1; i <= n; ++i) {
        int w1 = 0, w2 = 0;
        int j = 0, lst = 0, ok = 0;
        // cout << "check " << i << endl;
        while (j <= n) {
            int p1 = pos[prefix[j][0] + i][0], p2 = pos[prefix[j][1] + i][1];
            // cout << p1 << " " << p2 <
            if (p1 == 0 && p2 == 0) break;
            if (p1 != 0 && p2 != 0) {
                if (p1 > p2) {
                    j = p2;
                    lst = 2;
                    w2++;
                } else {
                    j = p1;
                    w1++;
                    lst = 1;
                }
            } else if (p1 != 0) {
                w1++;
                j = p1;
                lst = 1;
            } else {
                w2++;
                j = p2;
                lst = 2;
            }

            if (j == n) {
                ok = true;
                break;
            }
        }
        
        if (ok) {
            if (lst == 1) {
                if (w1 > w2) {
                    ret.emplace_back(i, w1);
                }
            } else if (lst == 2) {
                if (w2 > w1) {
                    ret.emplace_back(i, w2);
                }
            }
        }
    }

    printf("%d\n", (int) ret.size());
    for (auto &p : ret) {
        // printf("%d %d\n", p.second, p.first);
        swap(p.first, p.second);
    }

    sort(ret.begin(), ret.end());
    for (auto p : ret) {
        printf("%d %d\n", p.first, p.second);
    }
    return 0;
}