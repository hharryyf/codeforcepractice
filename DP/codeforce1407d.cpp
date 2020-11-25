#include <bits/stdc++.h>
#define MAX_SIZE 300011
using namespace std;
int N;
int h[MAX_SIZE];
int dp[MAX_SIZE];
vector<int> inc, des;

int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) scanf("%d", &h[i]);
    inc.push_back(1);
    des.push_back(1);
    for (i = 2; i <= N; ++i) {
        dp[i] = dp[i-1] + 1;
        while (!inc.empty() && h[inc.back()] > h[i]) {
            dp[i] = min(dp[i], dp[inc.back()] + 1);
            inc.pop_back();
        }
        
        while (!des.empty() && h[des.back()] < h[i]) {
            dp[i] = min(dp[i], dp[des.back()] + 1);
            des.pop_back();
        }
        
        if (!inc.empty()) dp[i] = min(dp[i], dp[inc.back()] + 1);
        if (!des.empty()) dp[i] = min(dp[i], dp[des.back()] + 1);
        while (!inc.empty() && h[inc.back()] == h[i]) inc.pop_back();
        while (!des.empty() && h[des.back()] == h[i]) des.pop_back();
        
        inc.push_back(i);
        des.push_back(i);
    }

    printf("%d\n", dp[N]);
    return 0;
}