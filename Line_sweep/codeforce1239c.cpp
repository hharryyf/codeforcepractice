#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 101111
using namespace std;
 
struct people {
    ll t;
    int id;  
};
// this is just a simulation problem with priority queue
// optimization
people peo[MAX_SIZE];
ll ans[MAX_SIZE];
priority_queue<int, vector<int>, greater<int>> q;
 
static bool cmp(const people &a, const people &b) {
    if (a.t != b.t) return a.t < b.t;
    return a.id < b.id;
}
 
int main() {
    int n, i;
    ll p;
    ll T = 0;
    scanf("%d%lld", &n, &p);
    for (i = 1; i <= n; i++) {
        scanf("%lld", &peo[i].t);
        peo[i].id = i;
    }
    
    sort(peo + 1, peo + 1 + n, cmp);
    
    i = 1;
    while (i <= n || !q.empty()) {
        int v;
        if (!q.empty()) {
            v = q.top();
            q.pop();
        } else {
            v = peo[i].id;
            T = peo[i].t;
            i++;
        }
        
        ans[v] = T + p;
        T += p;
        
        while (i <= n && peo[i].t <= T) {
            if (peo[i].id < v) {
                v = peo[i].id;
                ans[v] = T + p;
                T += p;
            } else {
                q.push(peo[i].id);
            }
            i++;
        }
        
        
    }
    
    for (i = 1; i <= n; i++) {
        printf("%lld ", ans[i]);
    }
    printf("\n");
    return 0;
}
