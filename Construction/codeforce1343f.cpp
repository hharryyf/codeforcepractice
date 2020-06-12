#include <bits/stdc++.h>
#define MAX_SIZE 203
using namespace std;


set<int> mp[MAX_SIZE];
set<int> st[MAX_SIZE];
int ans[MAX_SIZE];
int n;
vector<int> org[MAX_SIZE];

void init() {
    int i;
    for (i = 0; i < MAX_SIZE; ++i) {
        st[i].clear();
        mp[i].clear();
        org[i].clear();
    }
}

// occ[i] means i occurs in which set
set<int> occ[MAX_SIZE];
// st2[i] means the content of the ith set at the moment
set<int> st2[MAX_SIZE];
int visited[MAX_SIZE];
int p[MAX_SIZE];

bool check() {
    int i, j;
    for (i = 1; i <= n; ++i) {
        p[ans[i]] = i;
    }

    for (i = 2; i <= n; ++i) {
        int L = n + 1, R = 0;
        for (auto v : org[i]) {
            L = min(L, p[v]);
            R = max(R, p[v]);
        }

        if (R - L + 1 != (int) org[i].size()) return false;
        for (j = L; j <= R; ++j) {
            if (!binary_search(org[i].begin(), org[i].end(), ans[j])) return false;
        }
    }

    return true;
}

void dupset() {
    int i;
    for (i = 0; i < MAX_SIZE; ++i) {
        occ[i].clear();
        st2[i].clear();
    }

    for (i = 0 ; i < MAX_SIZE; ++i) {
        for (auto v : mp[i]) occ[i].insert(v);
        for (auto v : st[i]) st2[i].insert(v);
    }
}

// here v means we let ans[n] = v 
bool solve(int v, int pos) {
    int i;
    dupset();
    ans[pos] = v;
    memset(visited, 0, sizeof(visited));
    for (i = pos; i <= n; ++i) visited[ans[i]] = 1;

    for (i = pos; i >= 2; --i) {
        if ((int) occ[ans[i]].size() != 1) return false;
        int id = *occ[ans[i]].begin();
        // erase the occurence of answer i
        for (auto v : st2[id]) {
            occ[v].erase(id);
        }
        int f = -1;
        // secondly, fill ans[i-1]
        for (auto v : st2[id]) {
            if (!visited[v]) {
                if ((i > 2 && (int) occ[v].size() == 1) || (i == 2 && (int) occ[v].size() <= 1)) {
                    if (f == -1) {
                        f = v;
                    } else if (mp[f].size() < mp[v].size()) {
                        f = v;
                    }
                }    
            }
        }

        if (f == -1) {
            return false;
        }
        ans[i - 1] = f;
        visited[f] = 1;
    }
    return check();
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &n);
        init();
        memset(visited, 0, sizeof(visited));
        int i, j;
        for (i = 2; i <= n; ++i) {
            int ti;
            scanf("%d", &ti);
            while (ti-- > 0) {
                int v;
                scanf("%d", &v);
                st[i].insert(v);
                mp[v].insert(i);
                org[i].push_back(v);
            }
        }

        // here from the constriaints of the problem
        // the candidate size is 1 or 2

        
        for (j = n; j >= 1; --j) {
            vector<int> candidate;
            for (i = 1; i <= n; ++i) {
                if ((int) mp[i].size() == 1) {
                    candidate.push_back(i);
                }
            }

            if ((int) candidate.size() == 1) {
                visited[candidate.front()] = 1;
                ans[j] = candidate.front();
                int id = *mp[ans[j]].begin();
                for (auto v : st[id]) {
                    mp[v].erase(id);
                }
                mp[ans[j]].clear();
            } else {        
                for (auto c : candidate) {
                    // cout << "solve " << c << endl;
                    if (solve(c, j)) {
                        break;
                    }
                }
                break;
            }
        }

        for (i = 1; i <= n; ++i) {
            printf("%d ", ans[i]);
        }
        printf("\n");
    }
    return 0;
}
  		 	   	  	  	  	    	   	 	