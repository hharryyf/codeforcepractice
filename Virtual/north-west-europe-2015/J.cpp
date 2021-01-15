#include <bits/stdc++.h>
using namespace std;
int main() {
    int N, i;
    scanf("%d", &N);
    map<int, int> mp;
    for (i = 0 ; i <= 255; ++i) {
        int b1 = i, b2 = (i << 1) & 255;
        mp[b1 ^ b2] = i;
    }
    
    while (N-- > 0) {
        int v;
        scanf("%d", &v);
        printf("%d ", mp[v]);
    }
    return 0;
}