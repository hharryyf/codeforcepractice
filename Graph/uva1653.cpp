#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 10111


struct state {
   int rem;
   int digit;
   int id;
};

int visited[MAX_SIZE];
unordered_map<int, int> pre;
int tol = 0;
unordered_set<int> h;
unordered_map<int, state> stt;
vector<int> could;
int n, m;



void init() {
    int i;
    memset(visited, 0, sizeof(visited));
    h.clear();
    stt.clear();
    could.clear();
    pre.clear();
    tol = 0;
}

int BFS() {
    queue<state> q;
    for (auto num : could) {
        if (num != 0) {
            pre[++tol] = -1;
            q.push(state{num % n, num, tol});
            stt[tol] = state{num % n, num, tol};
        }
    }
    
    while (!q.empty()) {
        state curr = q.front();
        q.pop();
        if (curr.rem == 0) {
            return curr.id;
        }
        if (visited[curr.rem]) continue;
        visited[curr.rem] = 1;
        for (auto num : could) {
            int nxt = (curr.rem * 10 + num) % n;
            if (!visited[nxt]) {
                q.push(state{nxt, num, ++tol});
                stt[tol] = state{num % n, num, tol};
                pre[tol] = curr.id;
               
            }
        }
    } 
    return -1;
}

void print(int start) {
    stack<int> ret;
    
    while (start != -1) {
        ret.push(stt[start].digit);
        start = pre[start];
    }
    
    while (!ret.empty()) {
        printf("%d", ret.top());
        ret.pop();
    }
    
    printf("\n");
}

int main() {
    int cnt = 1;
    while(scanf("%d%d", &n, &m) != EOF) {
        init();
        int i;
        for (i = 0 ; i < m; i++) {
            int v;
            scanf("%d", &v);
            h.insert(v);
        }
        
        for (i = 0 ; i <= 9; i++) {
            if (h.find(i) == h.end()) {
                could.push_back(i);
            }
        }
        int ret = BFS();
        if (ret == -1) {
            printf("Case %d: -1\n", cnt);
        } else {
            printf("Case %d: ", cnt);
            print(ret);
        }
        cnt++;
    }
    return 0;
}
