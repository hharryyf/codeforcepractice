#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;
typedef long long ll;
char st[MAX_SIZE];
int p[MAX_SIZE];
ll dp[MAX_SIZE];
vector<int> ans;

int main() {
    int N, i, j = 0;
    scanf("%s", st+1);
    N = strlen(st+1);
    for (i = 2; i <= N; ++i) {
        while (j > 0 && st[i] != st[j+1]) j = p[j];
        if (st[i] == st[j+1]) ++j;
        p[i] = j;
    }

    i = N;
    
    while (i > 0) {
        ans.push_back(i);
        i = p[i];
    }

    cout << ans.size() << endl;
    for (i = N; i >= 1; --i) {
        ++dp[i];
        dp[p[i]] += dp[i];
    }

    for (i = (int) ans.size() - 1; i >= 0; --i) {
        cout << ans[i] << " " << dp[ans[i]] << endl;
    }
    return 0;
}