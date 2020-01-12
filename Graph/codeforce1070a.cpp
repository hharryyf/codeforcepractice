#include <bits/stdc++.h>

using namespace std;

struct state {
    int id, digit, rem, sm;  
};

unordered_map<int, state> st;
unordered_map<int, int> p;
bool visited[501][5001];
int d, s;

int bfs() {
    int i;
    int cnt = 0;
    queue<state> q;
    for (i = 1; i <= 9; i++) {
       if (i <= s) {
           q.push(state{cnt, i, i % d, i});
           p[cnt] = -1;
           st[cnt] = state{cnt, i, i % d, i};
           visited[i % d][i] = true;
           cnt++;
       }
    }
    
    while (!q.empty()) {
        state curr = q.front();
        q.pop();
        if (curr.rem == 0 && curr.sm == s) {
            return curr.id;
        }
        
        for (i = 0 ; i < 10; i++) {
            int nxtrem = (curr.rem * 10 + i) % d;
            int nxtsm = curr.sm + i;
            if (nxtsm <= s && !visited[nxtrem][nxtsm]) {
                visited[nxtrem][nxtsm] = true;
                st[cnt] = state{cnt, i, nxtrem, nxtsm};
                q.push(state{cnt, i, nxtrem, nxtsm});
                p[cnt] = curr.id;
                cnt++;
            }
        }
    }
    return -1; 
}

void print(int fid) {
    if (fid == -1) {
        printf("-1\n");
        return;
    }
    
    stack<int> ret;
    while (fid != -1) {
        ret.push(st[fid].digit);
        fid = p[fid];
    }
    
    while (!ret.empty()) {
        printf("%d", ret.top());
        ret.pop();
    }
    printf("\n");
}

int main() {
    scanf("%d%d", &d, &s);
    // return the id of the state
    int ret = bfs();
    print(ret);
    return 0;
}
