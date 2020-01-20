#include <bits/stdc++.h>
#define MAXL 1011
#define MAX_SIZE 29
using namespace std;

int indegree[MAX_SIZE], outdegree[MAX_SIZE], f[MAX_SIZE];
char s[MAXL];
/*
    We use the Euler path existence condition for
    a directed graph. An euler path exists iff there is
    at most 1 vertex with +1 outdegree and 1 vertex with -1 outdegree
    and the "undirected" graph must be connected
*/
unordered_set<char> h;
void init() {
    int i;
    h.clear();
    for (i = 0 ; i < MAX_SIZE; i++) {
        outdegree[i] = indegree[i] = 0;
        f[i] = i;
    }
}

int find(int x) {
    if (x == f[x]) return x;
    return f[x] = find(f[x]);
}

void unionset(int a, int b) {
    int x = find(a), y = find(b);
    f[x] = y;
}

int main() {
    int T, n, i;
    scanf("%d", &T);
    while (T > 0) {
        init();
        scanf("%d", &n);
        for (i = 0 ; i < n; i++) {
            scanf("%s", s);
            int len = strlen(s);
            outdegree[s[0] - 'a']++, indegree[s[len-1] - 'a']++;
            h.insert(s[0]);
            h.insert(s[len-1]);
            unionset(s[0] - 'a', s[len-1] - 'a');
        }
        
        bool valid = true;
        unordered_set<int> p;
        for (auto ch : h) {
            p.insert(find(ch - 'a'));
        }
        
        if (p.size() != 1) valid = false;
        int cntp = 0, cntn = 0, cntb = 0;
        for (i = 0 ; i < 26; i++) {
            if (outdegree[i] - indegree[i] == 1) cntp++;
            if (indegree[i] - outdegree[i] == 1) cntn++;
            if (abs(outdegree[i] - indegree[i]) >= 2) cntb++;
        }
        
        if (cntb != 0) {
            valid = false;
        }
        
        if (cntp == 1 && cntn == 1 && valid) {
            valid = true;
        } else if (cntp == 0 && cntn == 0 && valid) {
            valid = true;
        } else {
            valid = false;
        }
        
        if (!valid) {
            printf("The door cannot be opened.\n");
        } else {
            printf("Ordering is possible.\n");
        }
        T--;
    }
    return 0;
}
