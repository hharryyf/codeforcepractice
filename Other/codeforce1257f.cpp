#include <bits/stdc++.h>
#define MAX_SIZE 111
typedef long long ll;
using namespace std;

map<vector<int>, int> mp;
int a[MAX_SIZE];

int main() {
    int N, i, j;
    scanf("%d", &N);
    for (i = 0; i < N; ++i) {
        scanf("%d", &a[i]);
    }

    for (i = 0 ; i < (1<<15); ++i) {
        vector<int> vc(N);
        for (j = 0 ; j < N; ++j) {
            vc[j] = __builtin_popcount((a[j] & 32767) ^ i) - __builtin_popcount((a[0] & 32767) ^ i);
        }

        if (!mp.count(vc)) mp[vc] = i;
    }

    for (i = 0 ; i < (1<<15); ++i) {
        vector<int> vc(N);
        for (j = 0 ; j < N; ++j) {
            vc[j] = __builtin_popcount(((a[0]>>15) & 32767) ^ i) - __builtin_popcount(((a[j]>>15) & 32767) ^ i); 
        }

        if (mp.count(vc)) {
            printf("%d\n", (i << 15) + mp[vc]);
            return 0;
        }
    }

    printf("-1\n");
    return 0;
}