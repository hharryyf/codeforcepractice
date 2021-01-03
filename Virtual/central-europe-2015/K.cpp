/*
    Not my code, implemented by Tom.
*/

#include <bits/stdc++.h>
using namespace std;
#define MAXN 200005
#define ID if (1)
#define INF ((1<<30)+1)
int n;
int nx[MAXN];
int in[MAXN];
int color[MAXN];
int main() {
    cin >> n;
    n *= 2;
    for (int i = 1; i <= n; i++) {
        cin >> nx[i];
        in[nx[i]]+=1;
    }
    deque<int> q;
    for (int i = 1; i <= n; i++) {
        if (!in[i]) {
            color[i] = 1;
            q.push_back(i);
        }
    }
    while (q.size()) {
        int at = q.front();
        q.pop_front();
        color[at] = 1;
        if (color[nx[at]] != 2) {
            color[nx[at]] = 2;
            in[nx[nx[at]]] -= 1;
        }
        if (!color[nx[nx[at]]] && in[nx[nx[at]]] == 0) {
            color[nx[nx[at]]] = 1;
            q.push_back(nx[nx[at]]);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!color[i]) {
            color[i] = 1;
            q.push_back(i);
            while (q.size()) {
                int at = q.front();
                q.pop_front();
                color[at] = 1;
                if (color[nx[at]] != 2) {
                    color[nx[at]] = 2;
                    in[nx[nx[at]]] -= 1;
                }
                if (!color[nx[nx[at]]] && in[nx[nx[at]]] == 0) {
                    color[nx[nx[at]]] = 1;
                    q.push_back(nx[nx[at]]);
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (color[i] == 1) cout << i << ' ';
    }
    cout << endl;
}