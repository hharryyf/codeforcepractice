// @E solved this problem
#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<int , int > ii;

vector<array<int , 3>> ps;
int N , K;
vector<int> a , b;
ll ans[100005];

int main(){
    int i;
    scanf("%d %d" , &N , &K);
    for(i = 1; i <= N; ++i){
        int x;
        scanf("%d" , &x);
        a.push_back(x);
    }
    for(i = 1; i <= N; ++i){
        int x;
        scanf("%d" , &x);
        b.push_back(x);
    }
    for(i = 0; i < N; ++i){
        ps.push_back({a[i] , b[i] , i + 1});
    }
    sort(ps.begin() , ps.end());
    multiset<int> vis;
    ll sum = 0; 
    for(auto& e : ps){
        if(vis.size() > K){
            int v = *vis.begin();
            sum -= v;
            vis.erase(vis.begin());
        }
        sum += e[1];//e.y;
        ans[e[2]] = sum;
        vis.insert(e[1]);
    }
    for(int i = 1; i <= N; ++i){
        printf("%lld " , ans[i]);
    }
    printf("\n");
}