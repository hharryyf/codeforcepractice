#include <bits/stdc++.h>
#define MAX_SIZE 100111
using namespace std;

map<int, multiset<int>> incr, decr;
int n;
int ans[MAX_SIZE];
int pos[MAX_SIZE];
int b[MAX_SIZE];
int main() {
    scanf("%d", &n);
    int i;
    for (i = 0; i < n; i++) {
        int v;
        scanf("%d", &v);
        pos[v-1] = i;
    }
    
    for (i = 0; i < n; i++) {
        scanf("%d", &b[i]);
        b[i]--;
        if (pos[b[i]] <= i) {
            decr[i - pos[b[i]]].insert(b[i]);
        } else {
            incr[pos[b[i]] - i].insert(b[i]);
        }
    }
    
    for (i = 0 ; i < n; i++) {
        ans[i] = n;
        if (!incr.empty()) {
            ans[i] = min(ans[i], incr.begin()->first + i); 
        }
        
        if (!decr.empty()) {
            ans[i] = min(ans[i], decr.begin()->first - i);
        }
        
        if (!decr.empty() && decr.begin()->first == i) {
            for (auto nv : decr.begin()->second) {
                incr[-i].insert(nv);
            }
            decr.erase(i);
        }
        
        // b[i] is the element that would be thrown to the back
        // and the distance at the moment is pos[b[i]]
        // hence the key should be pos[b[i]] - i in incr
        incr[pos[b[i]] - i].erase(b[i]);
        if (incr[pos[b[i]] - i].empty()) {
            incr.erase(pos[b[i]] - i);
        }
        decr[n - pos[b[i]] + i].insert(b[i]);
    }
    
    for (i = 0 ; i < n; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
