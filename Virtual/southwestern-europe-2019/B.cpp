#include <bits/stdc++.h>

using namespace std;

char st[25];
map<string, int> mp;

int main() {
    int N, i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%s", st);
        mp[string(st)]++;
    }

    for (auto iter : mp) {
        if (iter.second > N - iter.second) {
            cout << iter.first << endl;
            return 0;
        }
    }

    printf("NONE\n");
    return 0;
}