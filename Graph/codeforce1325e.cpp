#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 1000011
using namespace std;
// prime less than 1000
vector<int> prime;
int seen[MAX_SIZE];
// the chunks stores all the primes greater than 1e3
vector<pair<int, int>> g[MAX_SIZE];
int a[MAX_SIZE];
// by default first= first prime, second= second prime
pair<int, int> p[MAX_SIZE];
int visited[MAX_SIZE];
int depth[MAX_SIZE];
int n;

void init() {
    int i, j;
    for (i = 2; i < 1000; ++i) {
        if (!seen[i]) { 
            prime.push_back(i);
            for (j = 1; j * i < 1000; ++j) {
                seen[i * j] = 1;
            }
        }
    }
}

void insert(int v, int idx) {
    if (p[idx].first == 0) {
        p[idx].first = v;
    } else {
        p[idx].second = v;
        if (p[idx].first > p[idx].second) {
            swap(p[idx].first, p[idx].second);
        }
    }
}


int BFS(int src) {
    if (g[src].empty()) return MAX_SIZE;
    int ret = MAX_SIZE;
    memset(depth, -1, sizeof(depth));
    memset(visited, 0, sizeof(visited));
    queue<int> q;
    q.push(src);
    depth[src] = 0;
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        for (auto np : g[p]) {
            int nv = np.first, id = np.second;
            if (visited[id]) continue;
            if (depth[nv] == -1) {
                depth[nv] = depth[p] + 1;
                q.push(nv);
                visited[id] = 1;
            } else {
                ret = min(ret, depth[nv] + depth[p] + 1);
            }
        }
    }
    return ret;
}

int main() {
    int i, j, ans = MAX_SIZE;
    init();
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }

    for (i = 1; i <= n; ++i) {
        map<int, int> cnt;
        for (j = 0 ; j < (int) prime.size(); ++j) {
            if (a[i] <= 1) break;
            while ((a[i] % prime[j] == 0) && a[i] > 1) {
                cnt[prime[j]]++;
                a[i] /= prime[j];
            }
        }

        auto iter = cnt.begin();
        vector<int> tmp;
        while (iter != cnt.end()) {
            if (iter->second % 2 == 1) {
                tmp.push_back(iter->first);
            }
            ++iter;
        }
        
        if (a[i] != 1) {
            for (auto tp : tmp) {
                insert(tp, i);
            }
            insert(a[i], i);
        } else {
            if (tmp.empty()) {
                printf("1\n");
                return 0;
            }

            for (auto tp : tmp) {
                insert(tp, i);
            }            
        }
    }

    sort(p + 1, p + 1 + n);
    for (i = 2; i <= n; ++i) {
        if (p[i] == p[i-1]) {
            printf("2\n");
            return 0;
        }
    }

    for (i = 1; i <= n; ++i) {
        g[p[i].first].emplace_back(p[i].second, i);
        g[p[i].second].emplace_back(p[i].first, i);
    }

    for (i = 0 ; i < 1000; ++i) {
        ans = min(ans, BFS(i));
    }

    if (ans == MAX_SIZE) {
        printf("-1\n");
        return 0;
    }

    printf("%d\n", ans);
    return 0;
}